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
    int RandCreatPolyn(Linklist *A);
    void ListArr(Linklist *A);

    for(i=0;i<10;i++) a[i]=NULL;
    do {
        system("clear");
        printf("***************************************************************\n");
        printf("***************************************************************\n");
        printf("        1. CreatPolyn\n");
        printf("        2. PrintPolyn\n");
        printf("        3. CopyPolyn\n");
        printf("        4. AddPolyn\n");
        printf("        5. SubtractPolyn\n");
        printf("        6. Value\n");
        printf("        7. DestroyPolyn\n");
        printf("        8. CleanPolyn\n");
        printf("        9. (1)insert\t(2)delete\t(3)change\n");   
        printf("***************************************************************\n"); 
        printf("***************************************************************\n");
        printf("-->");
        scanf("%d",&l);getchar();
        
        switch(l){
            case 1:
                printf("input array number: ");
                scanf("%d",&n);getchar();
                printf("input mumbers: ");
                scanf("%d",&m);getchar();
                if(m==-1){
                    RandCreatPolyn(&a[n]);
                }else{
                    CreatPolyn(&a[n],m);
                }
                PrintPolyn(a[n]);
                break;
            case 2:
                ListArr(a);
                printf("printpolyn input number: ");
                scanf("%d",&n);getchar();
                PrintPolyn(a[n]);break;
            case 3:
                ListArr(a);
                printf("Copy a to b: ");
                scanf("%d %d",&l,&m);getchar();
                CopyPolyn(a[l],&a[m]);
                break;
            case 4:
                ListArr(a);
                printf("Add a and b: ");
                scanf("%d %d",&m,&n);getchar();
                AddPolyn(&a[m],&a[n]);
                break;
            case 5:
                ListArr(a);
                printf("a minus b: ");
                scanf("%d %d",&m,&n);getchar();
                SubtractPolyn(&a[m],&a[n]);
                break;
            case 6:
                ListArr(a);
                printf("workout value: x=");
                scanf("%lf",&x);getchar();
                printf("polyn number: ");
                scanf("%d",&n);getchar();
                Value(a[n],x);
                break;
            case 7:
                ListArr(a);
                printf("Destroy polyn number: ");
                scanf("%d",&m);getchar();
                printf("expn: ");
                scanf("%d",&n);getchar();
                DestoryPolyn(a[m],n);
                break;
            case 8:
                ListArr(a);
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
            default :printf("Invalid operation!\n");            
        }//endswitch
        fflush(stdin);
        getchar();getchar();
    }while(1<=l&&l<=9);
printf("test_main_2\n");
    return 0;
}
