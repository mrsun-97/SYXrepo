#include "prelude.h"

#define DIM 2
static int arr[DIM];

//行走一步
void walk(void){
    int k;
    k = rand()%(2*DIM);
    arr[k%DIM] += k/DIM*2-1;
}

//判断粒子是否位于原点
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

//初始化粒子坐标
int init(void){
    int i;
    for(i=0;i<DIM;i++){
        arr[i] = 0;
    }
    return i;
}


int main(){
    srand((unsigned int)time(0));
    int pnum = 100000;
    int step = 2;
    int i, j;
    int back;
    FILE *fp;
    switch(DIM){
        case 1: fp = fopen("data_1.txt","w");break;
        case 2: fp = fopen("data_2.txt","w");break;
        case 3: fp = fopen("data_3.txt","w");break;
        default: printf("dim != 1, 2 or 3\n");return 2;
    }
    if(!fp){
        printf("can't open data.txt\n");
        return 1;
    }

    //改变步长，记录每次数据
    for(step=2;step<=200000; ){
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
        fprintf(fp, "%d\t%.4lf\n", step, rate);
        step *= 3*((step-1)%9+1)-1; //步长为5,2交替
    }

    fclose(fp);
    return 0;
}