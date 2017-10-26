#include<time.h>
#include"common.h"
#define ARRLEN 40
#define MIN 1e-6

double poww(double x,int n){
    int i;
    if(n>1){
        for(i=0;i<n-1;i++)
            x*=x;
    }else if(n==0){
        x=1;
    }else if(n<0){
        exit(0);
    }
    return x;
}

void ListArr(Linklist *A){
    int i;
    printf("These mumbers are not empty:\n\t");
    for(i=0;i<10;i++)
        if(A[i]!=NULL)
            printf("%d  ",i);
    printf("end\n");
}


int order(Linklist Q){
    if(!Q || !Q->next){
        printf("order:empty list\n");
        return 0;
    }
    int i=0,j,m,done=0;
    Linklist p=Q,q=Q->next;
    while(q->next){
        if(q->expn<=q->next->expn || abs(q->coef)<MIN){
            done=1;
            break;
        }
        q=q->next;
    }
    if(!done){
        printf("order:Nothing more to do.\n");
        return 1;
    }
//printf("test_order_1\n");
    Linklist arr[2*ARRLEN];
    while(i<2*ARRLEN)
        arr[i++]=NULL;
    i=0;
    while(p->next){                 //put in array
        arr[i]=p->next;
        p=p->next;
        i++;
    }
    m=i;                            //mark the end
    for(j=0;j<m;j++){               //sort
        for(done=i=0;i<m-1-j;i++)
            if(arr[i]->expn<arr[i+1]->expn){
                q=arr[i];
                arr[i]=arr[i+1];
                arr[i+1]=q;
                done=1;
            }
        if(!done) break;
    }
    for((i=0,j=1);j<m;j++){         //combine similar terms
        if(arr[i]->expn==arr[j]->expn){
            arr[i]->coef+=arr[j]->coef;
            free(arr[j]);
            arr[j]=NULL;
        }
        else{
            if(abs(arr[i]->coef<MIN)){
                free(arr[i]);
                arr[i]=NULL;
            }
            i=j;
        }
    }

    //feed back data
    p=Q;
    for(i=0;i<m;i++){
        if(arr[i]){
            p->next=arr[i];
            p=p->next;
        }
        p->next=NULL;
    }
    if(!Q->next){                   //if it's empty, change it to zero polynomial.
        q=(Linklist)malloc(sizeof(LNode));
        if(!q) exit(-1);
        Q->next=q;
        q->coef=0;
        q->expn=0;
        q->next=NULL;
    }
    printf("order:finished\n");
    return 1;
}

int RandCreatPolyn(Linklist *p){     //(&a[n],m)
    if(*p){
        printf("List is not empty!\n");
        exit(0);
    }
    srand((unsigned int)time(NULL));
    int i,j,m;
    printf("input generate number: ");
    scanf("%d",&m);
    Linklist q,s;   
    q=(Linklist)malloc(sizeof(LNode));
    if(!q) exit(-1);
    q->next=NULL;
    q->expn=-1;
    q->coef=0;
    *p=q;
    for(i=0;i<m;i++){
        s=(Linklist)malloc(sizeof(LNode));
        if(!s) exit(-1);
        q->next=s;
        s->coef=(double)rand()/200000000;
        s->expn=(unsigned int)rand()%21;
        s->next=NULL;
        q=s;
    }
    order(*p);
    printf("RandCreate:finished.\n\n");
    return 1;
}





int CreatPolyn(Linklist *p,int m){     //(&a[n],m)
    if(m>ARRLEN || m<0){
        printf("The number is not proper.\n");
        exit(0);
    }
    if(*p){
        printf("List is not empty!\n");
        exit(0);
    }
    int i,j;
    Linklist q,s;   
    q=(Linklist)malloc(sizeof(LNode));
    if(!q) exit(-1);
    q->next=NULL;
    q->expn=-1;
    q->coef=0;
    *p=q;
    if(m==0){
        q=(Linklist)malloc(sizeof(LNode));
        if(!q) exit(-1);
        q->expn=0;
        q->coef=0;
        q->next=NULL;
        (*p)->next=q;
        printf("Generated zero polyn.\n");
        return 1;
    }
    double coe=0;
    int ex=0;
    for(i=0;i<m;i++){
        printf("(%d/%d finished) coef & expn: ",i,m);
        scanf("%lf %d",&coe,&ex);getchar();
        if(ex<0){
            printf("error: expn<0,try it again!\n");
            i--;
            continue;
        }
        s=(Linklist)malloc(sizeof(LNode));
        if(!s) exit(-1);
        q->next=s;
        s->coef=coe;
        s->expn=ex;
        s->next=NULL;
        q=s;
    }
printf("Into order\n");
    order(*p);
    printf("Create:finished.\n");
    return 1;
}


