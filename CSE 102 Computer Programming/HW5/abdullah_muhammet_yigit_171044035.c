#include<stdio.h>

#define max 250
#define max2 10

void rec(char input[max], int flag, char node[max2], int hyphencount, int flagnode, FILE *fp2);

int main(){

	char input[max],c,node[max2];
	int i = 0, flag = 0, hyphencount = 0, flagnode = 0;

	FILE *fp1;
	fp1 = fopen("input.txt","r");
	FILE *fp2;
	fp2 = fopen("output.txt","w+");

	while((c = fgetc(fp1)) != EOF) input[i++] = c; /*fills input.txt into input array*/
	input[i-1] = '\0';

	rec(input,flag,node,hyphencount,flagnode,fp2);
	fclose(fp1);
	fclose(fp2);
	return 0;
}

void rec(char input[max], int flag, char node[max2], int hyphencount, int flagnode, FILE *fp2){

	int i = 0;
	
	if(input[flag] == '\0');/*finishes recursion*/

	else if(input[flag] == '(') return rec(input,flag+1,node,hyphencount+1,flagnode,fp2);/*hyphencount increases*/
	
	else if(input[flag] == ')') return rec(input,flag+1,node,hyphencount-1,flagnode,fp2);/*hyphencount decreases*/

	else if(input[flag] == ','){
		i = 0;
		while(i <= max2) node[i++] = '\0';/*resets node array and makes flagnode 0*/
		return rec(input,flag+1,node,hyphencount,0,fp2);
	}
	
	else{
		node[flagnode] = input[flag];/*fills node*/
		if(input[flag+1] == ')' || input[flag+1] == '(' || input[flag+1] == ','|| input[flag+1] == '\0'){/*checks next char to print*/
			node[flagnode+1] = '\0';
			for(i=0;i<hyphencount;i++)fprintf(fp2,"-");
			if(input[flag+1] == '\0') fprintf(fp2,"%s",node);
			else fprintf(fp2,"%s\n",node);	
		}		
		return rec(input,flag+1,node,hyphencount,flagnode+1,fp2);
	}	
}
