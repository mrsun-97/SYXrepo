#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ture true

typedef long double  f128;
typedef double  f64;
typedef float  f32;

typedef struct node1{
    f128 data;
    struct node1 *next;
}NODE, * HEAD;
/*
typedef struct node2{
    f128 l;
    HEAD x;
    int t;
    struct node2 *next;
}BLOCK, *LINK;
*/
const f128 PI = 3.14159265358979323846;
//const f128 DELTA = 1e-14;

HEAD init(void){
    HEAD p;
    p = (HEAD)malloc(sizeof(NODE));
    if(p == NULL){
        printf("UdfError: init(): malloc() failed\n");
        exit(1);
    }
    p->data = 0.0;
    p->next = NULL;
    return p;
}

int push(HEAD Q, f128 e){
    if(Q == NULL){
        printf("UdfError: push(): invalid pointer \"HEAD\"\n");
        exit(1);
    }
    HEAD p;
    p = (HEAD)malloc(sizeof(NODE));
    if(p == NULL){
        printf("UdfError: push(): malloc() failed\n");
        exit(1);
    }
    p->data = e;
    HEAD q;
    q = Q->next;
    Q->next = p;
    p->next = q;
    return 1;
}

int in_set(HEAD Q, f128 e, f128 DELTA){
    if(Q == NULL){
        printf("UdfError: in_set(): invalid pointer \"HEAD\"\n");
        exit(1);
    }
    int flag = 0;
    HEAD p = Q->next;
    //if(p==NULL) return 0;
    while(p!=NULL){
        if(fabsl(p->data-e)<DELTA){
            flag = 1;
            break;
        }
        p = p->next;
    }
    return flag;
}

int length(HEAD Q){
    if(Q == NULL){
        printf("UdfError: length(): invalid pointer \"HEAD\"\n");
        exit(1);
    }
    HEAD p = Q->next; 
    if(p==NULL) return 0;

    //int count = 0;
    int i = 1;
    while(i < 4321){
        p = p->next;
        if(p == NULL) return i;
        i++;
    }
    return -1;
}

int drop(HEAD *P){
    HEAD Q = *P;
    if(Q!=NULL){
        HEAD p = Q, q;
        while(p!=NULL){
            q = p->next;
            free(p);
            p = q;
        }
        *P = NULL;
        return 1;
    }
    return 0;
}

int output(HEAD Q, FILE *fp){
    if(Q==NULL || fp==NULL){
        printf("UdfError: output(): invalid pointer\n");
        exit(1);
    }
    HEAD q = Q-> next;
    while(q!=NULL){
        fprintf(fp, "\t%.12llf", q->data);
        q = q->next;
    }
    return 1;
}

f128 x_max(f128 lambda){
    f128 t = lambda * PI;
    if(t < 1.0)
        return NAN;
    return sqrtl( 6 * ( 1 - 1/t ))/PI;
}

f128 f(f128 x, f128 lambda){
    return lambda * sinl(PI*x);
}

typedef struct
{

    f128 re;
    f128 im;
    int n;

} COMPLEX;
//定义 COMPLEX.init()
COMPLEX complex(f128 Re, f128 Im){
    COMPLEX Z;
    Z.re = Re;
    Z.im = Im;
    Z.n = 0;
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
