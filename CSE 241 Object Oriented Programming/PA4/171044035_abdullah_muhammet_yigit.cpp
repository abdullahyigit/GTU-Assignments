#include<iostream>
#include<cstdlib>
#include<fstream>
#include<cstring>

using namespace std;

class Gate{

	public:
		void read_circuit_file_first();
		void set_Gate_count(int number);		
		void set_Input_count(int number);
		void set_Circuit_count(int number);
		int get_Gate_count();	
		int get_Input_count();
		int get_Circuit_count();	
		void set_value(int number);
		int get_value();
		string get_name();
		void set_name(string name);
				
	private:
		int Gate_count;
		int Input_count;
		int Circuit_count;
		int input_value;
		string name;
		int total_gate_count;

};

string Gate::get_name(){
	return this->name;
}

void Gate::set_name(string name){

	this->name = name;

}

void Gate::set_value(int number){

	this->input_value = number;

}

int Gate::get_value(){

	return this->input_value;
}


int Gate::get_Gate_count(){

	return this->Gate_count;
}

int Gate::get_Input_count(){

	return this->Input_count;
}

int Gate::get_Circuit_count(){

	return this->Circuit_count;
}


void Gate::set_Gate_count(int number){

	this->Gate_count = number - 2;

}

void Gate::set_Input_count(int number){

	this->Input_count = number;


}

void Gate::set_Circuit_count(int number){

	this->Circuit_count = number;

}

void Gate::read_circuit_file_first(){

	ifstream read_circuit_file("circuit.txt");
	char c,temp;
	int count_gates = 0;
	int count_inputs = 0;
	
	while(read_circuit_file.get(c)){
		if(count_gates == 0 && temp == ' ' && isalpha(c)) count_inputs++;
		if(c == '\n') count_gates++;
		temp = c;
	}
	
	this->set_Gate_count(count_gates);
	this->set_Input_count(count_inputs);

}



class AND : public Gate{

	public:
		int Evaluate();
		void set_input1_name(string name);
		void set_input2_name(string name);
		void set_gate_name(string name);

	private:
		Gate *input1;
		Gate *input2;
		string input1_name;
		string input2_name;
		string gate_name;
		
};

int AND::Evaluate(){

	if(input1->get_value() == 1 && input2->get_value() == 1) return 1;
	
	else return 0;

}

void AND::set_input1_name(string name){

	this->input1_name = name;

}

void AND::set_input2_name(string name){

	this->input2_name = name;

}

void AND::set_gate_name(string name){

	this->gate_name = name;

}


class OR : public Gate{

	public:
		int Evaluate();
		void set_input1_name(string name);
		void set_input2_name(string name);
		void set_gate_name(string name);
		
	private:
		Gate *input1;
		Gate *input2;
		string input1_name;
		string input2_name;
		string gate_name;
		
};

int OR::Evaluate(){

	if(input1->get_value() == 0 && input2->get_value() == 0) return 0;
	
	else return 1;

}

void OR::set_input1_name(string name){

	this->input1_name = name;

}

void OR::set_input2_name(string name){

	this->input2_name = name;
	
}

void OR::set_gate_name(string name){

	this->gate_name = name;

}


class DECODER : public Gate{

	public:
		int Evaluate();

	private:
		Gate *input1;
		Gate *input2;
		string input1_name;
		string input2_name;
		string gate_name;
		
};

int DECODER::Evaluate(){

	if(input1->get_value() == 0 && input2->get_value() == 0) return 1;
	else if(input1->get_value() == 0 && input2->get_value() == 1) return 2;
	else if(input1->get_value() == 1 && input2->get_value() == 0) return 3;		
	else return 4;

}


class NOT : public Gate{

	public:
		int Evaluate();

	private:
		Gate *input;
		string input_name;
		int output;
		string gate_name;
		
};

int NOT::Evaluate(){

	if(input->get_value() == 0) return 1;
	
	else return 0;

}



class FLIPFLOP : public Gate{

	public:
		int Evaluate();
		void set_former_out();

	private:
		Gate *input;
		string input_name;
		int output;
		int Former_out;
		string gate_name;
		
};

int FLIPFLOP::Evaluate(){

	if(input->get_value() == 0 && Former_out == 0) {Former_out = 0; return 0;}
	if(input->get_value() == 0 && Former_out == 1) {Former_out = 1; return 1;}
	if(input->get_value() == 1 && Former_out == 0) {Former_out = 1; return 1;}
	else {Former_out = 0; return 0;}

}

