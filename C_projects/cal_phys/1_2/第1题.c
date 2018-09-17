#include "prelude.h"
#define testmod

int main(){
    const int N = 1001;
    const f128 PI = 3.14159265358979323846;
    f64 arr[N];
    f64 lambda = 0.8;// λ >= 0.318309886183791
    f64 f(f64 x, f64 lambda){
        return lambda*sin(PI*x);
    }

    f64 xmax = sqrt(6*(1-1/(PI*lambda)))/PI;
    f64 x = arr[0] = 0.2*xmax;
    int i;

    for(i=1;i<N;i++){
        x = f(x,lambda);
        arr[i] = x;
    }
#ifdef testmod
    for(i=0;i<61;i++){
        printf("%d\t%lf\n", i, arr[i]);
    }
#endif


    return 0;
}
