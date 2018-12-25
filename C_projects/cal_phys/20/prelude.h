#include <stdio.h>
#include <math.h>
#include <stdlib.h>

const double PI = 3.1415926535898;

double randi(void){
    return rand()/((double)RAND_MAX + 1);
}

double randn(double mu, double sigma){
    double u = 1.0-randi();
    double v = randi();
    double z = sqrt(-2*log(u))*cos(2*PI*v);
    return sigma*z+mu;
}