#include "prelude.h"
#define N 1000

//设置初值
const double V0 = 5.0;
static double V[N] = {0};
static double M[N] = {0};
double Ed = 0;
int time = (int)1e4;

//扰动一次
void dev(double v){
    int i = rand()%N;
    double vt = V[i] + randn(0,v);
    double Et = Ed + 0.5*M[i]*(V[i]*V[i] - vt*vt);
    if(Et>=0){
        Ed = Et;
        V[i] = vt;
    }
    else return;    //不接受
}

//粒子初始化
void init(void){
    int i;
    for(i=0;i<N;i++){
        V[i] = V0*sin(2*PI*i/N);
        M[i] = 1.0;
    }
    Ed = 0.5*M[0]*V[0]*V[0]/10;
}

//输出
void output(FILE *fp){    
    static int flag = 0;
    int i;
    if(!flag){
        for(i=0;i<N;i++){
            fprintf(fp, "%.1lf\t", M[i]);
        }
        fprintf(fp, "\n");
        flag = 1;
    }
    for(i=0;i<N;i++){
        fprintf(fp, "%.3lf\t", V[i]);
    }
    fprintf(fp, "\n");
}

//统计温度
double temp(void){
    int i;
    double T = 0;
    for(i=0;i<N;i++){
        T += 0.5*M[i]*V[i]*V[i];
    }
    return T/N;
}

int main(){

    FILE *fp = fopen("data.txt","w");
    if(!fp){
        printf("can't open data.txt\n");
        exit(1);
    }

    init();
    int t;
    for(t=0;t<=time;t++){
        dev(V0/2);
        if(t%(time/100)==0){
            output(fp);
            printf("%lf\n", temp());
        }
    }

    fclose(fp);
    return 0;
}