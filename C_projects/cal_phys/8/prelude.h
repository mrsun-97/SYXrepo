#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define LEN 512

typedef char _lines[LEN];
typedef _lines lattice[LEN];

int isodd(int a, int b){
    return 1&(a^b);
}

float rate(int n){
    return 100*n/(float)(LEN*LEN);
}

//定义循环边界
int plus1(int x){
    int a = x+1;
    return a>=LEN?0:a;
}
int minus1(int x){
    int a = x-1;
    return a<0?LEN-1:a;
}

int fcount(lattice A){
    int i, j, count = 0;
    #pragma omp parallel for num_threads(6) schedule(static, 8)
    {
        for(i=0;i<LEN;i++){
            for(j=0;j<LEN;j++){
                if(A[i][j]==1){
                    #pragma omp atom
                    count++;
                }
            }
        }
    }
    return count;
}