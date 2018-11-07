#include "prelude.h"



//512×512 array
static lattice A;

int main(){
    int i, j, k, tmp;
    int count;
    const int time = 9012;
    srand(59);
    count = 0;
    const int percent = 5;
    for(i=0;i<LEN;i++){
        for(j=0;j<LEN;j++){
            k = rand()%100;
            if(k<percent){
                A[i][j] = 1;
                count++;
            }
            else{
                A[i][j] = 0;
            }
        }
    }
    printf("start:\t%.3f\t%%\n",rate(count));
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
            #pragma omp barrier     //貌似自带阻塞不需要这条？
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
        if(k%5==1){
            count = fcount(A);
            printf("%d\t%.1f\t%%\n",k, rate(count));
        }
    }
    return 0;
}
