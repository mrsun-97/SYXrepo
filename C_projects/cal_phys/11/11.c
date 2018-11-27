#include "prelude.h"

//#define _P1_

double f(double x){
    double a = sqrt(x);
    return sqrt(a+x)-1.06*a;
}

int main(){
#ifdef _P1_
    //题目一
    const double sqx = 4.0*sqrt(2)/3*1.06;  //sqx为被抽取出的1.06√x的积分值
    int i, j, num = 100000;
    double r, sum;
    srand((unsigned)time(0));
    for(j=0;j<1000;j++){
        sum = 0;
        for(i=0;i<num;i++){
            r = 2*randi();
            sum += f(r);
        }
        sum = sum/num*2;
        sum += sqx;
        printf("%d\t%lf\n",num, sum);
    }
    
#else
    //题目二
    srand((unsigned)time(0));
    int i, j, num = 100000;
    double x, y, z, u, v, sum;
    for(j=0;j<1000;j++){
        sum = 0;
        #pragma omp parallel for private(x,y,z,u,v) reduction(+:sum) num_threads(4)
        {
            for(i=0;i<num;i++){
                x = 0.9*randi();
                y = 0.8*randi();
                z = 0.9*randi();
                u = 2.0*randi();
                v = 1.3*randi();
                double tmp = 6.0-(x*x+y*y+z*z+u*u+v*v);
                sum += tmp;
            }
        }
        sum = sum/num*(0.9*0.8*0.9*2.0*1.3);
        printf("%d\t%lf\n",num, sum);
    }
#endif
    return 0;
}