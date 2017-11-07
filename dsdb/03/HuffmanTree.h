#pragma once

typedef char **huffmanCode;

typedef struct {
	unsigned int weight;
	unsigned int parent,lchild,rchild;
}HTNode,*HuffmanTree;;

