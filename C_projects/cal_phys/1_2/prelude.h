#include <stdio.h>
#include <math.h>
#define ture true

typedef long double  f128;
typedef double  f64;
typedef float  f32;
typedef struct
{

    f128 re;
    f128 im;

} COMPLEX;

//定义 COMPLEX.init()
COMPLEX complex(f128 Re, f128 Im){
    COMPLEX Z;
    Z.re = Re;
    Z.im = Im;
    return Z;
}

void showsize(void){
    printf("==================================\n");
    printf("size of basic type: (double: %d)\n", sizeof(double));
    printf("\tf32:  %3d\n",sizeof(f32));
    printf("\tf64:  %3d\n",sizeof(f64));
    printf("\tf128: %3d\n",sizeof(f128));
    printf("==================================\n");
}
