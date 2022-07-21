#include<stdio.h>

#define p1 0.5
#define p2 20

int main(){

	char x,v;
	double n = 0,temp,currentnumber,a = 0,b=0;
	int y = 10, dotcount = 0,numbercount=0;

	FILE *fp;
	fp = fopen("input.txt","r");
	FILE *fp1;
	fp1 = fopen("output.txt","w");

	while((x = fgetc(fp)) != EOF){

/* this part gets the number till sees space */

		if(x != ' '){

			if(x == '.') dotcount ++;

			else if((x - 48) >= 0 && (x - 48) <= 9){

				if(dotcount == 0){
				
					n *= y;
					n += (x - 48);
					
				}
				
				else{

					temp = (x - 48);
					temp /= y;
					n += temp;
					y *= 10;

				}

			}

		}


		if(x == ' '){

/*this if statement places the first number into the first chunk, writes into output.txt and calculates average(a)*/

			if(numbercount == 0){

				fprintf(fp1,"%.4lf ",n);
				numbercount++;
				a += n;
				a /= numbercount;
				
			}

/*this else statement calculates the average with new number(b), applies to the formula and checks that which chunk is the new number belong to*/

			else{

				numbercount++;
				b = ((a * (numbercount - 1)) + n) / numbercount;

/*if formula verifies that new number belongs to current chunk, prints it into output.txt and replaces b to a*/

				if(b <= a * (1 + p1) && b >= a * (1 - p1) && a <= n * p2 && a>= n / p2){

					fprintf(fp1,"%.4lf ",n);
					a = b;
		
				}

/*in other case prints average of chunk to the current line and prints new number to the next line to create new chunk*/
				else{

					fprintf(fp1,"average: %.4lf ",a);
					fprintf(fp1,"\n%.4lf ",n);
					numbercount = 1;
					a = n / numbercount;

				}				

			}

			dotcount = 0;
			y = 10;
			n = 0;

		}

	}

/*when loop sees the end of file it quits from loop without calculating and printing last number, so this part for the last number*/


	if(a == 0) fprintf(fp1,"%.4lf average: %.4lf",n,n);  /*if input has just one number, average will be '0' in while loop so this if for printing one output*/

	else{

		numbercount++;
		b = ((a * (numbercount - 1)) + n) / numbercount;

		if(b <= a * (1 + p1) && b >= a * (1 - p1) && a <= n * p2 && a>= n / p2){

			fprintf(fp1,"%.4lf ",n);
			fprintf(fp1,"average: %.4lf \n",b);

		}

		else{

			fprintf(fp1,"average: %.4lf ",a);
			fprintf(fp1,"\n%.4lf ",n);
			numbercount = 1;
			a = n / numbercount;
			fprintf(fp1,"average: %.4lf \n",a);

		}

	}
	
	fclose(fp);
	fclose(fp1);
	
	return 0;
}
