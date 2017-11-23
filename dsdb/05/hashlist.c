#include <stdio.h>

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
	int i,h=0;
	for(i=0;i<13;i++){
		if(HT1[i]==NULL || HT1[i]==a){
			h=1;			//list isn't full
			break;
		}
	}
	if(h==0){				//list is full
		printf("HT1 is full!\n");
		return -1;
	}
	int sum=0;
	while(i=-1,i++){		//only once
		h=hash_mod13(a);
		while(sum++,HT1[h]!=0 && HT1[h]!=a)
			h=hash_mod13(h+1);
		if(HT1[h]==a)
			sum=0;
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
	while(sum++,HT1[i]!=0 && HT[i]!=a){
		i=hash_mod13(i+1);
		if(i==h) break;		
	}
	if(HT[i]==a){
		printf("  HT1[%d]=%d\n",i,a);
		return -sum;		//let sum<0
	}
	else{
		printf("  %d isn't in HT1.\n");
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
			printf("  %d isn't in HT2.\n");
			return sum;
		}
	}
	else{
		printf("  %d isn't in HT2.\n")
		return sum;
	}
}

float FASL_HT1(void){
	int a=1000;
	int sl=0;
	float asl;
	for(i=0;i<13;i++){
		sl+=search_HT1(a+i);
	}
	asl=(float)sl/13;
	return asl;
}

float FASL_HT2(void){
	int a=1000;
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
		if(p){
			do{
				printf(" %d -->",p->data);
			}while(p->next!=NULL);
		}
		printf(" (null)\n");
}

void delete_HT1(int a){
	if(a<=0){
		printf("Invalid number!\n");
		return 0;
	}
	int i,j,h;
	int sum=0;
	h=i=hash_mod13(a);
	while(sum++,HT1[i]!=0 && HT[i]!=a){
		i=hash_mod13(i+1);
		if(i==h) break;		
	}
	if(HT[i]==a){
		printf("  HT1[%d]=%d\n",i,a);
		HT[i]=0;	
		while(j=i,i=hash_mod13(i+1),HT1[i]!=0){
			if(hash_mod13(HT1[i])!=i){
				HT1[j]=HT1[i];
				HT1[i]=0;
			}
		}
	}
	else{
		printf("  %d isn't in HT1.\n");
		return sum;
	}
}

void main(){
	int a=1,k;
	make_HT1();
	print_HT1();	
	while(a!=0){
		scanf("%d",&a);getchar();
		k=search_HT1(a);
		if(k!=0)
			printf("times: %d\n",k>0?k:-k);
	}
	make_HT2();
	print_HT2();
	while(a!=0){
		scanf("%d",&a);getchar();
		k=search_HT2(a);
		if(k!=0)
			printf("times: %d\n",k>0?k:-k);
	}
	printf("ASL when failed to find x: %f\n",FASL_HT1());
	printf("ASL when failed to find x: %f\n",FASL_HT2());
}
