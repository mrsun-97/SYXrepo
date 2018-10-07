#include "prelude.h"
//#define coordinated4
//#define coordinated6
#define coordinated8
#define Len 1024
#define Hei 1024

//定义内存连续的二维数组
typedef int vec[Len];
typedef vec mat[Hei];

int xplus1(int x){
    int a = x+1;
    return a>=Len?0:a;
}
int xminus1(int x){
    int a = x-1;
    return a<0?Len-1:a;
}
int yplus1(int y){
    int a = y+1;
    return a>=Hei?0:a;
}
int yminus1(int y){
    int a = y-1;
    return a<0?Hei-1:a;
}


void walk(int *x, int *y){
    int sx = *x;
    int sy = *y;
    switch (rand()%4){
        case 0: sx = xplus1(sx);break;
        case 1: sx = xminus1(sx);break;
        case 2: sy = yplus1(sy);break;
        case 3: sy = yminus1(sy);break;
    }
    *x = sx;
    *y = sy;
}

int done(mat A, int x, int y){
    int flag;
    flag = A[y][xplus1(x)] + A[y][xminus1(x)] + A[yplus1(y)][x] + A[yminus1(y)][x]
        + A[yplus1(y)][xplus1(x)] + A[yplus1(y)][xminus1(x)] + A[yminus1(y)][xplus1(x)] + A[yminus1(y)][xminus1(x)];
    return flag;
}

int main(){

    srand(time(0));
    
    int i,j,k,s,sx,sy;
    mat arr;
    for(i=0;i<Hei;i++){
        for(j=0;j<Len;j++){
            //初始化网格，0表示此处无粒子
            arr[i][j] = 0;
        }
    }
    FILE *fp;
    fp = fopen("data.txt","w");
    if(!fp){
        printf("failed to open file\n");
        exit(0);
    }
    float tmp;
    //定义凝结核位置
    arr[Hei/2][Len/2] = 1;
    /*for(i=0;i<Hei;i++){
        for(j=0;j<Len;j++){
            tmp = (i-Hei/2)*(i-Hei/2)+(j-Len/2)*(j-Len/2)/8;
            if(tmp >= 0.18e4 && tmp <=0.25e4){
                arr[i][j] = 1;
            }
        }
    }*/
    //放置的点数：1.5%面积
    int N = 15000;
    //并行模拟,每次进入8个点，忽略点之间相互影响
    j=0;
    #pragma omp parallel for num_threads(8) private(s,sx,sy) shared(arr)
    {   
        for(k=0;k<N;k++){
            if((j++)%100 eqs 0){
                printf("%d\n",j);
            }
            s = rand()%(Hei+Len);
            if(s<Len){
                sx = s;
                sy = 0;
            }
            else{
                sx = 0;
                sy = s - Len;
            }
            while(!done(arr,sx,sy)){
                walk(&sx,&sy);
            }
            arr[sy][sx] = 1;
        }
    }
    fprintf(fp, "%d\t%d\n", Len, Hei);
    for(i=0;i<Hei;i++){
        for(j=0;j<Len;j++){
            if(arr[i][j]!=0){
                fprintf(fp, "%4d\t%4d\n", j, i);
            }
        }
    }

    fclose(fp);

    //sandbox
    int _N, M=0, r=0;
    FILE *ft;
    ft = fopen("./sandbox.txt","w");
    if(!ft){
        printf("failed to open sandbox.txt\n");
        exit(0);
    }
    for(k=0;k<Len/2-1;k++){
        _N = 0;
        //对当前矩形内粒子进行计数
        for(i=Hei/2-r;i<=Hei/2+r;i++){
            for(j=Len/2-r;j<=Len/2+r;j++){
                if(arr[i][j]){
                    _N++;
                }
            }
        }
        if(_N eqs M) break;     //扩大矩形后计数_N相比上一次计数M没有变化，说明已经完全覆盖图形，可以结束计数
        fprintf(ft, "%4d\t%5d\n", r,_N);
        M = _N;
        r += 1;
    }
    fclose(ft);

    //box-counting
    FILE *fs;
    fs = fopen("./box-counting.txt","w");
    if(!fs){
        printf("failed to open sandbox.txt\n");
        exit(0);
    }
    int K[11];
    K[0] = 1024;
    for(i=1;i<11;i++){
        K[i] = K[i-1]/2;
    }
    int I, J, count;
    //无脑for循环数格子
    for(k=0;k<11;k++){
        count = 0;
        for(I=0;I<Hei/K[k];I++){
            for(J=0;J<Len/K[k];J++){
                //下方循环寻找(I， J)中是否存在粒子
                for(i=0;i<K[k];i++){
                    for(j=0;j<K[k];j++){
                        if(
                            arr[I*K[k]+i][J*K[k]+j] != 0
                        ){  
                            count++;
                            //找到粒子，跳出循环
                            goto here;  
                        }
                    }
                }
                here:
                count&&count;
                // (I, J) finished, goto (I, J+1)
            }
        }
        //end
        //输出本次计数
        fprintf(fs, "%4d\t%5d\n", Hei/K[k], count);
    }
    fclose(fs);
    return 0;
}