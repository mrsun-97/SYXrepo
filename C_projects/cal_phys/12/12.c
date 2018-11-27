#include "prelude.h"

double G1(double x){        // 0, 1
    return sqrt(12)*(x-0.5);
}

double G2(double x){        // 0, 1
    if(x>0){
        return -log(x)-1;
    }
    else return NAN;
}

double G3(double x){        // 0, 1
    if(x<0) return NAN;
    
    double a;
    if(x<0.5){
        a = 2*sqrt(2*x);
    }
    else{
        a = 2*x+1;
    }
    return (12*a-23)/sqrt(71);  //标准化
}

int main(){
    srand(1);
    int i, j, k, l;
    int A[3] = {2, 5, 10};
    double xi, sum[3];
    FILE *fp = fopen("data.txt","w");
    if(!fp){
        printf("can't open data.txt\n");
        exit(0);
    }
    for(k=0;k<100000;k++){
        for(l=0;l<3;l++){
            for(j=0;j<3;j++){
                sum[j] = 0;
            }
            for(j=0;j<A[l];j++){
                xi = randi();
                sum[0] += G1(xi);
                sum[1] += G2(xi);
                sum[2] += G3(xi);
            }
            for(i=0;i<3;i++){
                sum[i] /= sqrt(j);
            }
            fprintf(fp, "%lf\t%lf\t%lf\t", sum[0], sum[1], sum[2]);
        }
        fseek(fp, -1L, SEEK_CUR);
        fprintf(fp,"\n");
    }
}