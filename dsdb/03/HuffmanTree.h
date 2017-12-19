#pragma once
#include<stdio.h>
#include<stdlib.h>

typedef char *String;
typedef String *HuffmanCode;

typedef struct {
	int weight;
	int parent,lchild,rchild;
	char c;
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
	int kind;
}Dict;

typedef struct {
	char code[15];		//mystery Orz
	char letter;
}HashDict,*Hashlist;
