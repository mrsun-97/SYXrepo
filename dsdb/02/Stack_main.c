#include"stack1.h"
#include<math.h>

int InitStack(SQStack *S);

Stype GetTop(SQStack S);
int Push(SQStack *S,Stype e);
int Pop(SQStack *S,Stype *e);
int StackEmpty(SQStack S);


static double arr[50]={0};
static int end=1; 
static char c,x;

int isOP(char s){
	switch(s){
		case '+':
		case '-':
		case '*':
		case '/':
		case '^':
		case '#':	
		case '(':
		case ')': return 1;
		default: return 0;
	}
}

char Precede(char a,char b){
	switch(a){
		case '+':
		case '-': 
			switch(b){
				case '+':
				case '-':
				case ')':
				case '#': return '>';
				default : return '<';
			}
		case '*':
		case '/':
		case '^':
			switch(b){
				case '+':
				case '-':
				case '*':
				case '/':
				case ')':
				case '#': return '>';
				default : return '<';
			}
		case ')': return '>';
		case '(':
			switch(b){
				case ')': return '=';
				default : return '<';
			}
		case 's':
		case 'c':
		case 't':
		case 'g':
		case 'n':
			switch(b){
				case '(':
				case 's':
				case 'c':
				case 't':
				case 'g':
				case 'n': return '<';
				default : return '>';
			}
		case '#':
			switch(b){
			case '#': return '=';
			default : return '<';
			}
	}
}

int trans(char s){
	return (int)(s-'0');
}

double operate(double a,char theta,double b){
	switch(theta){
			case '+': return a+b;
			case '-': return a-b;
			case '*': return a*b;
			case '/': return (double)a/b;
			case '^': return pow(a,b);
			case 's':
				arr[end++]=a;
				return sin(b);
			case 'c':
				arr[end++]=a;
				return cos(b);
			case 't':
				arr[end++]=a;
				return tan(b);
			case 'n':
				arr[end++]=a;
				return log(b);
			case 'g':
				arr[end++]=a;
				return log10(b);
			//case 
			default :exit(0);
	}
}

int main(){
	
	SQStack OP;
	InitStack(&OP);
	Push(&OP,'#');
	fflush(stdin);
	int Int,isnegtv=0,i;
	char d;
	double H,Dec,a,b,mid;
	c=getchar();
	
	while(c!='#' || GetTop(OP)!='#'){
		//isdigital
		printf("%d\n",c);
		if(c>='0' && c<='9'){
			isnegtv=0;
loop:	printf("%c_1\n",c);
			Int=0;
			H=10;
			Dec=0;
			do{
				Int=10*Int+trans(c);
				c=getchar();
			}while(c>='0' && c<='9');
			//meet '.'
			if(c!='.'){
				arr[end++]=(double)Int*(isnegtv?(-1):1);
			}else{
				c=getchar();
				while(c>='0' && c<='9'){
					Dec+=trans(c)/H;
					H*=10;
					c=getchar();
				}
				arr[end++]=((double)Int+Dec)*(isnegtv?(-1):1);
				isnegtv=0;
			}
			printf("--begin--\n");
			for(i=0;i<end;i++){
				printf("%g\n",arr[i]);
			}
			printf("--end--\n");

		}//end if
		else if(c==' ' || c=='\n')
			c=getchar();
		else{
			printf("%c_2\n",c);
			//c=getchar()
			if(c=='+' || c=='-'){
				isnegtv=(c=='-'?1:0);
				d=c;
				c=getchar();
				if(c>='0' && c<='9'){goto loop;}	//<== use 'goto' 
				else{
					stdin->_IO_read_ptr--;
					c=d;
				}
			}
			if(c>='a' && c<='z'){
				if(c=='s' || c=='c' || c=='t'){		//sin cos tan
					Push(&OP,c);
					do{
						c=getchar();
					}while(c>='a' && c<='z');
				}
				else if(c=='l'){					//ln or lg
					c=getchar();
					if(c=='n' || c=='g')
						Push(&OP,c);
					else exit(0);
					c=getchar();
				}
				else {
					printf("Unknow letter\n");
					exit(0);
				}
			}else if(isOP(c)){
				switch(Precede(GetTop(OP),c)){
					case '<':
						Push(&OP,c);c=getchar();
						break;
					case '=':
						Pop(&OP,&x);c=getchar();
						break;
					case '>':
						Pop(&OP,&x);
						b=arr[--end];
						a=arr[--end];
						mid=operate(a,x,b);
						arr[end++]=mid;
						printf("--begin--\n");
						for(i=0;i<end;i++){
							printf("%g\n",arr[i]);
						}
						printf("--end--\n");
						break;
				}
			}else{
				printf("Unknow operation\n");
				exit(0);
			}
		}
	}//end while
	printf("Result: %.3g\n",
			/*(double)(int)(arr[--end]+0.5)*/
		   arr[--end]);
	return 0;
}