int PrintPolyn(Linklist p){
    if(!p || !p->next){
        printf("List is empty!\n");
        exit(0);
    }
    if(p=p->next){                          //NO.1 exists
        if(p->expn!=0){
            if(p->coef>=0)
                printf(">>>\t%.3gx^%d ",p->coef,p->expn);
            else
                printf(">>>\t-%.3gx^%d ",-p->coef,p->expn);
        }else
            printf(">>>\t%+.5g ",p->coef);
    }/*else{
        printf("Empty list!\n");
    }*/
    int n=1;
    while((p=p->next)!=NULL){
        //p=p->next;
        n++;
        if(p->expn!=0){
            if(p->coef>=0)
                printf("+ %.3gx^%d ",p->coef,p->expn);      // example: 5.2x^1 + 0.09x^2 - 1x^3 ...
            else
                printf("- %.3gx^%d ",-p->coef,p->expn);
        }else
            printf("%+.5g ",p->coef);
        if(n%6==0) printf("\n>>>\t");
     }
    printf("#\n\n");
    return 1;
} 


int CopyPolyn(Linklist m ,Linklist *n){
    if(!m){
        printf("Empty list!\n");
        exit(0);
    }
    if(*n){
        printf("b already exist.\n");
        exit(0);
    }
    Linklist p,q=m;
    if(1){
        p=(Linklist)malloc(sizeof(LNode));
        if(!p){
            printf("Overflowed!\n");
            exit(-1);
        }
		*n=p;
        p->coef=q->coef;
        p->expn=q->expn;
    }
    while(q->next){ 
        q=q->next;
        p->next=(Linklist)malloc(sizeof(LNode));
        if(!p->next){
            printf("Overflowed!\n");
            exit(-1);
        }
        p=p->next;
        p->coef=q->coef;
        p->expn=q->expn;
    }
    p->next=NULL;
    printf("Finished.\n");
    return 1;
}


int AddPolyn(Linklist *m,Linklist *n){
    if(!*m || !*n){
        printf("Empty lists.\n");
        exit(0);
    }
    Linklist p;
    p=*m;
    while(p->next!=NULL)
        p=p->next;
    p->next=(*n)->next;
    free(*n);
    *n=NULL;
    order(*m);
    return PrintPolyn(*m);
}


int SubtractPolyn(Linklist *A,Linklist *B){
    if(!*A || !*B){
        printf("Empty lists.\n");
        exit(0);
    }
    Linklist p;
    p=*B;
    while(p=p->next)
        p->coef=-p->coef;
    
    AddPolyn(A,B);
    return 1;
}


double Value(Linklist Q,double x){
    if(!Q || !Q->next){
        printf("Empty list!\n");
        exit(0);
    }
    double e=0;
    while(Q->next){
        Q=Q->next;
        e+=Q->coef*poww(x,Q->expn);
    }
    printf("The value is : %.3g\n",e);
    return e;
}


int DestoryPolyn(Linklist Q,int n){                 //delete only one term
    if(!Q || !Q->next){
        printf("Empty list!\n");
        exit(0);
    }
    Linklist p=Q,s;
    while(p->next && p->next->expn!=n) p=p->next;
    if(!p->next){
        printf("The term you want doesn't exist.\n");
        return 0;
    }else{
        s=p->next;
        printf("Delete %.3gx^%d\n",s->coef,n);
        if(s==Q->next && s->next==NULL){
            s->expn=0;
            s->coef=0;
            return 1;
        }else{
            p->next=s->next;
            free(s);
        }
    }
    return PrintPolyn(Q);
}


int CleanPolyn(Linklist *A){
    if(!*A) exit(0);
    Linklist q=*A,p=*A;
    do {
        p=p->next;
        free(q);
        q=p;
    }while(p!=NULL);
    *A=NULL;
    printf("Finished.\n");
    return 1;
}


int Insert(Linklist *A){
    double coe;
    int ex;
    Linklist q;
    printf("Insert expression, coef&exp: ");
    scanf("%lf %d",&coe,&ex);
    if(ex<0){
        printf("Your exponent is not proper!\n");
        exit(0);
    }
    q=(Linklist)malloc(sizeof(LNode));
    if(!q){
        printf("Overflow!\n");
        exit(0);
    }
    q->expn=ex;
    q->coef=coe;
    q->next=(*A)->next;
    (*A)->next=q;
    order(*A);
    return PrintPolyn(*A);
}


int Delete(Linklist *A){
    printf("  pass\n");
    return 1;
}


