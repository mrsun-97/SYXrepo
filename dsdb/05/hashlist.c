#include <stdio.h>
#include <stdlib.h>
//#define run

typedef struct LNode{
	int data;
	struct LNode *next;
}LNode,*Linklist;

static int D[12]={19,14,23,1,68,20,84,27,55,11,10,79};
static int HT1[13];
static Linklist HT2[13];

int hash_mod13(int x){
	return x%13;
}

int insert_HT1(int a){
	if(a<=0) return 0;
	int i,h=0;
	for(i=0;i<13;i++){
		if(HT1[i]==0 || HT1[i]==a){
			h=1;			//list isn't full
			break;
		}
	}
	if(h==0){				//list is full
		printf("HT1 is full!\n");
		return -1;
	}
	int sum=0;
	if(1){					//only once
		h=hash_mod13(a);
		while(sum++,HT1[h]!=0 && HT1[h]!=a){
			h=hash_mod13(h+1);
		}
		if(HT1[h]==a){
			printf("%d already exists.\n",a);
			sum=0;
		}
		else 
			HT1[h]=a;
	}
	return sum;
}

int make_HT1(void){
	int i,sl=0;
	float asl;
	for(i=0;i<13;i++) HT1[i]=0;		//clean
	for(i=0;i<12;i++){
		sl+=insert_HT1(D[i]);
	}
	asl=(float)sl/i;
	printf("succeed asl=%.2f\n",asl);
	return 1;
}

int search_HT1(int a){		//if can't find a, then sum>0, else sum<0
	if(a<=0){
		printf("Invalid number!\n");
		return 0;
	}
	int i,h;
	int sum=0;
	h=i=hash_mod13(a);
	while(sum++,HT1[i]!=0 && HT1[i]!=a){
		i=hash_mod13(i+1);
		if(i==h) break;		
	}
	if(HT1[i]==a){
		printf("  HT1[%d]=%d\n",i,a);
		return -sum;		//let sum<0
	}
	else{
		printf("  %d isn't in HT1.\n",a);
		return sum;
	}
}

int insert_HT2(int a){
	int i,h;
	int sum=1;
	h=hash_mod13(a);
	Linklist p=HT2[h],q;
	if(p){
		while(sum++,p->data!=a && p->next!=NULL) p=p->next;
		if(p->data==a) return 0;	
		q=(Linklist)malloc(sizeof(LNode));
		if(!q){
			printf("overflowed!\n");
			exit(0);
		}
		q->data=a;
		q->next=NULL;
		p->next=q;		
	}
	else{
		p=HT2[h]=(Linklist)malloc(sizeof(LNode));
		if(!p){
			printf("overflowed!\n");
			exit(0);
		}
		p->data=a;
		p->next=NULL;		
	}
	return sum;
}

int make_HT2(void){
	int i,sl=0;
	float asl;
	for(i=0;i<13;i++) HT2[i]=NULL;
	for(i=0;i<12;i++){
		sl+=insert_HT2(D[i]);
	}
	asl=(float)sl/i;
	printf("succeed asl=%.2f\n",asl);
	return 1;
}

int search_HT2(int a){
	if(a<=0){
		printf("Invalid number!\n");
		return 0;
	}
	int i,h;
	int sum=1;
	Linklist p;
	h=hash_mod13(a);
	p=HT2[h];
	if(p){
		while(sum++,p->data!=a && p->next!=NULL) p=p->next;
		if(p->data==a){
			printf("  HT[%d]=%d\n",h,p->data);
			return -sum;
		}
		else{
			printf("  %d isn't in HT2.\n",a);
			return sum;
		}
	}
	else{
		printf("  %d isn't in HT2.\n",a);
		return sum;
	}
}

float FASL_HT1(void){
	int a=1000,i;
	int sl=0;
	float asl;
	for(i=0;i<13;i++){
		sl+=search_HT1(a+i);
	}
	asl=(float)sl/13;
	return asl;
}

float FASL_HT2(void){
	int a=1000,i;
	int sl=0;
	float asl;
	for(i=0;i<13;i++){
		sl+=search_HT2(a+i);
	}
	asl=(float)sl/13;
	return asl;
}

void print_HT1(void){
	int i,a;
	for(i=0;i<13;i++){
		printf("\t%d",i);
	}
	printf("\n");
	for(i=0;i<13;i++){
		a=HT1[i];
		if(a)
			printf("\t%d",a);
		else
			printf("\t%c",'-');
	}
	printf("\n");
}

void print_HT2(void){
	int i,a;
	Linklist p;
	for(i=0;i<13;i++){
		printf(" %d -->",i);
		p=HT2[i];
		if(p){
			do{
				printf(" %d -->",p->data);
			}while((p=p->next)!=NULL);
		}
		printf(" (null)\n");
	}
}

void delete_HT1(int a){
	if(a<=0){
		printf("Invalid number!\n");
		return;
	}
	int i,j,h;
	int sum=0;
	h=i=hash_mod13(a);
	while(sum++,HT1[i]!=0 && HT1[i]!=a){
		i=hash_mod13(i+1);
		if(i==h) break;		
	}
	if(HT1[i]==a){
		printf("  HT1[%d]=%d\n",i,a);
		HT1[i]=0;	
		for(i=i+1,j=0;j<13;j++){
			h=HT1[j];
			HT1[j]=0;
			insert_HT1(h);
		}
	}
	else{
		printf("  %d isn't in HT1.\n",a);
	}
}

void main(){
	int a=1,k;
	printf("--> ");
#ifdef run
	for(k=0;k<12;k++){
		scanf("%d",&D[k]);getchar();
	}
#endif
	make_HT1();
	print_HT1();
printf("1\n");
	while(a!=0){
		printf("Search: ");
		scanf("%d",&a);getchar();
		k=search_HT1(a);
		if(k!=0)
			printf("times: %d\n",k>0?k:-k);
	}
	print_HT1();

	make_HT2();
	print_HT2();
	a=1;
	while(a!=0){
		printf("Search: ");
		scanf("%d",&a);getchar();
		k=search_HT2(a);
		if(k!=0)
			printf("times: %d\n",k>0?k:-k);
	}
	printf("ASL when failed to find x: %.2f\n",FASL_HT1());
	printf("ASL when failed to find x: %.2f\n",FASL_HT2());
	printf("Which do you want to delete?\n-->");
	scanf("%d",&a);getchar();
	delete_HT1(a);
	print_HT1();
	return;
}
