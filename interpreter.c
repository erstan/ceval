#include<stdio.h>
#include<string.h>
#include "./eval.h"
int main (int argc, char** argv){
	char exp[100];
	while(1){
		printf("In = "); scanf("%s", exp);
		if(!strcmp(exp, "exit")) 
		        break;
		void * tree = makeET(exp);
		printET(tree);
		printf("\nOut = %f\n\n", evaluateET(tree));
		deleteET(tree);
	}
return 0;
}
