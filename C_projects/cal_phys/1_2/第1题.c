#include "prelude.h"
#define precision

int main(){

    const int M = 1600;
    const int N = 1500;
    //const f128 PI = 3.14159265358979323846;
    //f64 lam_min = 0.318309886183791;

    typedef f128 dat;

    dat lam_min = 0.706;
    dat arr[M][N+1];
    dat lambda = 0.0;
    /*
    dat f(dat x, dat lambda){
        return lambda*sin(PI*x);
    }*/
    dat l = (0.86559 - lam_min)/M;
    dat xmax = 0.0, x = 0.0;

    int i, _i, j;
    for(j=0;j<M;j++){
        arr[j][0] = lambda = lam_min + j*l;
        /*首先利用泰勒展开近似sin函数，
        找出一个介于0与不动点之间的值xmax*/
        xmax = sqrt(6*(1-1/(PI*lambda)))/PI;

        //初始值为 x < xmax.
        x = 0.9 * xmax;
        //用多次迭代预估不动点
        for(i=0;i<654321;i++){
            x = f(x,lambda);
        }
        arr[j][1] = x;
        for(i=2;i<N+1;i++){
            x = f(x,lambda);
            arr[j][i] = x;
        }
    }
#ifdef release
    FILE *fp;
    fp = fopen("./data.txt", "w");
    if(fp == NULL) {
        printf("文件打开失败!\n");
        return -1;
    }
    for(j=0;j<M;j++){
        fprintf(fp, "\n");
        //下面的循环写入整行
        for(i=0;i<=N;i++){
            fprintf(fp, "%.7llf\t", arr[j][i]);
        }        
    }
    fclose(fp);
#endif
//下面计算L指数的大小并输出
#ifdef precision
    FILE *fp;
    fp = fopen("./less.txt", "w");
    if(fp == NULL) {
        printf("文件打开失败!\n");
        return -1;
    }
    for(j=0;j<M;j++){
        fprintf(fp, "\n");
        fprintf(fp, "%.8llf\t", arr[j][0]);
        for(i=1;i<=N;i++){
            fprintf(fp, "%.8llf\t", arr[j][i]);
        }        
    }
    fclose(fp);
    
    FILE *ft;
    ft = fopen("./Lyapunov.txt", "w");
    if(fp == NULL) {
        printf("文件打开失败!\n");
        return -1;
    }
    int n = 1000;
    const int k = 10;
    f128 x01, x02;
    f128 x1, x2;
    f128 Lya;
    f128 xs[k];
    for(j=0;j<20*M;j++){
        lambda = lam_min + j*l/20;
        xmax = sqrt(6*(1-1/(PI*lambda)))/PI;
        x01 = x1 = 0.6*xmax;
        x02 = x2 = 0.600001*xmax;
        for(i=0;i<n-k;i++){
            x1 = f(x1, lambda);
            x2 = f(x2, lambda);
            //printf("%d  x1 = %.6llf  x2 = %.6llf\n",i+1, x1, x2);
        }
        for(i=0;i<k;i++){
            x1 = f(x1, lambda);
            x2 = f(x2, lambda);
            x = x2 - x1;
            xs[i] = (x>=0 ? x : -x);
        }
        x = xs[0];
        for(i=1;i<k;i++){
            x += xs[i];
        }
        Lya = log( x/k/(x02-x01) ) / n;   
        fprintf(ft, "\n%.8llf\t%.8llf", lambda, Lya);
    }
   fclose(ft);
#endif
    return 0;
}
