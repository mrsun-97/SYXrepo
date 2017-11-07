#pragma once
#include<stdio.h>

typedef char ** HuffmanCode;

typedef struct {
	unsigned int weight;
	unsigned int parent,lchild,rchild;
}HTNode,*HuffmanTree;
