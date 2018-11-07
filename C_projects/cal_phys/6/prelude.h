#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const double PI = 3.1415926535898;

//为使后面计算中0与2π为同一个点，要求随机数在[0，1)取值
const double RAND_MAX_PLUS = 1.0 + (double)RAND_MAX;

double randi(void){
    return rand()/RAND_MAX_PLUS;
}