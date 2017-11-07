#pragma once
#include<stdio.h>
#include<stdlib.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 20

typedef char Stype;

typedef struct {
	Stype *base;
	Stype *top;
	int stacksize;
}SQStack;


