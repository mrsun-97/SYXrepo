#include <stdio.h>
#include <stdlib.h>
#define INFINITY  100000
#define MAX 9
#define true 1
#define false 0

static int D[MAX];
static int map[MAX][MAX];
static int path[MAX][MAX];
static char name[MAX][4];

int plusone(int *array){
	int i,m=0;
	for(i=0;i<MAX;i++)
		if(array[i]>m)
			m=array[i];
	return m+1;
}

void ShortestPath_DIJ(int v0){
	int i,j,v,w,min;
	int final[MAX];
	for(v=0;v<MAX;v++){
		final[v]=false;
		D[v]=map[v0][v];
		for(w=0;w<MAX;w++) path[v][w]=0;
		if(D[v]<INFINITY){
			path[v][v0]=1;
			path[v][v]=plusone(path[v]);
		}
	}
	D[v0]=0;
	final[v0]=true;
	for(i=1;i<MAX;i++){
		min=INFINITY;
		for(w=0;w<MAX;w++){
			if(final[w]==false)		//w isn't in set S
				if(D[w]<min){	
					v=w;
					min=D[w];
				}
		}
		final[v]=true;				//put the shortest in S
		for(w=0;w<MAX;w++){
			if(!final[w] && (min+map[v][w]<D[w])){
				D[w]=min+map[v][w];
//printf("D[%d]=%d\n",w,D[w]);
				for(j=0;j<MAX;j++) path[w][j]=path[v][j];
				path[w][w]=plusone(path[w]);
			}
		}
	}//end outer for
}

void display(int P[],char (*N)[4]){
	int i,j,k;
	for(k=0,i=0;i<MAX;i++){			//find maxnum
		if(P[i]>k) k=P[i];
	}
	for(i=2;i<=k;i++)
		for(j=0;j<MAX;j++)			//find passed vertex in order
			if(P[j]==i){
				printf(" --> %s",N[j]);
				break;
			}	
	printf("\n");
}


void main(){
	FILE *fp;
	if((fp=fopen("map.txt","r"))==NULL){
		printf("Can't open map file.\n");
		exit(0);
	}
	int i,j,n;
	char c;
	c=fgetc(fp);
	
	while(c!='\n'){
		c=fgetc(fp);
		//if(c=='\t') MAX++;
	}
	

	for(j=0;j<MAX;j++)
		for(i=0;i<MAX;i++)
			path[i][j]=0;
	printf("\nIn file map.txt:\n");
	for(i=0;i<MAX;i++){  			//get the map
		fscanf(fp,"%s",name[i]);
		for(j=0;j<MAX;j++){
			fscanf(fp,"\t%d",&n);
			if(n==0)
				map[i][j]=INFINITY;
			else
				map[i][j]=n;
			printf("\t%c",n?('0'+n):'-');
		}
		printf("\n");
		c=fgetc(fp);
	}
	fclose(fp);
	n=-1;			//let n!=i
	while(1){		//loop until i or j is out of range.
		printf("Please input v0 and vt:");
		scanf("%d %d",&i,&j);getchar();
		if(i>=0 && i<MAX && j>=0 && j<MAX){
			if(n!=i) ShortestPath_DIJ(i);
		}
		else{
			printf("Out of range!\n");
			break;
		}
		n=i;
		if(D[j]<INFINITY){			//real path exists
			printf("\n%s",name[i]);
			display(path[j],name);
			printf("total length: %d\n",D[j]);
		}
		else
			printf("NO WAY!\n");
		printf("\n");
	}
/*[test]
for(i=0;i<MAX;i++)
	printf("%d ",D[i]);
*/
}
