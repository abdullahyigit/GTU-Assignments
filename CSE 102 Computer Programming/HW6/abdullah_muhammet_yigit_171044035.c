#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct tree{
	char name[20];
	float value;
	int amount;
	int components;/*node's component number*/
	int current_component;/*increases when node checks an component*/
	int flag;/*if a node's flag is 0, it means the node has not checked yet. After checking operation, flag becomes 1*/
	int flag2;/*if node has no component flag2 becomes 2, in other case becomes 1*/
	struct tree *node;
};

float rec(struct tree *object, struct tree *nodes, int current_pos, int total_component, char *current_component_name);

void filling_nodes(char *input,struct tree *node);


int main(){

	struct tree *object;

	char current_component_name[20];
	float result;

	object = (struct tree*)malloc(1*sizeof(struct tree));

	printf("Name the object:\n");
	scanf("%s",object->name);

	object->flag=0;
	object->flag2=0;
	object->current_component=0;
	object->components=0;
	object->amount=1;

	result = rec(object,object,1,0,current_component_name);

	printf("Total cost of %s is %1.f\n",object->name,result);

	free(object);

	return 0;
}

/*i sent 2 struct to recursion. First one is main object and second one is node. Main object is always constant and node is moving to it's node till it's node has not a node. After then, code makes it's flag 1 to not check it again and sends main object to node to check the other nodes*/
float rec(struct tree *object, struct tree *nodes, int current_pos, int total_component, char *current_component_name){

	char input[50];
	int i=0,j=0,component_number=0,temp;

	if(current_pos == 1) printf("Define %s?:\n",nodes->name);

	if(nodes->flag2 == 1){
		if(nodes->node[nodes->current_component].flag == 1) {/*after filling node's node, gets its value*/
			nodes->current_component++;
			nodes->value += (nodes->node[nodes->current_component-1].value*nodes->node[nodes->current_component-1].amount);
		}
		if(nodes->current_component == nodes->components && nodes->flag != 1) {nodes->flag=1; nodes->flag2 =0;}/*if code checks the node's all component, makes it's flag 1*/
		if((strcmp(nodes->name,object->name) == 0) && nodes->flag == 1) {object->flag = 1; object->value = nodes->value;}


		if(nodes->flag != 1)rec(object,nodes->node,current_pos,total_component,nodes->name);
		else rec(object,object,current_pos,total_component,nodes->name);
	}

	if(nodes->flag == 1 && object->flag != 1){	
		nodes++;
		if(nodes->flag2 != 2 && nodes->flag == 0 && nodes->components == 0){
			printf("Define %s in %s?:\n",nodes->name,current_component_name);
		}
		return rec(object,nodes,current_pos+1,total_component,current_component_name);
	}

	if(object->flag != 1){/*gets input and send it to a func to fill into struct*/
		getchar();	
		scanf("%[^\n]s",input);
		filling_nodes(input,nodes);
		total_component += nodes->components;
	}
	
	if(nodes->flag == 1 && nodes->components == 0){
		sscanf(input,"%f",&nodes->value);
		if(object->flag == 1) return object->value;
		return rec(object,object,current_pos+1,total_component,current_component_name);
	}

	else{
		if(object->flag != 1)printf("Define %s in %s?:\n",nodes->node[nodes->current_component].name,nodes->name);

		if(nodes->current_component == 0) return rec(object,nodes->node,current_pos+1,total_component,current_component_name);
		else return rec(object,nodes->node,current_pos+1,total_component,current_component_name);			
	}
}

void filling_nodes(char *input, struct tree *node){

	int temp=0,count=0,i=0,j=0,component_number=0,k=0;

	while(input[i++] != '\0') if(input[i] >= 'A' && input[i] <= 'Z') component_number++;/*finds component number*/
	node->components = component_number;

	if(node->components == 0) {node->flag=1; node->flag2 = 2;}

	else{
		node->node = (struct tree*)malloc(component_number*sizeof(struct tree));

		while(j<=i){
			if(input[j] >= '1' && input[j] <= '9'){/*if code sees a number, gets the amount with sscanf*/
				count = 0;
				for(k=0;k<20;k++) node->node[temp].name[k] = '\0';
				k=0;
				sscanf((input+j),"%d",&node->node[temp++].amount);
				
			}
			while(input[j] >= '1' && input[j] <= '9') j++;/*after getting amount, code goes till sees a letter*/
			if ((input[j] >= 'A' && input[j] <= 'Z') || (input[j] >= 'a' && input[j] <= 'z')){
				node->node[temp-1].name[count++] = input[j];
			}
			j++;
		}
		node->flag2++;
	}
}
