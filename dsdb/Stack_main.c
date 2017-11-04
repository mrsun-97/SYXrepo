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
				/*case '*':			
				case '/':
				case '^':
				case '(':*/
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
				case '^':
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
			case '/': return a/b;
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
	//char c;
	int Int,isminus;
	double H,Dec,a,b;
	c=getchar();
	
	while(c!='#' || GetTop(OP)!='#'){
		/*if(c=='-'){
			c=getchar();
			if(c>='0'&&c<='9')
				
		}
		*/
		//isdigital
		if(c>='0' && c<='9'){
			Int=0;
			H=10;
			Dec=0;
			do{
				Int=10*Int+trans(c);
				c=getchar();
			}while(c>='0' && c<='9');
			//meet '.'
			if(c!='.'){
				arr[end++]=(double)Int;
				c=getchar();
			}else{
				c=getchar();
				while(c>='0' && c<='9'){
					Dec+=trans(c)/H;
					H*=10;
					c=getchar();
				}
				arr[end++]=(double)Int+Dec;	
			}

		}//end if
		else{
			if(c>='a' && c<='z'){
				if(c=='s' || c=='c' || c=='t'){	//sin cos tan
					Push(&OP,c);
					do{
						c=getchar();
					}while(c<'a' || c>'z');
				}
				else if(c=='l'){				//ln or lg
					c=getchar();
					if(c=='n' || c=='g')
						Push(&OP,c);
					else exit(0);
					c=getchar();
				}
				else exit(0);
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
						arr[end++]=operate(a,x,b);
						break;
				}
			}else{
				printf("Unknow operation\n");
				exit(0);
			}
		}
	}
	printf("%g\n",arr[--end]);
	return 0;
}
