#include"HuffmanTree.h"
#include<string.h>

int poww(int x,int e){
	int sum=1,i;
	for(i=0;i<e;i++)
		sum*=x;
	return sum;
}

void Select(HuffmanTree T,int j,int *s1,int *s2){
	int i,a,b;
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
	for(i=n+1;i<=m;i++){					//root is in i=m.
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
		for(i=1;i<=fd->kind;i++){
			if(c==(fd->ch)[i]){		//c is in the ch[]
				(fd->weight)[i]++;
				find=1;
				break;
			}
		}
		if(!find){					//c isn't in D.ch
			i=fd->kind+1;
			(fd->weight)[i]=1;
			(fd->ch)[i]=c;
			fd->kind++;
		}
		fread(&c,sizeof(char),1,fp);
	}
	return 1;
}

int hash(char c){
	return (int)c&255;
}

void move(Dict *D,Hashlist H,HuffmanTree HT){
	int i,j;
	char *p,*q;
	for(i=0;i<257;i++){
		H[i].code[0]='\0';
		H[i].letter=-1;
	}
	j=D->kind;
	for(i=1;i<=j;i++){
		HT[i].c=(D->ch)[i];
	}
	for(i=1;i<=D->kind;i++){
		j=hash((D->ch)[i]);
/*
printf("\t%d\t%d\n",i,j);
*/
		for(p=H[j].code,q=(D->HC)[i];*q!='\0';p++,q++)
			*p=*q;
		*p='\0';
		H[j].letter=(D->ch)[i];
	}
}

char trans(char *q){
	char a=0;
	int i;
	for(i=0;i<8;i++){
		a+=((int)(q[7-i]-'0')*poww(2,i))&255;
	}
	return a;
}

int output(HuffmanTree HT,Hashlist H,int numd,FILE *fp,char *name){
	char queue[8],c,*fc;
	int i,j,last,size,k;
	FILE *fr;
	if((fr=fopen(name,"wb"))==NULL){
		printf("Failed to make file '%s'\n",name);
		exit(0);
	}
	fwrite(HT,sizeof(HTNode),2*numd,fr);
	c=fgetc(fp);
	i=0;
	size=0;
	while(!feof(fp)){
		j=hash(c);
		fc=H[j].code;
//printf("%d %s\n",c,fc);
//getchar();
		for( ;*fc!='\0';fc++){
			queue[i]=*fc;
//getchar();
			if(i==7){
				fputc(trans(queue),fr);
//printf("%d\n",trans(queue));
				size++;
/*				
for(k=0;k<8;k++) printf("%c ",queue[k]);
printf("\n");				
getchar();
*/
			}
			i=(i+1)%8;
		}
		c=fgetc(fp);
	}	
	last=i;
	if(i){
		for( ;i<8;i++)
			queue[i]=(char)0;
		fputc(trans(queue),fr);
	}
	fwrite(&last,sizeof(int),1,fr);
	fwrite(&size,sizeof(int),1,fr);
	fwrite(&numd,sizeof(int),1,fr);
	printf("last: %d\nsize: %d\nnumd: %d\n",last,size,numd);
	fclose(fr);
	printf("Compression finished.\n");
	return 1;
}

