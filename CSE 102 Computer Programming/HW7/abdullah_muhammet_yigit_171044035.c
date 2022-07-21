#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define max 10

struct input{
	char name[max];
	int value;
};

struct circuit{
	char input1_name[max];
	char input2_name[max];
	char gate_name[max];
	char gate_type[max];
	int result;
	int flipflop_count;
};

int recursion(struct circuit *gates, struct input *inputs, int count, int total_gates, int total_inputs);

int main(){

	struct circuit *gates;
	gates = (struct circuit*)malloc(1*sizeof(struct circuit));
	struct input *inputs;
	inputs = (struct input*)malloc(1*sizeof(struct input));

	FILE *fp1;
	fp1 = fopen("input.txt","r");
	FILE *fp2;
	fp2 = fopen("circuit.txt","r");
	FILE *fp3;
	fp3 = fopen("output.txt","w+");

	char c,d,*line;
	int i=0,j=0,temp=0,temp1=-1,result,flipflop=0,flag=0;

	line = (char*)malloc(1*sizeof(char));

	while((c = fgetc(fp1)) != EOF){/*fills structs and sends them to recursion function when it sees '\n',after then fills again till EOF*/

		if(c != '\n'){/*fills input struct's values*/
			if(c != ' '){
				if(flag == 0) inputs = (struct input*)realloc(inputs,(i+1)*sizeof(struct input));
				inputs[i].value = (int)c - 48;
				i++; 	
			}
		}

		else{/*fills the gates struct*/
			if(flag == 0){
				while((d = fgetc(fp2)) != EOF){
					if(d != '\n'){
						if(j == 0){/*for the first line at circuit.txt, fills input's name into inputs struct*/
							if(d == 'I')while((d = fgetc(fp2)) != ' ');
							if(d == ' '){
								temp1++;
								temp = 0;
							}
							else inputs[temp1].name[temp++] = d;	
						}
						else{/*for the other lines, gets the line into a string to seperate*/
							line[temp++] = d;
						}
					}
					else {/*seperates line string and fills gates struct*/
						gates = (struct circuit*)realloc(gates,(j+1)*sizeof(struct circuit));
						line[temp] = '\0';
						if(j != 0){
							if(line[0] == 'N' || line[0] == 'F'){
	 							sscanf(line,"%s%s%s",gates[j-1].gate_type,gates[j-1].gate_name,gates[j-1].input1_name);
							}
							else{
								sscanf(line,"%s%s%s%s",gates[j-1].gate_type,gates[j-1].gate_name,gates[j-1].input1_name,gates[j-1].input2_name);
							}
						}
						gates[j-1].flipflop_count = 0;
						j++;
						temp = 0;
					}
				}
				flag++;
			}
			result = recursion(gates,inputs,0,j-1,i);/*after filling operation, sends the structs to recursion function*/
			fprintf(fp3,"%d\n",result);
			i=0;
		}

	}
	return 0;
}

int recursion(struct circuit *gates, struct input *inputs, int count, int total_gates, int total_inputs){

	int temp=0,current_input1=2,current_input2=2,i,j;

	if((count) == total_gates) return gates[count-1].result;/*returns last gate's value*/
	
		
	else{
		/*first, code searches input1 at input's struct. if it can't find it, then keeps searching at gates' struct*/
		for(i=0;i<total_inputs;i++) if((strcmp(gates[count].input1_name,inputs[i].name)) == 0) current_input1 = inputs[i].value;
				
		if(current_input1 == 2){
				for(j=0;j<total_gates;j++){
					if((strcmp(gates[count].input1_name,gates[j].gate_name)) == 0) current_input1 = gates[j].result;
				}
		}

		for(i=0;i<total_inputs;i++) if((strcmp(gates[count].input2_name,inputs[i].name)) == 0) current_input2 = inputs[i].value;
		if(current_input2 == 2){				
				for(j=0;j<total_gates;j++){
					if((strcmp(gates[count].input2_name,gates[j].gate_name)) == 0) current_input2 = gates[j].result;
				}		
		}
		/*after finding inputs, find the current gate's result*/
		if(gates[count].gate_type[0] == 'A'){		
			if(current_input1 == 1 && current_input2 == 1) gates[count].result = 1;
			else gates[count].result = 0;	
		}
		else if(gates[count].gate_type[0] == 'O'){		
			if(current_input1 == 1 || current_input2 == 1) gates[count].result = 1;
			else gates[count].result = 0;	
		}
		else if(gates[count].gate_type[0] == 'N'){
			if(current_input1 == 1) gates[count].result = 0;
			else gates[count].result = 1;
		}
		else{
			if(current_input1 == 0 && gates[count].flipflop_count == 0) gates[count].result = 0;
			else if(current_input1 == 0 && gates[count].flipflop_count == 1) gates[count].result = 1;
			else if(current_input1 == 1 && gates[count].flipflop_count == 0) gates[count].result = 1;
			else if(current_input1 == 1 && gates[count].flipflop_count == 1) gates[count].result = 0;

			if(current_input1 == 1){
				if(gates[count].flipflop_count == 0)gates[count].flipflop_count = 1;
				else gates[count].flipflop_count =0;
			}
		}
		return recursion(gates,inputs,count+1,total_gates,total_inputs);
	}
}
