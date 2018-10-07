#include "prelude.h"

int main(){
    srand(time(0));
    int i;
    for(i=1;i<=40;i++){
        printf("%4d\t\t", rand()%2000);
        if(i%8 eqs 0){
            printf("\n");
        }
    }
    return 0;
}