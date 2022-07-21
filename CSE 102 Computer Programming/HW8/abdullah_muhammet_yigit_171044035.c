#include<stdio.h>
#include<stdlib.h>

#define max 512

int terrainparts(int m[max][max] , int row , int column , int currentmark , int waterlevel);
int terrainparts2(int m[max][max] , int row , int column , int currentmark , int markone);

int main(){
	int m[max][max], i=0, j=0, markone=-1, currentmark=markone, islandcount=0, waterlevel;
	
	FILE *input;
	FILE *output;
	
	input=fopen("input.txt","r");
	
	fscanf(input,"%d",&waterlevel);
	
	int marktwo=waterlevel+1;
	
	for(i=0;i<max;i++){/* transfers numbers from input to array*/
		for(j=0;j<max;j++){
			fscanf(input,"%d",&m[i][j]);
		}
	}
	
	for(i=0;i<max;i++){/* if result of first recursion is bigger than 1, there will be an island and counts how many islands in array.*/
		for(j=0;j<max;j++){
			if(terrainparts(m,i,j,currentmark,waterlevel)>= 1)islandcount++;
		}
	}
	
	output=fopen("output.txt","w");
	
	fprintf(output,"%d\n",islandcount);/* prints count of island.*/
	
	currentmark=marktwo;
	
	for( i=0 ; i<max ; i++){
		for( j=0 ; j<max ; j++){
			if(terrainparts2(m,i,j,currentmark,markone)>= 1)fprintf(output,"%d %d\n",i,j); /* if result of first recursion is bigger than 1, prints a terrain's coordinate from an island.*/
		}
	}


	return 0;
}

int terrainparts(int m[max][max] , int row , int column , int currentmark , int waterlevel ){ /* determines the parts what are they, water,terrain or island.*/
	if(row>=0 && column>= 0 && row < max && column < max && m[row][column] > waterlevel ){
		m[row][column] = currentmark;/* if part is terrain, marks the terrain and checks are the any terrain around the marked terrain.*/
		return 1 + terrainparts(m,row+1,column,currentmark,waterlevel) + terrainparts(m,row,column-1,currentmark,waterlevel) + terrainparts(m,row,column+1,currentmark,waterlevel);
	}
	else 
		return 0;	/* if part is water returns 0.*/
}

int terrainparts2(int m[max][max] , int row , int column , int currentmark , int markone ){/* makes the marked terrains waterlevel+1 to make a terrain again.*/
	if(row>=0 && column>= 0 && row < max && column < max && m[row][column] == markone ){
		m[row][column] = currentmark;
		return 1 + terrainparts2(m,row+1,column,currentmark,markone) + terrainparts2(m,row,column-1,currentmark,markone) + terrainparts2(m,row,column+1,currentmark,markone);
	}
	else 
		return 0;
}
