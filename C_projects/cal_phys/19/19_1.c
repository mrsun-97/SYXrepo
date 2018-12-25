#include "prelude.h"

typedef struct {
    double x;
    double y;
}position, *point;

const double sigma_x = 5*1.414;
const double sigma_y = 0.1;
const double beta = 2.0;
const int N = (int)1e5;
double Delta_r = 0.4;
int seed = 0;

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
    //printf("Initialized.\n");
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
    FILE* fp = fopen("data_1.txt", "w");
    if(!fp){
        printf("can't open data.txt\n");
        return 1;
    }       
    double exa[3] = {0};
    exa[0] = sigma_x*sigma_x/beta;
    exa[1] = sigma_y*sigma_y/beta;
    exa[2] = exa[0] + exa[1];
    int k = 0;
    for(k=0;k<=5;k++){
        fprintf(fp,"$%.2lf$ ", Delta_r);
        double sqrtsig2=0;

        for(seed=1;seed<10;seed++){
            srand(seed);
            point Q = init(N/100);
            int i;
            double sum[3] = {0,0,0};
            //开始抽样
            for(i=0;i<N;i++){
                next(Q);
                //sum[0] += evaluate(x_square, Q);
                //sum[1] += evaluate(y_square, Q);
                sum[2] += evaluate(x2_plus_y2, Q);
                //fprintf(fp,"%.4lf\t%.4lf\n", Q->x, Q->y);
            }
            //输出结果
            for(i=2;i<3;i++){
                double real = sum[i]/N, exact = exa[i];
                exact = (real-exact)/exact*100;
                fprintf(fp, "&%5.2lf ", exact);
                sqrtsig2 += exact*exact;
            }
        }
        //直接输出Latex代码
        fprintf(fp, "&%.2lf ", sqrt(sqrtsig2/9.0));
        fprintf(fp, "\\\\ \\hline\n");
        printf("%d\n",k);
        Delta_r *= 5;
    }
    fclose(fp);
    return 0;
}