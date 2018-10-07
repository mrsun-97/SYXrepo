#include "prelude.h"
#define EQ ==

int main(){

    const int M = 200;
    const int N = 7654321;
    int n = 1000;
    int k = 5;
    typedef f128 dat;

    dat DELTA = 1e-12;
    dat lam_min = 0.605;
    dat lam_max = 0.8656;
    dat ll = (lam_max-lam_min)/M;
    dat lambda, x, Lya, xs[k], x01, x02, x1, x2;
    int e, i, j, K = 1;
    int count, len = 1, _len;
    FILE *fp, *ft;
    HEAD A = NULL;
    ft = fopen("./Lyapunov1.txt", "w");
    fp = fopen("./prsc.txt", "w");
    if(!fp || !ft){
        printf("UdfError: main: fopen() failed\n");
        exit(1);
    }
    for(e=0;e<10;e++){              //求出前十个分叉点
        lambda = lam_min;
        printf("\ne = %d\t lam_min = %.5llf\n", e, lam_min);
        if(len!=K){                 //当前周期不是2^e，程序有误 
            printf("ERROR! len = %d\n", len);
            exit(1);
        }
        while(lambda < lam_max){    //等间隔寻找分叉点直到超过寻找范围
            x = x_max(lambda);
            x01 = x1 = 0.75*x;
            x02 = x2 = 0.750001*x;
            for(i=0;i<n-k;i++){
                x1 = f(x1, lambda);
                x2 = f(x2, lambda);
            }
            for(i=0;i<k;i++){
                x1 = f(x1, lambda);
                x2 = f(x2, lambda);
                x = x2 - x1;
                xs[i] = (x>=0 ? x: -x);
            }
            x = xs[0];
            for(i=1;i<k;i++){       //计算Lyapunov指数
                x += xs[i];
            }
            Lya = logl( fabsl(x/k/(x02-x01)) )/n;

            printf("\n%.8llf\t%e\n", lambda, Lya);

            if(!(Lya>0)){           //没有分岔时，计算至看到2K周期
                count = 0;
                do{ 
                    x2 = f(x1, lambda);
                    x = x2;
                    for(i=1;i<10240;i++){ x = f(x, lambda); }
                    if((x == x1) && (f(x,lambda) == x2)){
                        //printf("%d\n", count);
                        j = 0;
                        for(i=0;i<2*K;i++){
                            x = f(x, lambda);
                        }
                        for(i=0;i<2*K;i++){
                            j += (fabsl(x-x1)<DELTA)?1:0;
                            x = f(x, lambda);
                            x1 = f(x1, lambda);
                        }
                        //free(cmp);
                        if(j==2*K){
                            printf("T = %d\n",K);
                            break;
                        }
                    }
                    x1 = x;
                }while(++count<2000);
                if(      count>1999){
                    printf("j = %d\n",j);
                    for(i=0;i<3*K;i++){
                        x = f(x, lambda);
                        printf("%.64LF\n", x);
                    }
                    printf("UdfError: main: needs further calculating\n");
                    goto ending;
                }

                printf(" count = %d\n", count);

            }   
            else{                   //临界分岔时，迭代指定的次数     
                x = x1;
                for(i=0;i<4*N;i++){
                    x = f(x, lambda);
                }
            }
            A = init();
            for(i=0;i<1200;i++){
                x = f(x, lambda);
                if(!in_set(A, x, DELTA)){
                    push(A, x);
                }
            }
            _len = length(A);
            printf("_len = %d\n", _len);
            if(_len<=len){          //没有出现分岔
                fprintf(fp, "\n%.9llf", lambda);
                output(A, fp);
                fprintf(ft, "\n%.9llf\t%.6llf", lambda, Lya);
                drop(&A);
                lambda += ll;
                if(_len<len){
                    printf("_len < len\n");
                }
                //printf("\t%.5llf", lambda);
                continue;
                
            }
            drop(&A);
            break;
            
        }
        if(lambda>=lam_max){
            printf("lambda hit maximum\n");
            return 0;
        }
        //此时说明已找到分岔位置，下面用二分法定位
        printf("searching presice lambda...\n");
        f128 left = lambda - ll;
        f128 right = lambda;
        drop(&A);
        while(right-left>=1e-9/K){
            lambda = 0.5*(left+right);
            x = 0.75*x_max(lambda);

            while(DELTA>=1e-24){
                
                j = 0;
                while(j<6){
                    for(i=0;i<N;i++){
                        x = f(x, lambda);
                    }
                    A = init();
                    for(i=0;i<1200;i++){
                        x = f(x, lambda);
                        if(!in_set(A, x, DELTA)){
                            push(A, x);
                        }
                    }
                    _len = length(A);
                    if(_len==2*K || _len==K){ 
                        goto conti;
                    }

                    printf("now _len = %d  (%d)\n", _len, j);
                    
                    drop(&A);
                    j++;
                }

                if(j>=6){
                    drop(&A);

                    for(i=0;i<6*K;i++){
                        x = f(x, lambda);
                        printf("%.64LF\n", x);
                    }

                    printf("WORNING 1\n");

                    //goto ending;
                }
                DELTA *= 2e-1;
            }
            printf("WORNING 3, e = %d\n", e);
            goto ending;
conti:
            if(_len<=2*K && _len>K){
                right = lambda;
                drop(&A);
                continue;
            }else if(_len!=K){
                printf("ERROR2!\n");
                exit(1);
            }
            else{                //len = K 
                left = lambda;
                fprintf(fp, "\n%.8llf", lambda);
                output(A, fp);
                drop(&A);
                lambda += ll;
            }
        }
        
        if(_len>len){ len = _len; }
        else if(_len==len){ len = 2*len; }
        else{
            printf("UdfError: main: wrong length\n");
            exit(1);
        }
        K *= 2;
        lam_min = right;
        ll /= 4.0;
        DELTA /= 2.0;
    }

ending:
    fclose(fp);
    fclose(ft);
    return 0;
}