#include"HuffmanTree.h"
#include<string.h>

void Select(HuffmanTree T,int j,int *s1,int *s2){
	int i,a,b;
	//a=(T[1].weight>T[2].weight)?T[1].weight:T[2].weight;
	//b=(T[1].weight>T[2].weight)?T[2].weight:T[1].weight;
	//*s1=(T[1].weight>T[2].weight)?1:2;
	//*s2=(T[1].weight>T[2].weight)?2:1;
	a=b=2e9;
	*s1=*s2=0;
	for(i=1;i<=j;i++){			//a>=b
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
	if(n<=1){
		printf("Too few data, nothing to do.\n");
		return;
	}
	int m=2*n-1,i,s1,s2;
	HuffmanTree p;
	*HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));
	if(!*HT){
		printf("Failed to generate Huffmantree!\n");
		exit(0);
	}
	for(p=*HT,i=1;i<=n;i++,p++,w++){
		p->weight=*w;			//w[]
		p->lchild=p->rchild=p->parent=0;
	} 
	for( ;i<=m;i++,p++){
		p->weight=p->lchild=p->rchild=p->parent=0;
	}
	for(i=n+1;i<=m;i++){
		Select(*HT,i-1,&s1,&s2);
		p=*HT;
		p[s1].parent=i;	p[s2].parent=i;
		p[i].lchild=s1;	p[i].rchild=s2;
		p[i].weight=p[s1].weight+p[s2].weight;
	}
	//workout the huffmancode
	char *cd;
	int start,c,f;
	*HC=(HuffmanCode)malloc((n+1)*sizeof(char *));
	if(!*HC){
		printf("Failed to generate HC list!\n");
		exit(0);
	}
	cd=(char *)malloc(n*sizeof(char));
	cd[n-1]='\0';
	for(i=1;i<=n;i++){
		start=n-1;
		for(c=i,f=p[i].parent;f!=0;c=f,f=p[f].parent)
			if(p[f].lchild==c) cd[--start]='0';
			else cd[--start]='1';
		(*HC)[i]=(char *)malloc((n-start)*sizeof(char));
		strcpy((*HC)[i],&cd[start]);
	}
	free(cd);
	printf("HuffmanCoding finished\n");
}

int stat(FILE *fp,Dict *fd){
	char c,*d;
	int i,j,find;
	fread(&c,sizeof(char),1,fp);
	while(!feof(fp)){
		find=0;
		for(i=1;i<=fd->size;i++){
			if(c==(fd->ch)[i]){		//c is in the ch[]
				(fd->weight)[i]++;
				find=1;
				break;
			}
		}
		if(!find){					//c isn't in D.ch
			i=fd->size+1;
			(fd->weight)[i]=1;
			(fd->ch)[i]=c;
			fd->size++;
		}
		fread(&c,sizeof(char),1,fp);
	}
	return 1;
}

int hash(char c){
	return (int)(c);
}

void move(Dict *D,Hashlist H){
	int i,j;
	for(i=0;i<257;i++){
		H[i].code[0]='\0';
		H[i].letter=-1;
	}
	for(i=1;i<=D->size;i++){
		j=hash((D->ch)[i]);
		strcpy(H[j].code,(D->HC)[i]);
		H[j].letter=(D->ch)[i];
	}
}

char trans(char *q){
	char a;
	a=(char)(128*q[0]+64*q[1]+32*q[2]+16*q[3]+8*q[4]+4*q[5]+2*q[6]+q[7]);
	return a;
}

int output(Hashlist H,FILE *fp,char *name){
	char queue[8],c,*fc;
	int i,j,last,size;
	FILE *fr;
	if((fr=fopen(name,"wb"))==NULL){
		printf("Failed to make file '%s'\n",name);
		exit(0);
	}
printf("a\n");
	for(i=0;i<257;i++){
		fwrite(H+i,sizeof(HashDict),1,fr);
	}
	c=fgetc(fp);
	i=0;
	size=0;
	while(!feof(fp)){
		j=hash(c);
		fc=H[j].code;
		for( ;*fc!='\0';fc++){
			queue[i]=(char)(*fc-'0');
			if(i==7){
				fputc(trans(queue),fr);
				size++;
			}
			i=(i+1)%8;
		}
		c=fgetc(fp);
	}	
	last=i;
printf("last: %d\n",last);
	if(i){
		//fputc((char)0,fp);
		for( ;i<8;i++)
			queue[i]=(char)0;
		fputc(trans(queue),fr);
	}
	fwrite(&last,sizeof(int),1,fr);
	fwrite(&size,sizeof(int),1,fr);
	fclose(fr);
	return 1;
}

int main(){
	FILE *fp;
	if((fp=fopen("testtext","rb"))==NULL){
		printf("Can't open this file!\n");
		exit(0);
	}
	else printf("%p\n",fp);
	HuffmanTree HT;
	HuffmanCode HC;
	Dict D;
	Hashlist H;
	D.ch=(char *)malloc(257*sizeof(char));
	H=(Hashlist)malloc(257*sizeof(HashDict));
	if(!D.ch || !H){
		printf("Failed to generate array D.ch!\n");
		exit(0);
	}
	D.weight=(int *)malloc(257*sizeof(int));
	if(!D.weight){
		printf("Failed to generate array D.weight!\n");
		exit(0);
	}
	D.HC=NULL;
	D.size=0;
	stat(fp,&D);
printf("1 %d	%p\n",D.size,D.HC+1);
	HuffmanCoding(&HT,&D.HC,D.weight,D.size);
printf("2\n");
	move(&D,H);
printf("3\n");
	fseek(fp,0,SEEK_SET);					//let fp move to the head of file
printf("4\n");
	output(H,fp,"testfile.hf");
printf("5\n");
	fclose(fp);
	//Decompress("testfile.hf");
	return 0;
}
