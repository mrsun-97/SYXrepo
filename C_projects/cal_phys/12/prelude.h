#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>

double randi(void){
    return rand()/(double)RAND_MAX;
}