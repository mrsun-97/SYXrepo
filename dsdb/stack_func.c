#include"stack1.h"

int InitStack(SQStack *S){
	S->base=(Stype)malloc(STACK_INIT_SIZE*sizeof(Stype));
	if(!S->base){
		printf("Overflow!\n");
		exit(-1);
	}
	S->top=S->base;
	S->stacksize=STACK_INIT_SIZE;
	return 1;
}

int GetTop(SQStack *S,Stype *e){
	if(S->top==S->base){
		printf("Empty stack!\n");
		return 0;
	}
	*e=*(S->top-1);
	return 1;
}

int Push(SQStack *S,Stype e){
	if(S->top-S->base >= S.stacksize){
		S->base=(Stype)realloc(S->base,(S.stacksize+STACKINCREMENT)*sizeof(Stype));
		if(!s->base){
			printf("Overflow!\n");
			exit(-1);
		}
		S->top=S->base+S->stacksize;
		S->stacksize+=STACKINCEMENT;
	}
	*S->top++ =e;
	return 1;
}

int Pop(SQStack *S,Stype *e){
	if(S->top==S->base){
		printf("Empty stack!\n");
		return 0;
	}
	*e=*--S->top;
	return 1;
}

int StackEmpty(SQStack S){
	if(S.top==S.base) return 1;
	else return 0;
}
