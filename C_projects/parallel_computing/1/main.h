#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define eqs ==

typedef int data;

struct Vec {
    data *pt;
    unsigned int len;
};

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
        a[i] = tmp;
        return i;
    }
}

//[start, end] 闭区间
void quick_sort(data *p, int start, int end){
    if(start >= end) return;
    int k = _sort(p, start, end);
    quick_sort(p, start, k-1);
    quick_sort(p, k+1, end);
}