void FLIPFLOP::set_former_out(){
	Former_out = 0;
}



class INPUT : public Gate{

	public:
		void set_input_value(int number);
		void set_input_name(string name);
		string get_input_name();
		string print_name();
		void printf() {cout << "alp" << endl;}

	private:
		int input_value;
		string input_name;
		
};




void INPUT::set_input_name(string name){

	this->input_name = name;


}

void INPUT::set_input_value(int number){

	this->input_value = number;


}

string INPUT::print_name(){
	
	return this->input_name;

}

string INPUT::get_input_name(){

	return this->input_name;
	
}



int main(){

	Gate **Gates;
	Gate temp_object;

	temp_object.read_circuit_file_first();
	int gate_count = temp_object.get_Gate_count();
	int input_count = temp_object.get_Input_count();

	Gates = new Gate*[gate_count + input_count];


	ifstream read_circuit_file("circuit.txt");
	char c;
	int count_each_line = 0;
	char temp[10];
	int i = 0;
	int line_count = 0;
	Gate *temp_gate;
	temp_gate = new Gate[input_count];	
	int total_gate_count = 0;

	int and_gate=0,or_gate=0,ff_gate=0,decoder_gate=0,input_gate=0;
	string temp_names1,temp_names2,temp_names3;

	for(int k = 0; k < 10; k++) temp[k] = '\0';
		while(read_circuit_file.get(c)){
				if(c != '\n'){
			
				if(c != ' '){
					
					temp[i++] = c;
						
				}
					
				else{

					if(count_each_line == 0){
						
						if(temp[0] == 'I')
							input_gate++;
						
						else if(temp[0] == 'A')
							and_gate++;
							
						else if(temp[0] == 'O' && temp[1] == 'R')
							or_gate++;									
																						
					}
						
					else{
						
						if(input_gate > 0){
							Gates[total_gate_count]	= new INPUT[1];
							INPUT temp_input;
							temp_input.set_input_name(temp);
							Gates[total_gate_count] = (Gate*) &temp_input;
							Gates[total_gate_count][0].set_name(temp);
						}
							
							
						else if(and_gate > 0){
							if(count_each_line == 1) temp_names1 = temp;
							if(count_each_line == 2) temp_names2 = temp;
						}
							
						else if(or_gate > 0){
							if(count_each_line == 1) temp_names1 = temp;
							if(count_each_line == 2) temp_names2 = temp;
						}							

						if(count_each_line == 1 || total_gate_count < 4) total_gate_count++;
	
					}
						 
					 count_each_line++;
					 for(int k = 0; k < 10; k++) temp[k] = '\0';
					 i = 0;
				}
			}
				
			else{
				if(input_gate > 0){
					Gates[total_gate_count]	= new INPUT[1];
					INPUT temp_input;
					temp_input.set_input_name(temp);
					Gates[total_gate_count][0] = temp_input;
					Gates[total_gate_count][0].set_name(temp);
					input_gate = 0;
				}
						
				else if(and_gate > 0){
					Gates[total_gate_count]	= new AND[1];
					AND temp_and;
					if(count_each_line == 3) temp_names3 = temp;
					temp_and.set_gate_name(temp_names1);
					temp_and.set_input1_name(temp_names2);
					temp_and.set_input2_name(temp_names3);
					Gates[total_gate_count][0] = temp_and;
					Gates[total_gate_count][0].set_name(temp_names1);
					and_gate = 0;
				}						
	
				else if(or_gate > 0){
					Gates[total_gate_count]	= new OR[1];
					OR temp_or;
					if(count_each_line == 3) temp_names3 = temp;
					temp_or.set_gate_name(temp_names1);
					temp_or.set_input1_name(temp_names2);
					temp_or.set_input2_name(temp_names3);
					Gates[total_gate_count] = (OR*) &temp_or;
					Gates[total_gate_count][0].set_name(temp_names1);
					or_gate = 0;
				}															

				for(int k = 0; k < 10; k++) temp[k] = '\0';
				i = 0;
				count_each_line = 0;
			
			}
				
	}
	
	ifstream read_input_file("input.txt");
	char c1;
	int inp_value;
	int input_file_count = 0;

	return 0;
}
