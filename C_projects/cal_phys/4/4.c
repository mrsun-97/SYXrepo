#include "prelude.h"
#define N 110000000
#define SEED 1
//N = 5e7;
//下面为16807标准数据
const int a0 = 16807, b0 = 0, m0 = 2147483647;
static float Af[N]={-1.0};

int main(){
    int a, b, m, r, q;
    //在这里以下符号表示 x[n+1] = { a*x[n] + b } mod m;
    a = 12345;      
    b = 432143215;
    m = m0;
    r = m%a;        //m = a*q + r
    q = (m-r)/a;    //q

    if(r>=q){
        printf("r >= q\n");
        return 1;
    }
/*
    FILE *fp;
    fp = fopen("data.txt","w");
    if(!fp){
        printf("can't open data.txt\n");
        return 2;
    }
*/
    int i, z0, z, rz;
    z = z0 = SEED;      //seed;
    for(i=0;i<m;i++){
        rz = z%q;
        z = a*rz - r*((z-rz)/q);
        /*以上与Schrage方法一致，
        下面考虑b会使z溢出，
        于是用同余系中的等价负数去计算，
        防止溢出
        */
        z = z<0 ? z : z-m;
        z = z + b;
        z = z<0 ? z+m : z;
        if(i<N){
            //根据I[n]计算第n个随机数I[n]/m，保证随机数属于[0,1)。
            Af[i] = (float)z/m;
        }
        if(z==z0){ break;}
    }
    z = i+1;
/*
    fprintf(fp, "%d\n%d\n%d\n\n", a, b, m);
    for(i=0;i<N;i++){
        fprintf(fp,"%f\n", Af[i]);
    }
    fclose(fp);
*/

    //计算C(l)
    FILE *ft = fopen("cl.txt","w");
    if(!ft){
        printf("can't open cl.txt\n");
        return 3;
    }
    fprintf(ft, "T = %d\t1-T/m = %lf\n\n", z, (double)(m-z)/m);
    int l, n;
    float xn[5]={0}, dn[5]={0}, xnl, tmp;
    //每次取出连续的n个数
    for(n=1000;n<N/5;n*=10){
        fprintf(ft, "n = %d\n", n);
        for(i=1;i<5;i++){
            xn[i] = 0.0;
        }
        for(i=100;i<n+100;i++){
            tmp = Af[i];
            xn[1] += tmp;
            tmp = tmp*tmp;
            xn[2] += tmp;
            xn[3] += tmp*Af[i];
            xn[4] += tmp*tmp;
        }
        //xn[k]分别表示k阶矩
        xn[1] /= n;
        xn[2] /= n;
        xn[3] /= n;
        xn[4] /= n;
        fprintf(ft, "<x^k>\t\t<x>\t\t\t<x^2>\t\t<x^3>\t\t<x^4>\n");
        fprintf(ft, "value\t\t%f\t%f\t%f\t%f\n", xn[1], xn[2], xn[3], xn[4]);
        for(i=1;i<5;i++){
            tmp = 1.0/(i+1.0);
            dn[i] = fabsf(xn[i]-tmp)/tmp*100;
        }
        fprintf(ft, "delta\t\t%-7.3f%%\t%-7.3f%%\t%-7.3f%%\t%-7.3f%%\n", dn[1], dn[2], dn[3], dn[4]);
        fprintf(ft, "   l\t |C(l)| \n");
        for(l=1;l<n/2;l*=10){
            xnl = 0.0;
            for(i=100 ;i<n+100;i++){
                xnl += Af[i]*Af[i+l];
            }
            xnl /= n;
            tmp = xn[1]*xn[1];
            tmp = (xnl-tmp)/(xn[2]-tmp);
            fprintf(ft, "%7d\t%f\n", l, fabsf(tmp));
        }
    }
    fclose(ft);
    return 0;
}