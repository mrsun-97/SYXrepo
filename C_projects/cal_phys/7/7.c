#include "prelude.h"
#define NUM 20000
#define THETA (1/3.0)
#define PHI 1.25

int main(){

    srand(3);
    double u, v, t, r2;

    double x[3], scl;
    //定义z’轴方向n
    const double n[3] = {sin(THETA*PI)*cos(PHI*PI), sin(THETA*PI)*sin(PHI*PI), cos(THETA*PI)};
    int count[10];
    int i, j, k;
    for(k=0;k<10;k++){
        count[k] = 0;
    }

    FILE *fp = fopen("data.txt", "w");
    if(!fp){
        printf("can't open file\n");
        return 1;
    }

    for(i=0;i<NUM;i++){
        u = 2*randi()-1;
        rand();
        v = 2*randi()-1;
        r2 = u*u + v*v;
        if(r2>1){
            continue;
        }

        //计算坐标（x，y，z)
        x[0] = 2*u*sqrt(1-r2);
        x[1] = 2*v*sqrt(1-r2);
        x[2] = 1-2*r2;
        scl = 0.0;
        for(j=0;j<3;j++){
            scl += x[j]*n[j];
        }
        //输出到data.txt
        fprintf(fp, "%.7lf\t%.7lf\t%.7lf\n", x[0], x[1], x[2]);

        //放大内积，按取整切成10片
        k = (int)floor(scl*10.5+1);
        if(k>=0 && k<10){
            count[k] += 1;
        }
    }

    printf("theta = %.2lfPI, phi = %.2lfPI\ncount:\n", THETA, PHI);
    for(k=0;k<10;k++){
        printf("\t%d\n", count[k]);
    }
    //由于抽样效率不是1，计算时要乘以效率PI/4
    printf("average:\n\t%.2lf\n", NUM/2.0/10.5*PI/4);

    return 0;
}