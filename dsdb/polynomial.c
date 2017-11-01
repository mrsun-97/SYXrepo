#include <stdio.h>
#include"common.h"
#include<unistd.h>

int main(){
    char c;
    double x=0;
    int l,m,n,i;
    Linklist a[11];
    int CreatPolyn(Linklist *p,int m);
    int PrintPolyn(Linklist p);
    int CopyPolyn(Linklist m ,Linklist *n);
    int AddPolyn(Linklist *m,Linklist *n);
    int AddPolyn(Linklist *m,Linklist *n);
    int SubtractPolyn(Linklist *A,Linklist *B);
    int Value(Linklist Q,double x);
    int DestoryPolyn(Linklist Q,int n);
    int CleanPolyn(Linklist *A);
    int Insert(Linklist *A);
    int Delete(Linklist *A);
    int Change(Linklist *A);
    int RandCreatPolyn(Linklist *A,int m);
    void ListArr(Linklist *A);
	int DiffPolyn(Linklist Q,int n);
	int UDFIntegral(Linklist Q);
	int DEFIntegral(Linklist Q);
    int MultPolyn(Linklist *P,Linklist *Q);
	int DivPolyn(Linklist *P,Linklist *Q);
	int PowPolyn(Linklist *P,int k);
	int Least_Greatest(Linklist *P,Linklist *Q);

	for(i=0;i<11;i++) a[i]=NULL;
    do {
        system("clear");
        printf("******************************************************************\n");
        printf("******************************************************************\n");
        printf("		1. CreatPolyn\n");
        printf("		2. PrintPolyn\n");
        printf("		3. CopyPolyn\n");
        printf("		4. AddPolyn\n");
        printf("		5. SubtractPolyn\n");
        printf("		6. Value\n");
        printf("		7. DestroyPolyn\n");
        printf("		8. CleanPolyn\n");
        printf("		9. (1)insert\t(2)delete\t(3)change\n");
		printf("		10.Differential\n");
		printf("		11.Undefied integral\n");
		printf("		12.Defined integral\n");
		printf("		13.MultPolyn\n");
		printf("		14.DivPolyn\n");
		printf("		15.Power\n");
		printf("		16.Least&Greatest common polyn\n");
        printf("******************************************************************\n"); 
        printf("******************************************************************\n");
        printf("-->");
        scanf("%d",&l);getchar();
		if(l<0 || l>16) continue;
        ListArr(a);
        switch(l){
            case 1:
                printf("input array number: ");
                scanf("%d",&n);getchar();
                printf("input mumbers: ");
                scanf("%d",&m);getchar();
                if(m<0){
                    RandCreatPolyn(&a[n],m);
                }else{
                    CreatPolyn(&a[n],m);
                }
                break;
            case 2:
                printf("printpolyn input number: ");
                scanf("%d",&n);getchar();
            	break;
			case 3:
                printf("Copy a to b: ");
                scanf("%d %d",&n,&m);getchar();
                CopyPolyn(a[n],&a[m]);
                break;
            case 4:
                printf("Add a and b: ");
                scanf("%d %d",&n,&m);getchar();
                AddPolyn(&a[n],&a[m]);
                break;
            case 5:
                printf("a minus b: ");
                scanf("%d %d",&n,&m);getchar();
                SubtractPolyn(&a[n],&a[m]);
                break;
            case 6:
                printf("workout value: x=");
                scanf("%lf",&x);getchar();
                printf("polyn number: ");
                scanf("%d",&n);getchar();
                Value(a[n],x);
                break;
            case 7:
                printf("Destroy polyn number: ");
                scanf("%d",&n);getchar();
                printf("expn: ");
                scanf("%d",&m);getchar();
                DestoryPolyn(a[n],m);
                break;
            case 8:
                printf("Clean polyn number: ");
                scanf("%d",&n);getchar();
                CleanPolyn(&a[n]);
                break;
            case 9:{
                do {
                    ListArr(a);
                    printf("Change polyn\n");
                    printf("a: insert\nb: delete\nc:change\n-->");
                    scanf("%c",&c);getchar();
                    printf("Polyn number: ");
                    scanf("%d",&n);getchar();
                    switch(c){
                        case 'a':
                            Insert(&a[n]);
                            break;
                        case 'b':
                            Delete(&a[n]);
                            break;
                        case 'c':
                            Change(&a[n]);
                            break;
                        default:
                            printf("Invalid operation!\n");
                            n=10;
                    }
                        
                }while(n!=10);
                break;
            }
			case 10:
				printf("DifferentialPolyn, number&times:");
				scanf("%d %d",&n,&m);getchar();
				DiffPolyn(a[n],m);
				break;
			case 11:
				printf("UDFIntegral: number:");
				scanf("%d",&n);getchar();
				UDFIntegral(a[n]);
				break;
			case 12:
				printf("DEFIntegral: number:");
				scanf("%d",&n);getchar();
				DEFIntegral(a[n]);
				break;
			case 13:
				printf("Mult: number1 & number2:");
				scanf("%d %d",&n,&m);getchar();
				MultPolyn(&a[n],&a[m]);
				//CleanPolyn(&a[m]);
				break;
			case 14:
				printf("Div: number1 & number2:");
				scanf("%d %d",&n,&m);getchar();
				DivPolyn(&a[n],&a[m]);
				//CLeanPolyn(&a[m]);
				break;
			case 15:
				printf("pow(a[n],k) n&k: ");
				scanf("%d %d",&n,&m);getchar();
				PowPolyn(&a[n],m);
				break;
			case 16:
				printf("printf polyn number 1&2: ");
				scanf("%d %d",&m,&n);
				Least_Greatest(&a[m],&a[n]);
				break;
            default :
				printf("Invalid operation!\n");            
        }//end switch
		if(l!=2 && l!=8 && l!=14 && l!=16) PrintPolyn(a[n]);
        fflush(stdin);
        getchar();getchar();
    }while(1<=l && l<=16);
    printf("Exit.\n");
	return 0;
}
