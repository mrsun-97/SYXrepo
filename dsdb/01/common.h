#pragma once
#include<stdio.h>
#include<stdlib.h>
typedef struct LNode{
    double coef;
    int expn;
    struct LNode *next;
}LNode,*Linklist;

