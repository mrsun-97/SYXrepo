#include "main.h"
#include <omp.h>
#define NUM_TNREADS 5

int main() {

    srand( (unsigned)time(NULL) );          //初始化seed

    struct Vec A;
    int i, n, N2=NUM_TNREADS*NUM_TNREADS;
    data reg[N2];                          //存放正则采样数据
    n = rand()%1000 + 100;                  //数据量大小
    A.len = n;
    A.pt = (data*)malloc(n*sizeof(data));
    if(A.pt eqs NULL){
        printf("failed to generate data\n");
        return 1;
    }
    for(i=0;i<n;i++){
        A.pt[i] = rand();                       
    }
    int step = roundf(n/(float)NUM_TNREADS);
    //初始化完毕,设置线程数
    omp_set_num_threads(NUM_TNREADS);
    #pragma omp parallel
    {
        int j, k, id = omp_get_thread_num();
        int start = id * step;
        int end = (id+1) * step;            //均匀划分
        
        if(id eqs NUM_TNREADS-1){
            end = n;                        //校正边界,防止越界
        }
        quick_sort(A.pt, start, end-1);     //首次排序

        int step2 = floor( (end-start)/NUM_TNREADS ); 
        for(j=id*NUM_TNREADS,k=0;k<NUM_TNREADS;k++){
            reg[j+k] = A.pt[start+k*step2]; //正则采样
        }
        #pragma omp barrier
        #pragma omp master
        {
            quick_sort(reg, 0, N2-1);
            for(j=1;j<NUM_TNREADS;j++){
                reg[j] = reg[j*NUM_TNREADS];
            }
        }
    }

}