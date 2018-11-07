#include "prelude.h"
#define N 110000000
#define SEED1 1
#define dp 27
#define dq 98
#define MACRO_RAND_16807    if(1){\
                                rz=z%q;\
                                z=a*rz-r*((z-rz)/q);\
                                z=z<0?z:z-m;\
                                z=z+b;\
                                z=z<0?z+m:z;\
                            }
//N = 5e7;
//下面为16807标准数据
const int a0 = 16807, b0 = 0, m0 = 2147483647;

int main(){
    double rate1 = -1.0, rate2 = -1.0;
    if(1){      //16807
        int a, b, m, r, q;
        int cac[2], flag, count1;
        //在这里以下符号表示 x[n+1] = { a*x[n] + b } mod m;
        a = a0;    
        b = b0;
        m = m0;
        r = m%a;        //m = a*q + r
        q = (m-r)/a;    //q
        if(r>=q){
            printf("r >= q\n");
            return 1;
        }

        int i, z, rz;
        z = SEED1;
        count1 = 0;
        flag = 0;
        for(i=0;i<N;i++){

            MACRO_RAND_16807

            if(flag==1){        //flag==1说明cac[]只存有z[n-1]
                if(z>cac[0]){
                    cac[1] = z;
                    flag = 2;
                }
                else{
                    cac[0] = z;
                }
            }
            else if(flag==2){   //flag==2说明z[n-1]<z[n]，此时取出z[n+1]与二者比较
                if(z>=cac[1]){  //z[n]<z[n+1],已经不满足条件，令z[n]成为新的z[n-1],flag不变，继续之前步骤
                    cac[0] = cac[1];
                    cac[1] = z;
                }
                else{
                    if(z>cac[0]){
                        //满足条件,计数加一
                        count1++;
                    }
                    cac[0] = z;
                    flag = 1;
                }
            }
            else if(flag==0){   //该分支只在第一次循环执行
                cac[0] = z;
                flag = 1;
            }
        }
        rate1 = N/(double)count1;
    }

    if(2){      //斐波那契延迟产生器
        int a, b, m, r, q;
        int i, z, rz;
        int cac[2], flag, count2;
        a = a0;    
        b = b0;
        m = m0;
        r = m%a;        //m = a*q + r
        q = (m-r)/a;    //q
        int len = dp>dq?dp:dq;
        //生成空队列
        int *que = queue_with_capacity(len);
        z = SEED1;

        //队列使用16807初始化
        for(i=0;i<len;i++){     
            MACRO_RAND_16807
            que[i] = z;
        }

        int I, k = len-1;
        m = (m0-1)/2;
        flag = 0;
        count2 = 0;
        for(i=0;i<N;i++){
            //I[n] = {I[n-p] - I[n-q]} mod m
            //下面利用循环队列que[MAX(p,q)]计算
            I = (que[(k+dp)%len] - que[(k+dq)%len])%m;
            while(I<0){
                I += m;
            }
            que[k] = I;
            k--;
            if(k<0){
                k += len;
            }

            if(flag==1){
                if(I>cac[0]){
                    cac[1] = I;
                    flag = 2;
                }
                else{
                    cac[0] = I;
                }
            }
            else if(flag==2){
                if(I>=cac[1]){
                    cac[0] = cac[1];
                    cac[1] = I;
                }
                else{
                    if(I>cac[0]){
                        //满足条件,计数加一
                        count2++;
                    }
                    cac[0] = I;
                    flag = 1;
                }
            }
            //下面分支只在第一次循环执行
            else if(flag==0){
                cac[0] = I;
                flag = 1;
            }
        }
        rate2 = N/(double)count2;
    }
    printf("1/rate1: %.4lf\n", rate1);
    printf("operator '-'\n");
    printf("1/rate2: %.4lf\n", rate2);
    return 0;
}