#include "prelude.h"

double g(double x){
    if(x < 2961)
        return (x-2900)*27+1614;
    else if(x < 2969)
        return 6000;
    else if(x < 2994)
        return 2900;
    else if(x < 3007)
        return 38000;
    else return 1200;
}

double _K(double y){
    if(y < 148687.5){
        int c = 807/13.5;
        return sqrt(y/13.5+c*c)+2900-c;
    }
    else if(y < 196687.5)
        return (y-148687.5)/6000+2961;
    else if(y < 269187.5)
        return (y-196687.5)/2900+2969;
    else if(y < 763187.5)
        return (y-269187.5)/38000+2994;
    else 
        return (y-763187.5)/1200+3007;
}

double K(double y){
    return _K(771587.5*y);
}

static int ap[2][114];


double p(double x){
    if(x<3014 && x>=2900){
        int n = (int)floor(x);
        return ap[1][n-2900];
    }
    else return 0;
}

double rate(double x){
    return p(x)/g(x);
}

static double arr[115];

//直接抽样法，离散反函数
int search(double y){
    int l=0, h=114, mid;
    while(h-l>1){
        mid = (h+l)/2;
        if(y >= arr[mid]){
            l = mid;
        }
        else{
            h = mid;
        }
    }
    return l;
}

int main(){

    FILE *fp = fopen("data.TXT","r");
    if(!fp){
        printf("can't open data.TXT\n");
        exit(0);
    }
    int i = 0, j;
    while(!feof(fp)){
        fscanf(fp,"%d\t%d\n", &ap[0][i], &ap[1][i]);
        i++;
    }
    fclose(fp);
    srand(3);

    //舍选法 rand1
    fp = fopen("rand1.txt","w");
    if(!fp){
        printf("can't open rand1.txt\n");
        exit(0);
    }
    double x, y, eta;
    for(j=0;j<1000000;j++){
        y = randi();
        x = K(y);           //用反函数确定x
        eta = randi();
        if(eta<=rate(x)){   //根据p(x)与f(x)的比值确定是否舍去
            fprintf(fp, "%d\n", (int)floor(x));
        }
    }
    fclose(fp);

    //直接抽样法 rand2
    fp = fopen("rand2.txt","w");
    if(!fp){
        printf("can't open rand2.txt\n");
        exit(0);
    }

    //arr[]内存储 Σp_i 的值，即归一化概率分布的原函数的值
    arr[0] = 0.0;
    for(i=1;i<115;i++){
        arr[i] = arr[i-1]+ap[1][i-1];
    }
    for(i=1;i<115;i++){
        arr[i] /= arr[114];
    }

    //开始
    for(j=0;j<500000;j++){
        y = randi();
        i = search(y);      //把y映射为xi对应的i
        fprintf(fp, "%d\n", i+2900);
    }
    fclose(fp);
    return 0;
}