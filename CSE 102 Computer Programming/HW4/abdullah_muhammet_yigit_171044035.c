#include<stdio.h>
#include<math.h>

#define pol_length 1000
#define max 100

double calculation(double value, char polynomial[pol_length]);

int main(){

	char c,polynomial[pol_length];
	double values[max],result;
	int polynom_length=0,number_of_values=0,i=0;

	FILE *fp1,*fp2,*fp3;
	fp1 = fopen("polynomial.txt","r");
	fp2 = fopen("values.txt","r");
	fp3 = fopen("evaluations.txt","w+");

	while((fscanf(fp2,"%lf",&values[number_of_values])) != EOF)number_of_values++;/*Reads the values and fills into an array*/

	while((c = fgetc(fp1)) != EOF) if(c != ' ' && c != '\n') polynomial[polynom_length++] = c;/*Reads the polynom and fills into an array*/
	for(polynom_length;polynom_length<=pol_length;polynom_length++)polynomial[polynom_length] = '\0';/*If length of array is smaller than pol_length, fills with '\0' rest of array*/
	
	while(i < number_of_values){/*Passes values namely and prints returned value into evaluations.txt*/
		result = calculation(values[i],polynomial);
		fprintf(fp3,"%.2lf\n",result);
		i++;
	}
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	return 0;
}

double calculation(double value, char polynomial[pol_length]){

	int i=0,j=0,temp=0,power=0,count=0,m,k;
	double result = 0,parameter,number;
	char part_of_pol[15],sign,x,current_sign='+';

	/*for(k=0;k*/

	while(i < pol_length){

		if(polynomial[0] == '-'){/*At the beginning of function current sign is + but polynom array's first char is -, current sign becomes - and polynom array's first char becomes + to not to get into this if statement again*/
			current_sign = '-';
			polynomial[0] = '+';
			i++;
		}


/*There are one main if and one main else statement here. Program divides the polynom into parts unless it see + or - sign so program can use sscanf easily on divided parts*/
		if(polynomial[i] == '+' || polynomial[i] == '-' || polynomial[i] == '\0'){

			while(temp <= 15) part_of_pol[temp++] = '\0';

			if(part_of_pol[0] == 'x'){/*If part of polynom starts with 'x' it means there are two statements. Part is just x or part is x power something like x^5*/

				if(part_of_pol[1] == '^') sscanf(part_of_pol,"%c%c%d",&x,&sign,&power);
				else sign = ',';
		
				if(sign == '^'){
					if(current_sign == '+')result += pow(value,power);
					else result -= pow(value,power);
				}
				else{
					if(current_sign == '+')result += value;
					else result -= value;
				}
			}
			else{/*If part of polynom doesnt start with 'x' it means there are three statements. Part is just number like +5, -10 or part is x with parameter like 5x, 12.5x or part is x with parameter and power like 5x^2, -4x^7*/
				for(j=0;j<temp;j++) if(part_of_pol[j] == '^' || part_of_pol[j] == 'x') count++;/*Count determines what kind of polynom is parts. Count increases when code sees '^' or 'x'*/
				if(count == 0){/*If count is 0, it means part is just number*/
					sscanf(part_of_pol,"%lf",&number);
					if(current_sign == '+')result += number;
					else result -= number;
				}
				else if(count == 1){/*If count is 1, it means part is x with parameter*/
					sscanf(part_of_pol,"%lf%c",&parameter,&x);
					if(current_sign == '+')result += (parameter * value);
					else result -= (parameter * value);
				}
				else if(count == 2){/*If count is 2, it means part is x with parameter and power*/
					sscanf(part_of_pol,"%lf%c%c%d",&parameter,&x,&sign,&power);
					if(current_sign == '+')result += (parameter * (pow(value,power)));
					else result -= (parameter * (pow(value,power)));
				}
			}
/*After operations, resets values and array, changes current sign and if code comes to '\0' i becomes pol_length to get out of while*/
			for(j=0;j<=10;j++) part_of_pol[j] = '\0';
			temp = 0;
			count = 0;
			current_sign = polynomial[i];
			i++;
			if(polynomial[i] == '\0') i = pol_length;
		}
/*Fills a part of polynom into an array unless it see + or -*/
		else{
			part_of_pol[temp] = polynomial[i];
			temp++; i++;
			part_of_pol[temp] = '\0';
		}
	}

	return result;
}
