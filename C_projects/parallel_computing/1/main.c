#include "main.h"
#include <omp.h>
#define NUM_TNREADS 4

int main() {

    srand( (unsigned)time(NULL) );          //初始化seed

    Vec A;
    Vec trans[NUM_TNREADS][NUM_TNREADS];

    int i, n, N2=NUM_TNREADS*NUM_TNREADS;
    int s[NUM_TNREADS];
    data reg[N2];                           //存放正则采样数据
    n = 65;//rand()%256 + 50;               //数据量大小
    A.len = n;
    A.pt = (data*)malloc(n*sizeof(data));
    if(A.pt eqs NULL){
        printf("failed to generate data\n");
        return 1;
    }
    for(i=0;i<A.len;i++){
        A.pt[i] = rand()%8192-2048;                       
    }
    int step = roundf(n/(float)NUM_TNREADS);
    display(A);
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

        int step2 = floorf( (end-start)/(float)NUM_TNREADS );
        for(j=id*NUM_TNREADS,k=0;k<NUM_TNREADS;k++){
            reg[j+k] = A.pt[start+k*step2]; //正则采样
        }

        #pragma omp barrier
        #pragma omp master
        {   
            quick_sort(reg, 0, N2-1);       //采样排序
            for(j=1;j<NUM_TNREADS;j++){     //选择主元
                reg[j] = reg[j*NUM_TNREADS];
            }
            display(A);
        }
        #pragma omp barrier

        data *t = A.pt + start;             //指针t用来遍历数组，开始指向数组首地址
        for(j=1;j<NUM_TNREADS;j++){         //主元划分,写入全局交换矩阵
            //trans[j-1][id].len = 0;
            trans[j-1][id].pt = t;          //该段首地址
            data cmp = reg[j];              //读取主元
            for( ;*t<cmp;t++){              //检查直到有大于该主元的元素，划分出一段
                //pass
            }
            trans[j-1][id].len = t-trans[j-1][id].pt;   //算出该段长度
        }
        trans[NUM_TNREADS-1][id].pt = t;
        trans[NUM_TNREADS-1][id].len = A.pt + end - t;
        #pragma omp barrier                 //等待写入完成

        Vec B;                              //全局交换后每个线程拥有的数据
        B = vec_fuse(trans[id], NUM_TNREADS);
        //#pragma omp atom
            s[id] = B.len;
        #pragma omp barrier
        for(j=0,t=A.pt;j<id;j++){           //计算新的首地址
            t += s[j];
        }
        merge_sort(B, t);                   //归并排序
        
    }//end parallel
    display(A);
    return 0;
}
