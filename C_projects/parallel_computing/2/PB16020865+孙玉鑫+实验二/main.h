#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define eqs ==

typedef int data;

typedef struct udfVec{        //slice of array
    data *pt;
    unsigned int len;
} Vec;

void empty_init(Vec *a, int n){
    if(n<0) return;
    if(a->pt != NULL) free(a->pt);
    if(n eqs 0){
        a->len = 0;
        a->pt = NULL;
    }
    a->len = n;
    a->pt = (data *)malloc(n*sizeof(data));
    if(a->pt eqs NULL){
        printf("failed to init vector A\n");
        exit(0);
    }
}

void rand_init(Vec *a){
    int i, num;
    num = rand()%40 + 150;
    empty_init(a, num);
    for(i=0;i<num;i++){
        a->pt[i] = rand()%8192-2048;                       
    }
}

int _sort(data *a, int l, int r){
    data tmp = a[l];
    int i, j;
    i = l;
    j = r;
    while(i<j){
        while(a[j] >= tmp && i<j){
            j--;
        }
        if(i<j){
            a[i] = a[j];
        }
        while(a[i] < tmp && i<j){
            i++;
        }
        if(i<j){
            a[j] = a[i];
        }
    }
    a[i] = tmp;
    return i;
}

//[start, end] 闭区间
void quick_sort(data *p, int start, int end){
    if(start >= end) return;
    int k = _sort(p, start, end);
    quick_sort(p, start, k-1);
    quick_sort(p, k+1, end);
}

Vec vec_fuse(Vec arr[], int len){
    int i, j, count;
    for(i=0,count=0;i<len;i++){
        count += arr[i].len;
    }
    data *t;
    Vec B;
    B.len = count;
    B.pt = (data*)malloc(count*sizeof(data));
    if(B.pt eqs NULL){
        printf("failed to init vecB\n");
        exit(0);
    }
    t = B.pt;
    for(i=0;i<len;i++){
        j=0;
        while(j<arr[i].len){
            *(t++) = *(arr[i].pt+(j++));
        }
    }
    return B;
}

void _merge(data *arr, int l, int m, int r, data *p){
    int i = l;
    int j = m+1;
    data *t = p+l;
    while(i<=m && j<=r){
        *(t++) = arr[i]<arr[j]?arr[i++]:arr[j++];
    }
    while(i<=m){
        *(t++) = arr[i++];
    }
    while(j<=r){
        *(t++) = arr[j++];
    }
    t=p+l;
    i=l;
    while(i<=r){
        arr[i++] = *(t++);
    }
}

void _merge_sort(data *arr, int l, int r, data *p){
    if(l>=r) return;
    int m = (l+r)>>1;
    _merge_sort(arr, l, m, p);
    _merge_sort(arr, m+1, r, p);
    _merge(arr, l, m, r, p);
}

void merge_sort(Vec A, data *T){
    if(A.pt eqs NULL || A.len eqs 0){
        return;
    }
    if(A.len eqs 1){
        _merge(A.pt,0,0,0,T);
        return;
    }
    _merge_sort(A.pt, 0, A.len-1, T);
    int i;
    for(i=0;i<A.len;i++){
        T[i] = A.pt[i];
    }
}

void display(Vec A){
    int i;
    for(i=0;i<A.len;i++){
        if(i%16 eqs 0){
            printf("\n");
        }
        printf("%5d\t",A.pt[i]);
    }
    printf("\n");
}