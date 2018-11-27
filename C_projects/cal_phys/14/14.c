#include "prelude.h"

#define DIM 2
static int arr[DIM];

void walk(void){
    int i;
    for(i=0;i<DIM;i++){
        arr[i] += rand()%2*2-1;
    }
}

int is_back(void){
    int i, sum=0;
    for(i=0;i<DIM;i++){
        sum += arr[i];
    }
    if(sum!=0){
        return 0;
    }
    else{
        sum = 0;
        for(i=0;i<DIM;i++){
            sum += arr[i]*arr[i];
        }
        if(sum!=0){
            return 0;
        }
        else return 1;
    }
}

int init(void){
    int i;
    for(i=0;i<DIM;i++){
        arr[i] = 0;
    }
    return i;
}

int main(){
    srand((unsigned int)time(0));
    int pnum = 10000;
    int step = 10000;
    int i, j;
    int back;
    back = 0;
    for(i=0;i<pnum;i++){
        init();
        for(j=0;j<step;j++){
            walk();
            if(is_back()){
                back++;
                break;
            }
            else continue;
        }
    }
    double rate = back/(double)pnum;
    printf("back rate: %.4lf%%\n", 100*rate);

    return 0;
}