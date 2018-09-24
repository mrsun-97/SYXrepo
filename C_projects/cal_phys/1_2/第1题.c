#include "prelude.h"
#define release

int main(){

    const int N = 2001;
    const int n = 256;
    const int M = 500;
    const f128 PI = 3.14159265358979323846;
    //f64 lam_min = 0.318309886183791;
    f64 lam_min = 0.32;
    f64 arr[M][N+1];
    f64 lambda = 0.0;
    f64 f(f64 x, f64 lambda){
        return lambda*sin(PI*x);
    }
    f64 l = (1.5 - lam_min)/M;
    f64 xmax = 0.0, x = 0.0;

    int i, _i, j;
    for(j=0;j<M;j++){
        arr[j][0] = lambda = lam_min + j*l;
        /*首先利用泰勒展开近似sin函数，
        找出一个介于0与不动点之间的值xmax*/
        xmax = sqrt(6*(1-1/(PI*lambda)))/PI;
        //初始值为 x < xmax.
        x = arr[j][1] = 0.5 * xmax;
        for(i=2;i<N+1;i++){
            x = f(x,lambda);
            arr[j][i] = x;
        }
    }
#ifdef testmod
    //输出测试
    for(i=0;i<51;i++){
        printf("%d\t%lf\t\t", i, arr[100][i]);
        _i = i + 950;
        printf("%d\t%lf\n", _i, arr[100][_i]);
    }
#endif
#ifdef release
    FILE *fp;
    fp = fopen("./data.txt", "w");
    if(fp == NULL) {
        printf("文件打开失败!\n");
        return -1;
    }
    //fprintf(fp, "N %d", N+1);
    for(j=0;j<M;j++){
        fprintf(fp, "\n");
        //下面的循环写入整行
        for(i=0;i<=N;i++){
            fprintf(fp, "%.6lf\t", arr[j][i]);
        }
    }
    fclose(fp);
#endif
    return 0;
}
