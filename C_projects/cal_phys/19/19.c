#include "prelude.h"

typedef struct {
    double x;
    double y;
}position, *point;

const double sigma_x = 0.8;
const double sigma_y = 0.4;
const double Delta_r = 0.05;
const double beta = 2.0;

//哈密顿量
double Ham(double x, double y){
    double x1 = x/sigma_x;
    double y1 = y/sigma_y;
    return (x1*x1+y1*y1)/2.0;
}

//计算下一个点的位置
void next(point Q){
    double dr = Delta_r*randi(), da = 2*PI*randi();
    double xt = Q->x + dr*cos(da), yt = Q->y + dr*sin(da);
    double r = exp(-beta*(Ham(xt,yt)-Ham(Q->x,Q->y)));
    if(randi()>=r) return;
    else {
        Q->x = xt;
        Q->y = yt;
    }
}

//初始化、热化
point init(int n){
    point Q = (point)malloc(sizeof(position));
    if(!Q){
        printf("failed to generate point\n");
        exit(1);
    }
    Q->x = -randi()-0.2;
    Q->y = +randi()+0.2;

    //热化
    int i=n>0?n:-n;
    while(i-->0){
        next(Q);
    }
    printf("Initialized.\n");
    return Q;
}

double evaluate(double (*fn)(point), point Q){
    return (*fn)(Q);
}

double x_square(point Q){
    double a = Q->x;
    return a*a;
}

double y_square(point Q){
    double b = Q->y;
    return b*b;
}

double x2_plus_y2(point Q){
    double a = Q->x, b = Q->y;
    return a*a+b*b;
}


int main(){
    FILE* fp = fopen("data.txt", "w");
    if(!fp){
        printf("can't open data.txt\n");
        return 1;
    }
    srand(8);
    point Q = init(50); 
    int i, N = (int)1e4;
    double sum[3] = {0,0,0};

    //开始抽样
    for(i=0;i<N;i++){
        next(Q);
        sum[0] += evaluate(x_square, Q);
        sum[1] += evaluate(y_square, Q);
        sum[2] += evaluate(x2_plus_y2, Q);
        fprintf(fp,"%.4lf\t%.4lf\n", Q->x, Q->y);
    }
    //输出结果
    for(i=0;i<3;i++){
        fprintf(fp, "%.4lf\t0\n", sum[i]/N);
    }

    fclose(fp);
}