int decompress(char *p){
	FILE *fp,*fq;
	if((fp=fopen(p,"rb"))==NULL){
		printf("Failed to open compressed file '%s'.\n",p);
		exit(0);
	}
	if((fq=fopen("test_out","ab"))==NULL){
		printf("Failed to build output file!\n");
		exit(0);
	}
	int last,size,numd,s,i,pht,LAST;
	HuffmanTree HT;
	char queue[9],*fc,c;
	queue[8]='\0';
	fseek(fp,-12L,SEEK_END);
	fread(&last,sizeof(int),1,fp);
	fread(&size,sizeof(int),1,fp);
	fread(&numd,sizeof(int),1,fp);
	printf("read:\nlast: %d\nsize: %d\nnumd: %d\n",last,size,numd);
	getchar();
	HT=(HuffmanTree)malloc(2*numd*sizeof(HTNode));
	if(!HT){
		printf("Failed to generate HuffmanTree!\n");
		exit(0);
	}
	fseek(fp,0,SEEK_SET);
	fread(HT,sizeof(HTNode),2*numd,fp);			//read HuffmanTree(SQList)
	s=i=0;
	LAST=2*numd-1;
	pht=LAST;
/*
for(i=0;i<257;i++)
	printf("\t%d\t%d\t%d\n",i,HT[i].c,HT[i].parent);
fclose(fp);
fclose(fq);
return 1;
*/
	while(s<size || i){
		if(i==0){
			fread(&c,sizeof(char),1,fp);
			s++;
//printf("_%d\n",c);
			for(i=7;i>=0;i--){
				queue[i]=(c&1)+'0';
				c>>=1;
				//
			}
//printf("%s\n",queue);
//getchar();
			i=0;
		}
loop1:
		if(queue[i]=='0'){
			if(HT[pht].lchild){
				pht=HT[pht].lchild;
			}
			else{
				fwrite(&HT[pht].c,sizeof(char),1,fq);			//write into file test_out
printf("%c",HT[pht].c);//getchar();
				pht=LAST;
				goto loop1;
			}
		}
		else if(queue[i]=='1'){
			if(HT[pht].rchild){
				pht=HT[pht].rchild;
			}
			else{
				fwrite(&HT[pht].c,sizeof(char),1,fq);
printf("%c",HT[pht].c);//getchar();
				pht=LAST;
				goto loop1;
			}
		}
		else{
			printf("Error: meet '%d'.\n",c-'0');
			exit(0);
		}
		i=(i+1)%8;
	}
	if(last!=0){
		c=fgetc(fp);
		printf("last: %d\n",last);
		for(i=7;i>=0;i--){
			queue[i]=(c&1)+'0';
			c>>=1;
		}
		i=0;
		while(i<last){
//printf("queue[i]=%c\n",queue[i]);
			if(queue[i]=='0'){
				if(HT[pht].lchild){
					pht=HT[pht].lchild;
//printf("%d--",pht);
				}
				else{
					fwrite(&HT[pht].c,sizeof(char),1,fq);
					pht=LAST;
//printf("^\n");
					continue;
				}
			}
			else if(queue[i]='1'){
				if(HT[pht].rchild){
					pht=HT[pht].rchild;
//printf("%d--",pht);
				}
				else{
					fwrite(&HT[pht].c,sizeof(char),1,fq);
					pht=LAST;
//printf("^\n");
					continue;
				}
			}
			i++;
		}		
	}
	fclose(fp);
	fclose(fq);
	printf("Decompression finished.\n");
	return 1;
}

int main(){
	FILE *fp;
	if((fp=fopen("testtext","rb"))==NULL){
		printf("Can't open this file!\n");
		exit(0);
	}
printf("------\n%p\n",fp);
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
	D.kind=0;
	stat(fp,&D);
printf("1 %-d	%p\n",D.kind,D.HC+1);
	HuffmanCoding(&HT,&D.HC,D.weight,D.kind);
int i;
printf("2\n");
//for(i=1;i<257;i++) printf("\t %d\t%s\n",(D.ch)[i],(D.HC)[i]);
printf("3\n");
	move(&D,H,HT);
//for(i=0;i<257;i++)
//	printf("\t%d\t%s\n",255&H[i].letter,H[i].code);
printf("HT: %p\nH : %p\nfp: %p\n",HT,H,fp);
	fseek(fp,0,SEEK_SET);					//let fp move to the head of file
printf("4\n");
	char *NAME="testfile.hf";
	output(HT,H,D.kind,fp,NAME);
	fclose(fp);
	decompress(NAME);
	return 0;
}
