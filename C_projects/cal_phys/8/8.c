#include "prelude.h"

//512×512 array
static lattice A;

int main(){
    FILE *fp=fopen("lattice.txt","w");
    if(!fp){
        printf("failed to open lattice.txt");
        return 2;
    }
    int i, j, k, tmp;
    int count;
    //迭代次数
    const int time = 101011;
    srand(17);
    count = 0;
    const int percent = 5;
    //按给定概率设置初态
    for(i=0;i<LEN;i++){
        for(j=0;j<LEN;j++){
            rand();
            k = rand()%100;
            if(k<percent){
                A[i][j] = 1;
            }
            else{
                A[i][j] = 0;
            }
        }
    }

    //统计位于|1>态的个数
    count = fcount(A);
    printf("start:\t%.3f\t%%\n",rate(count));
    //这里输出到了stdout，因为可以通过shell控制重定向到文件
    
    for(k=0;k<time;k++){
        #pragma omp parallel num_threads(6) threadprivate(tmp)
        {   
            //更新偶数格子
            #pragma omp for schedule(static, 4)
            for(i=0;i<LEN;i++){
                for(j=0;j<LEN;j++){
                    if(!isodd(i,j)){
                        tmp = 0;
                        tmp = A[minus1(i)][j] + A[i][minus1(j)] + A[i][plus1(j)] + A[plus1(i)][j];
                        if(tmp==2){
                            A[i][j] = 1 - A[i][j];
                        }
                    }
                }
            }
            #pragma omp barrier     //自带阻塞否？

            //更新奇数格子
            #pragma omp for schedule(static, 4)
            for(i=0;i<LEN;i++){
                for(j=0;j<LEN;j++){
                    if(isodd(i,j)){
                        tmp = 0;
                        tmp = A[minus1(i)][j] + A[i][minus1(j)] + A[i][plus1(j)] + A[plus1(i)][j];
                        if(tmp==2){
                            A[i][j] = 1 - A[i][j];
                        }
                    }
                }
            }
            
        }//end parallel
        if(1){
            count = fcount(A);
            printf("%d\t%.1f\t%%\n",k, rate(count));
        }
    }

    //输出512×512矩阵
    for(i=0;i<LEN;i++){
        for(j=0;j<LEN;j++){
            fprintf(fp, "%d\t", (int)A[i][j]);
        }
        fseek(fp, -1L, SEEK_CUR);
        fprintf(fp, "\n");
    }
    fclose(fp);
    return 0;
}
