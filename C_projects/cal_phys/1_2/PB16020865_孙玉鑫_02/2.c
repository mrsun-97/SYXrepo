#include "prelude.h"
#include <omp.h>
#define maxN 128
#define maxV2 6400
#define perT 1
typedef f128 dat;

int is_deverge(dat a, dat b){
    dat r2 = a*a + b*b;
    if(!(r2<=maxV2)){
        return 1;
    }else{
        return 0;
    }
}

int cal(dat reZ, dat imZ, dat reC, dat imC){
    dat re = reZ;
    dat im = imZ;
    dat t = 0.0;
    int i, j, count = 0;
    for(i=0;i<maxN;i++){
        for(j=0;j<perT;j++){
            t = (re+im)*(re-im) + reC;
            im = 2*re*im + imC;
            re = t;
        }
        count++;
        if(is_deverge(re, im)){
            break;
        }
    }
    return count;
}

int main(){


    const int A = 10000;
    const int B = 10000;
    const dat xlm = 1.0;
    const dat ylm = 1.0;
    int i, j, k;
    dat a = 2*xlm/A;
    dat b = 2*ylm/B;
    int arr[A+1][B+1];
    FILE *fp;
    fp = fopen("./juliaset.txt", "w");
    if(!fp){
        printf("failed to open file\n");
        exit(0);
    }
    #pragma omp parallel for //num_threads(thread_count)
    {
        for(i=0;i<A+1;i++){
            for(j=0;j<B+1;j++){
                arr[i][j] = cal(
                    -xlm + a*j, -ylm + b*i,
                    0.3, -0.4
                );
            }
        }
    }
    fprintf(fp, "%llf\t%llf\t%llf\t%llf\n", xlm, ylm, a, b);
    for(i=0;i<A+1;i++){
        for(j=0;j<B+1;j++){
            fprintf(fp, "\t%d", arr[i][j]);
        }
        fprintf(fp, "\n");
    }

    return 0;
}