#include "prelude.h"

int main(){

    double dx, dy, dk;
    const double a = 10.0;
    const double b = 10.0;
    const double t = 1e-4;
    double Dx, Dy, Dk;
    Dk = 1/(a*a + b*b);
    Dx = sqrt(a)/(sqrt(a)+sqrt(b));
    Dy = 1 - Dx;
    int i, j; 
    double x, y, k;
    FILE *fp = fopen("data.txt","w");
    if(!fp){
        printf("can't open data.txt\n");
        return 1;
    }
    srand(1);
    for(j=0;j<1000;j++){
        x = y = k = 0;
        for(i=0;i<54321;i++){
            fprintf(fp, "%lf\t%lf\t%lf\t", k, x, y);
            dk = sqrt(2*Dk*t)*randj();
            dx = sqrt(2*Dx*t)*randj();
            dy = sqrt(2*Dy*t)*randj();
            x += dx*cos(k) - dy*sin(k);
            y += dx*sin(k) + dy*cos(k);
            k += dk;
        }
        fprintf(fp, "%lf\t%lf\t%lf\n", k, x, y);
    }

    fclose(fp);
    return 0;
}