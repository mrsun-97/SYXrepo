#include "prelude.h"

int main(){

    //计算扩散系数
    double dx, dy, dk;
    const double a = 0.004;
    const double b = 0.08;
    const double t = 1e-4;
    double Dx, Dy, Dk;
    Dk = 1/(a*a + b*b);
    Dx = sqrt(a)/(sqrt(a)+sqrt(b));
    Dy = 1 - Dx;


    int i, j; 
    double x, y, k;
    FILE *fp = fopen("data.txt","w");
    if(!fp){
        printf("can't open data.txt\n");
        return 1;
    }
    srand(2);
    for(j=0;j<1000;j++){//模拟1000个粒子
        x = y = k =0;
        for(i=0;i<160000;i++){
            if(i%20==0){//每隔20步采样一次
                fprintf(fp, "%lf\t%lf\t%lf\t", k, x, y);
            }

            //产生随机步长
            dk = sqrt(2*Dk*t)*randj();
            dx = sqrt(2*Dx*t)*randj();
            dy = sqrt(2*Dy*t)*randj();

            //转换到实验室参考系
            x += dx*cos(k) - dy*sin(k);
            y += dx*sin(k) + dy*cos(k);
            k += dk;
        }
        fprintf(fp, "%lf\t%lf\t%lf\n", k, x, y);
    }

    fclose(fp);
    return 0;
}