#include "prelude.h"
#define NUM 100000
#define THETA (1/6.0)
#define PHI 1.25

int main(){
    srand(21);
    double xi, eta;
    double x, y, z;
    double tmp=0.0;
    int i;
    const double n[3] = {sin(THETA*PI)*cos(PHI*PI), sin(THETA*PI)*sin(PHI*PI), cos(THETA*PI)};
    double scl;
    int count[10], k;
    for(k=0;k<10;k++){
        count[k] = 0;
    }
    FILE *fp = fopen("data.txt","w");
    FILE *ft = fopen("data2.txt","w");
    if(!fp || !ft){
        printf("failed to open file\n");
        return 1;
    }
    for(i=0;i<NUM;i++){
        xi = randi();       //随机变量 ξ=randi()为0~1内的随机数
        rand();             //没作用，减小随机数相关性
        eta = randi();      //随机变量 η
        
        z = 2*xi - 1;
        tmp = sqrt(1-z*z);
        eta = 2*PI*eta;
        x = tmp*cos(eta);
        y = tmp*sin(eta);

        //计算内积
        scl = n[0]*x + n[1]*y + n[2]*z;

        //这里记录空间直角坐标系中的坐标
        fprintf(fp, "%.7lf\t%.7lf\t%.7lf\n", x, y, z);

        z = acos(z);        // z -> θ
        eta = eta;          // η ∈ [0,2π)
        fprintf(ft, "%.7lf\t%.7lf\n", z, eta);

        //放大内积，按取整切成10片
        k = (int)floor(scl*11+2);
        if(k>=0 && k<10){
            count[k] += 1;
        }
    }
    
    printf("theta = %.2lfPI, phi = %.2lfPI\ncount:\n", THETA, PHI);
    for(k=0;k<10;k++){
        printf("\t%d\n", count[k]);
    }
    printf("average:\n\t%.2lf\n", NUM/2.0/11.0);
    fclose(fp);
    fclose(ft);
    return 0;
}