#include <stdio.h>
#include <math.h>
#include <stdlib.h>

const double PI = 3.141592653590;

double randi(void){
    return rand()/((double)RAND_MAX + 1);
}

double randj(void){
    return 2*randi()-1;
}

double randl(void){
    double y = randi();
    return y>0.5 ? 1-sqrt(2*(1-y)) : sqrt(2*y)-1;
}