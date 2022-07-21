#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cstring>

using namespace std;

const int maxLength = 20;

void adding(int firstInput[], int firstSize, int secondInput[], int secondSize, int result[], int &resultSize);
void getting_input(int input[], int &inputSize);
void output(int output[], int outputSize);


int main(){

	int firstInput[maxLength], secondInput[maxLength], result[maxLength];
	int firstSize = 0, secondSize = 0, resultSize = 0;
	int i = 0, end;
	bool endCount = true;
	char c;
	
	cout<<"Large integer suming program"<<endl;
	
	while(endCount){
	
		cout<<"Please enter an integer, 20 digits or less"<<endl;
		getting_input(firstInput,firstSize);
		cout<<"You entered: ";
		output(firstInput,firstSize);
		cout<<endl;
		cout<<"Digit number: " << firstSize << endl;
		
		cout<<"Enter another integer, 20 digits or less"<<endl;
		getting_input(secondInput,secondSize);
		cout<<"You entered: ";
		output(secondInput,secondSize);
		cout<<endl;
		cout<<"Digit number: " << secondSize << endl;
		
		adding(firstInput,firstSize,secondInput,secondSize,result,resultSize);
		cout<<"The result is: ";
		output(result,resultSize);
		cout<<endl;
		cout<<"Digit number: " << resultSize << endl << endl;
	
		cout<<"Press 1 to continue or 0 to end"<<endl;
		cin >> end;
		cin.get(c);
		
		if(end == 0) endCount = false;
		
		else{
			for(i = 0; i < maxLength; i++){
				firstInput[i] = '\0';
				secondInput[i] = '\0';
				result[i] = '\0';
			}
			i = 0;
			firstSize = 0, secondSize = 0, resultSize = 0;
		}
		
	}

}

void getting_input(int input[], int &inputSize){

	char c;
	int i = 0, temp[maxLength];
	cin.get(c);
	
	/* gets input char by char and controls it if the entered number is valid */
	
	while(c != '\n'){
	
		if(!isdigit(c)){
			cout << "non digit entered. Aborting. " << endl;
			exit(1);
		}
		
		temp[i] = int(c) - int('0');
		inputSize++;
		i++;
		cin.get(c);
		
	}
	
	if(inputSize > 20){
		cout << "Input number size too large. Aborting." << endl;
		exit(1);
	}
	
	if(temp[0] == 0){
		cout << "Input can not start with '0'. Aborting." << endl;
		exit(1);
	}
	

	for(i = 0; i < inputSize; i++)
		input[inputSize - i - 1] = temp[i];


}


void output(int output[], int outputSize){
	int i;
		
	for(i = outputSize-1; i >= 0; i--)
		cout << output[i];
	
}

void adding(int firstInput[], int firstSize, int secondInput[], int secondSize, int result[], int &resultSize){

	int carry = 0, i;
	int largerSize;
	
	/* puts 0 at the end of number which has less digit than the other while their digit number will be equal */

	if(firstSize > secondSize){
		for(i = secondSize; i < firstSize; i++)
			secondInput[i] = 0;
		largerSize = firstSize;	
	}
	
	else{
		for(i = firstSize; i < secondSize; i++)
		
			firstInput[i] = 0;
			largerSize = secondSize;
	}
	
	i = 0;

	while(i < largerSize){

	/* adds digits and carry then write it to result array. If it carry is not 0 and still their sum is smaller than 9, resets carry*/

		if((firstInput[i] + secondInput[i] + carry) <= 9){
			result[i] = firstInput[i] + secondInput[i] + carry;
			if(carry == 1)
				carry = 0;
		}
		
	/* if sum of digits and carry is bigger than 9, it writes mod of their sum and makes carry 1 */	
	
		else{
			result[i] = (firstInput[i] + secondInput[i] + carry) % 10;
			carry = 1;
		}
		
		if(carry == 1){
		
		/* if sum of carry and larger size is bigger than 20 and it is last digit and also carry is 1, it means result has more than 20 digits, so gives overflow */
		
			if(largerSize + carry > 20 && i == largerSize -1){
				cout << "An overflow has occured. Result is set to 0 " << endl;
				resultSize = 1;
				result[0] = 0;	
			}
			
			else{
				result[largerSize] = carry;
				resultSize = largerSize + 1;
			}	

		}
		
		else
			resultSize = largerSize;
			
		i++;
	}

}
