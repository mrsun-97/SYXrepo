#include "main.h"
#include <mpi.h>
#define FLUSH {if(!rank) fflush(stdout);}

// void myMPI_allDisplay(Vec A){
//     int size
// }

int main(){

    MPI_Init(NULL, NULL);
    int size, rank, tmp, i;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    Vec A, Ai;
    A.pt = NULL;
    Ai.pt = NULL;
    int sendvar[size], sd[size];
    MPI_Status stat;
    if(rank eqs 0){
        srand( (unsigned int)time(NULL) );
        Vec send[size];
        rand_init(&A);
        
        printf("A.len = %d\n", A.len);

        //分段
        int step = round(A.len/(double)size);
        if(step*size<=A.len) step++;
        for(i=0;i<A.len%size;i++){
            //send[i].pt = A.pt+step;
            send[i].len = step;
        }
        for( ;i<size;i++){
            //send[i].pt = A.pt+(step-1);
            send[i].len = step-1;
        }
        for(i=0;i<size;i++){
            sendvar[i] = send[i].len;
        }
        display(A);
    }
    //发送
    // if(!rank) printf("send start:\n");
    MPI_Scatter(sendvar, 1, MPI_INT, &tmp, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if(!rank){
        for(i=0;i<size;i++){
            sd[i] = 0;
            for(int j=i-1;j>=0;j--){
                sd[i] += sendvar[j];
            }
        }
    }
    empty_init(&Ai, tmp);
    MPI_Scatterv(A.pt, sendvar, sd, MPI_INT, Ai.pt, Ai.len, MPI_INT, 0, MPI_COMM_WORLD);
    // printf("%d received\n", rank);
    //局部排序
    quick_sort(Ai.pt, 0, Ai.len-1);
    // display(Ai);
    // printf("%d quicksort done\n", rank);
    printf("A%d.len = %d\n", rank, Ai.len);
    MPI_Barrier(MPI_COMM_WORLD);
    data reg[size];
    int step2 = floor(Ai.len/(double)size);
    for(i=0;i<size;i++){
        //正则采样
        reg[i] = Ai.pt[step2*i+(step2-1)/2];
    }
    

    Vec regAll;
    regAll.pt = NULL;
    empty_init(&regAll, (rank eqs 0)?size*size:(size-1));
    MPI_Gather(reg, size, MPI_INT, regAll.pt, size, MPI_INT, 0, MPI_COMM_WORLD);
    // printf("%d gather done\n", rank);

    //对采样排序
    MPI_Barrier(MPI_COMM_WORLD);
    if(rank eqs 0){
        // printf("rank %d: quick sort\n", rank);
        quick_sort(regAll.pt, 0, regAll.len-1);
        for(i=1;i<size;i++){
            regAll.pt[i-1] = regAll.pt[i*size];
        }
    }
    //data mel[size-1];
    // if(!rank) printf("\nBroadcast:\n");
    MPI_Bcast(regAll.pt, size-1, MPI_INT, 0, MPI_COMM_WORLD);
    // printf("%d received Bcast\n", rank);
    regAll.len = size-1;
    //regAll.pt =  realloc(regAll.pt, size-1);

    //段内划分
    Vec arv[size];
    data *t = Ai.pt;
    for(i=0;i<regAll.len;i++){
        arv[i].pt = t;
        for( ;*t<regAll.pt[i];*t++);   //pass
        arv[i].len = t - arv[i].pt;
    }
    arv[size-1].pt = t;
    arv[size-1].len = Ai.pt + Ai.len - t;
    // printf("%d separate done\n", rank);

    //准备全局交换
    // if(!rank) printf("alltotal start:\n");
    MPI_Barrier(MPI_COMM_WORLD);
    int recvvar[size];
    for(i=0;i<size;i++){
        sendvar[i] = arv[i].len;
    }
    //发送数据大小信息
    MPI_Alltoall(sendvar, 1, MPI_INT, recvvar, 1, MPI_INT, MPI_COMM_WORLD);
    // printf("%d needs %d (INT)\n", rank, recvvar[2]);
    int rd[size], j;
    for(i=0;i<size;i++){
        sd[i] = rd[i] = 0;
        for(j=i-1;j>=0;j--){
            sd[i] += sendvar[j];
            rd[i] += recvvar[j];
        }
    }
    int total = rd[size-1]+recvvar[size-1];
    Vec Bi;
    Bi.pt = NULL;
    empty_init(&Bi, total);
    //全局交换
    MPI_Alltoallv(Ai.pt, sendvar, sd, MPI_INT, Bi.pt, recvvar, rd, MPI_INT, MPI_COMM_WORLD);
    // printf("%d alltotal done\n", rank);
    // FLUSH
    //归并排序
    printf("B%d.len = %d\n", rank, Bi.len);
    empty_init(&Ai, Bi.len);
    merge_sort(Bi, Ai.pt);
    //printf("%d mergesort done\n", rank);

    //发送每个进程数据量大小
    MPI_Gather(&Bi.len, 1, MPI_INT, recvvar, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if(rank eqs 0){
        for(i=0;i<size;i++){
            rd[i] = 0;
            for(j=i-1;j>=0;j--){
                rd[i] += recvvar[j];
            }
        }
    }
    //发送数据
    MPI_Gatherv(Bi.pt, Bi.len, MPI_INT, A.pt, recvvar, rd, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    if(!rank) display(A);
    MPI_Finalize();

    return 0;

}