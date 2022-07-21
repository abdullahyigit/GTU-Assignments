#include<stdio.h>

#define row 100
#define column 250
#define length 10

int horizontal(char input2[row+1][column], char input1[length], int word_length);
int vertical(char input2[row+1][column], char input1[length], int word_length);

int main(){

	char c,input2[row+1][column],input1[length];
	int i=1,j=1,m,n,result,word_length;	
	FILE *fp3;
	fp3 = fopen("output.txt","w+");
	FILE *fp2;
	fp2 = fopen("input2.txt","r");

/*this while gets letters from input2.txt and fills them into array*/
	while((c=fgetc(fp2)) != EOF){
		if(c == '\n'){
			while(j <= column){/*if number of letters smaller than column, fills array with spaces to column value*/
				input2[i][j] = ' ';
				j++;
			}
			i++;
			j=1;
		}
		else{
			input2[i][j] = c;
			j++;
		}
	}

	FILE *fp1;
	fp1 = fopen("input1.txt","r");

	i=0;
		
/*this while gets words namely from input1.txt and fills them into array, then passes to function with input2 array and word length*/
	while((c=fgetc(fp1)) != EOF){
		if(c == '\n' || c == '\0'){ 
			if(c != '\0') input1[i] = '\0';/*after filling array, puts \0 next char*/
			result = horizontal(input2,input1,i);
			if(result == 0) vertical(input2,input1,i);
			for(j=0;j<i;j++) input1[j] = '\0';/*for the next word, resets array*/
			i = 0;		
		}
		else{
			input1[i] = c;
			i++;
		}
	}

	fclose(fp1);
	fclose(fp2);
	fclose(fp3);

	return 0;
}

int horizontal(char input2[row+1][column], char input1[length], int word_length){

	int count=0,i=1,j=1,temp=0,temp2=0;
	FILE *fp3;
	fp3 = fopen("output.txt","a");

	for(i=1;i<=row;i++){
		for(j=1;j<=column;j++){
			if(input2[i][j] == input1[temp2] && (j+temp) <= column && input1[temp2] != '\0'){
				while(temp <= word_length){/*if the current letter matches with word's first letter,controls next letter word's length times horizontally*/
					if(input2[i][j+temp] == input1[temp2]){
						count++;/*if next letters matches with word's other letter, increases count*/
						temp2++;
					}
				temp++;
				}
			}
			if(count == word_length){/*if count equals to word length, prints word and it's coordinates to output.txt*/
				fprintf(fp3,"%s (%d,%d) Horizontal\n",input1,i,j);
				fclose(fp3);
				return 1;
			}
			else{/*else resets temp values and count,then continues searching*/
				count=0;temp=0;temp2=0;
			}
		}
	}
	return 0;
}

int vertical(char input2[row+1][column], char input1[length], int word_length){

	int count=0,i=1,j=1,temp=0,temp2=0;
	FILE *fp3;
	fp3 = fopen("output.txt","a");

	for(i=1;i<=row;i++){
		for(j=1;j<=column;j++){
			if(input2[i][j] == input1[temp2]){
				while(temp <= word_length){/*if the current letter matches with word's first letter,controls next letter word's length times vertically*/
					if(input2[i+temp][j] == input1[temp2] && (i+temp) <= row && input1[temp2] != '\0'){
						count++;/*if next letters matches with word's other letter, increases count*/
						temp2++;
					}
				temp++;
				}
			}
			if(count == word_length){/*if count equals to word length, prints word and it's coordinates to output.txt*/
				fprintf(fp3,"%s (%d,%d) Vertical\n",input1,i,j);
				fclose(fp3);
				return 1;
			}
			else{/*else resets temp values and count,then continues searching*/
				count=0;temp=0;temp2=0;
			}
		}
	}
	return 0;
}
