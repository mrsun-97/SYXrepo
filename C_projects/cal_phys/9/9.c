#include "prelude.h"
#define NUM 2000
#define RANGE 4.5

const double k = 1.26865;//1.26865
const double c = 1.12432;

//归一化比较函数的积分
double F(double x){
    double r = sqrt(2.0);
    return 0.5 + (0.5*(log((x+k*r)*x+k*k)-log((x-k*r)*x+k*k))-atan(1-r*x/k)+atan(r*x/k+1))/(2*PI);
}

//比较函数
double f(double x){
    double r = sqrt(2.0)/PI;
    return c*r/k/(1+pow(x/k,4));
}

//高斯分布
double prob(double x){
    return exp(-x*x/2)/sqrt(2*PI);
}

//比较
double rate(double x){
    return prob(x)/f(x);
}

//给定y,寻找满足y=F(x)的x，返回下
int search(double y[2*NUM+1], double eta){
    if(eta < y[0] || eta > y[2*NUM]){
        return -1;
    }
    int mid, l = 0, r = 2*NUM;
    while(r-l>1){
        mid = (l+r)/2;
        if(eta>=y[mid]){
            l = mid;
        }
        else{
            r = mid;
        }
    }
    return l;

}

int main(){
    double arr[2][2*NUM+1];
    double x, y, eta;
    double h = RANGE/(double)NUM;
    int i, j;

    //数组中存储F(x)
    for(i=-NUM;i<=NUM;i++){
        x = i*h;
        arr[0][i+NUM] = x;
        arr[1][i+NUM] = F(x);
    }

    double a, b;
    srand(3);
    for(j=0;j<1000000;j++){
        eta = randi();
        i = search(arr[1], eta);    //F^-1(eta)
        if(i<0){ continue; }       
        a = arr[0][i];
        b = arr[0][i+1];
        if(randi()>rate((a+b)/2)){ continue; }  //舍选
        eta = a+(b-a)*randi();      //小区间内均匀分布
        printf("%.6lf\n",eta);      //输出
    }

    return 0;
}