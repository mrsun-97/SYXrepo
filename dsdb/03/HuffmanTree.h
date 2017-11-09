#pragma once
#include<stdio.h>

typedef char *String;
typedef String *HuffmanCode;

typedef struct {
	int weight;
	int parent,lchild,rchild;
}HTNode,*HuffmanTree;

/*
typedef struct LNode{
	char ch;
	int times;
	struct LNode *next;
}LNode,*Linklist;
*/

typedef struct {
	HuffmanCode HC;
	int *weight;
	char *ch;
	int size;
}Dict;

typedef struct {
	HuffmanCode HC;
	char *ch
}Hashlist;
