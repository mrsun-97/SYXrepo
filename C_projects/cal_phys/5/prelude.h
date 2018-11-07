#include <stdio.h>
#include <stdlib.h>

int* queue_with_capacity(int Q){
    if(Q < 1){
        exit(-1);
    }
    int i;
    int *q = (int*)malloc(sizeof(int)*Q);
    if(q==NULL){
        printf("failed to create queue[%d]\n",Q);
        exit(-1);
    }
    for(i=0;i<Q;i++){
        q[i] = 0;
    }
    return q;
}