#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// double * _t_integrate(double (*f)(double), double a, double b, int k){
//     if(k>40){
//         printf("k must be within [1,40]!\n");
//         exit(0);
//     }
//     if(fabs(b-a)<1e-6){
//         printf("b meets a!\n");
//         exit(0);
//     }

// }

double randi(void){
    return rand()/(double)RAND_MAX;
}