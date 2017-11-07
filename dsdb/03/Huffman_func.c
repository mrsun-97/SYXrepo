#include"HuffmanTree.h"
#include<string.h>

void select(HuffmanTree T,int j,int *s1,int *s2){
	int i,a,b;
	//a=(T[1].weight>T[2].weight)?T[1].weight:T[2].weight;
	//b=(T[1].weight>T[2].weight)?T[2].weight:T[1].weight;
	//*s1=(T[1].weight>T[2].weight)?1:2;
	//*s2=(T[1].weight>T[2].weight)?2:1;
	a=b=2e9;
	*s1=*s2=0;
	for(i=1,i<=j;i++){			//a>=b
		if(T[i].parent==0){
			if(T[i].weight<b){
				a=b;
				b=T[i].weight;
				*s1=*s2;
				*s2=i;
			}else if(T[i].weight<a){
				a=T[i].weight;
				*s1=i;
			}
		}
		else continue;
	}
}

void HuffmanCoding(HuffmanTree *HT,HuffmanCode *HC,int *w,int n){
	if(n<=1) return;
	int m=2*n-1,i,s1,s2;
	HuffmanTree p;
	*HT=(HuffmanTree)malloc((m+1)sizeof(HTNode));
	for(p=*HT,i=1;i<=n;i++,p++,w++) *p={*w,0,0,0};
	for( ;i<=m;i++,p++) *p={0,0,0,0};
	for(i=n+1;i<=m;i++){
		select(*HT,i-1,&s1,&s2);
		p=*HT;
		p[s1].parent=i;	p[s2].parent=i;
		p[i].lchild=s1;	p[i].rchild=s2;
		p[i].weight=p[s1].weight+p[s2].weight;
	}
	//workout the huffmancode
	char *cd;
	int start,c,f;
	*HC=(HuffmanCode)malloc((n+1)*sizeof(char *));
	cd=(char *)malloc(n*sizeof(char));
	cd[n-1]='\0';
	for(i=1;i<=n;i++){
		start=n-1;
		for(c=i,f=p[i].parent;f!=0;c=f,f=p[f].parent)
			if(p[f].lchild==c) cd[--start]='0';
			else cd[--start]='1';
		p[i]=(char *)malloc((n-start)*sizeof(char));
		strcpy(p[i],&cd[start]);
	}
	free(cd);
}