int Change(Linklist *A){
    if(!(*A) || !(*A)->next){
        printf("Empty list!\n");
        exit(0);
    }
    int ex,ex_old;
    double coe;
    Linklist p;
    printf("input the term's exp you want to change:");
    scanf("%d",&ex_old);getchar();
    p=*A;
    while(p=p->next){
        if(p->expn==ex_old) break;
    }
    if(!p){
        printf("this term doesn't exist.\n");
        return 0;
    }

    printf("new value, exp&coef:");
    scanf("%d %lf",&ex,&coe);getchar();
    if(ex<0){
        printf("Improper exponent!\n");
        exit(0);
    }
    p->coef=coe;
    p->expn=ex;
    order(*A);
    return PrintPolyn(*A);
}


int DiffPolyn(Linklist Q,int n){
	if(!Q || !Q->next){
		printf("Empty list!\n");
		exit(0);
	}
	PrintPolyn(Q);
	if(n<0){
		printf("please check the number\n");
		exit(0);
	}else if(n==0) return 1;

	Linklist p;
	while(n!=0){
		p=Q;
		while(p=p->next){
			p->coef*=p->expn;
			p->expn--;
		}
		n--;
	
	}	
	p=Q;
	//find the first one with 'expn<0'
	while(p->next && p->next->expn>=0) p=p->next;
	CleanPolyn(&(p->next));			//cleanpolyn() deletes the items which have negative exponent.print 'finished'.	
	return PrintPolyn(Q);
}


int UDFIntegral(Linklist Q){
	if(!Q || !Q->next){
		printf("Empty list!\n");
		exit(0);
	}
	Linklist p=Q;
	while(p=p->next){
		p->expn++;
		p->coef/=p->expn;
	}
	PrintPolyn(Q);
	return 1;
}


int DEFIntegral(Linklist Q,Linklist *A){
	if(!Q || !Q->next){
		printf("Empty list\n");
		exit(0);
	}
	double bottom,top,outcome;
	printf("input the range of integration bottom&top: ");
	scanf("%lf %lf",&bottom,&top);getchar();	
	CopyPolyn(Q,A);
	UDFIntegral(*A);
	outcome=Value(*A,top)-Value(*A,bottom);
	printf("The value is: %.5g \n",outcome);
	CleanPolyn(A);
	return 1;
}


int MultPolyn(Linklist *P,Linklist *Q){
	if(!*P || !*Q){
		printf("List is empty!\n");
		exit(0);
	}
	Linklist S;			//sum
	Linklist p=*P,q,s,r;
	S=(Linklist)malloc(sizeof(LNode));
	if(!S){
		printf("Overflow!\n");
		exit(0);
	}
	S->coef=0;
	S->expn=-1;
	s=S;
	s->next=(Linklist)malloc(sizeof(LNode));
	s=s->next;
	s->coef=0;
	s->expn=0;
	s->next=NULL;		//S: zero polyn

	while(p=p->next){
		q=*Q;
		*P=(Linklist)malloc(sizeof(LNode));
		(*P)->coef=0;
		(*P)->expn=-1;
		(*P)->next=NULL;
		r=*P;
		while(q=q->next){
			//*P=*P(i)*Q;
			r->next=(Linklist)malloc(sizeof(LNode));
			if(!r->next){
				printf("Overflow!\n");
				exit(0);
			}
			r=r->next;
			r->expn=p->expn+q->expn;
			r->coef=p->coef*q->coef;
			r->next=NULL;
		}
		AddPolyn(&S,P);
	}
	*P=S;
	CleanPolyn(&S);			//Q exists.
	return PrintPolyn(*P);
}


int DivPolyn(Linklist *P,Linklist *Q){
	if(!*P || !*Q ||!(*P)->next || !(*Q)->next){
		printf("List is empty!\n");
		exit(0);
	}
	Linklist S,E;
	Linklist p,q,s,e;
	s=(Linklist)malloc(sizeof(LNode));
	s->coef=0;
	s->expn=-1;
	S=s;
	while((*P)->next->expn>=(*Q)->next->expn){
		e=(Linklist)malloc(sizeof(LNode));
		E=e;
		e->coef=0;
		e->expn=-1;
		e->next=(Linklist)malloc(sizeof(LNode));
		s->next=(Linklist)malloc(sizeof(LNode));
		e=e->next;
		s=s->next;
		s->expn=e->expn=(*P)->next->expn-(*Q)->next->expn;
		s->coef=e->coef=(*P)->next->coef/(*Q)->next->coef;
		s->next=e->next=NULL;
		MultPolyn(&E,Q);
		SubtractPolyn(P,&E);		//E was deleted here,S is exists.
	}
	printf("\nResult:\n");
	PrintPolyn(S);
	printf("remains:\n");
	PrintPolyn(*P);
	return 1;
}
