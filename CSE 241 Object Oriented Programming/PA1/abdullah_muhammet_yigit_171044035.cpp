#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cstring>

int gameplay(int secretNumber);
int gettingNumber(char** argv);
int differentDigits(int secretNumber);

using namespace std;

int main(int argc, char** argv){

	int secretNumber = 0;
	int canbeSecret;
	char firstparameter[15] = "./mastermind";
	int game;
	srand(static_cast<int>(time(NULL)));
	
	if(argc != 3 || strcmp(argv[0],firstparameter) != 0){ /* gives E0 error to missing parameters and wrong compile name */
		cout << "E0" << endl;
		return 0;
	}

	secretNumber = gettingNumber(argv); /* gets secret number */
	
	if(secretNumber == -1){ /* if gettingNumber func return -1, it means E0 error */
		cout << "E0" << endl;
		return 0;
	}
	
	if(secretNumber == -2){ /* if gettingNumber func return -2, it means E0 error */
		cout << "E1" << endl;
		return 0;
	}	

	game = gameplay(secretNumber);
	
	return 0;
}


int gettingNumber(char** argv){

	int number = 0;
	int canbeSecret = 0;

	if(argv[1][0] == '-' && argv[1][1] == 'u' && argv[1][2] == '\0'){
	
		int length = strlen(argv[2]); /* gets given number's length */
		
		if(length > 9) return -2; /* digits of number cant be bigger than 9 */
		if(length == 1 && (argv[2][0] - 48) == 0) return -1; /* if user enters -u 0, gives Eo error */
		
		int i = length - 1;
		int multiplier = 1;
	
		while(i >= 0){
			if((argv[2][i] - 48) < 0 || (argv[2][i] - 48) > 9) return -1;/* if input has a noninteger digit, returns -1 to give E0 error*/
			number += (argv[2][i--] - 48) * multiplier;
			multiplier *= 10;
		}
		canbeSecret = differentDigits(number);
		if(canbeSecret == 0) return -1; /* if input has a repeating digit, gives E0 error */
	}

	else if(argv[1][0] == '-' && argv[1][1] == 'r' && argv[1][2] == '\0'){
	
		int digitnumber;
		digitnumber = atoi(argv[2]);
	
		if(digitnumber <= 0) return -1; /* if entered digit number is smaller than 1, gives E0 error */
		else if(digitnumber > 9) return -2; /* if entered digit number is bigger than 9, gives E1 error */
	
		int digit = argv[2][0] - 48;
		int i = 0;
		int multiplier = 1;
		
		while(canbeSecret == 0){ /* gets random numbers and multiplies them with multiple of 10 (1,10,100..) namely and adds it to number which is 0 at the beginning */
			i = 0;
			multiplier = 1;
			number = 0;
			while(i++ < digit){
				number += ((rand() % 9) + 1) * multiplier;
				multiplier *= 10;
			}		 
			canbeSecret = differentDigits(number);
		}
	}
	
	else return -1;

	return number;

}


int differentDigits(int secretNumber){

	int temp1 = secretNumber;
	int temp2 = secretNumber;
	int count = 0;

/* takes last digit of secret number and checks it with all digits. If that digit is same with another one, count increases. */
/* If count is bigger than 1, it means number cant be secret number */

	while(temp1 > 0){
	
		while(temp2 > 0){	
			if((temp2 % 10) == (temp1 % 10)) count++;
			temp2 /= 10;		
		}
		
		if(count != 1) return 0;	
		else{
			temp1 /= 10;
			count = 0;
			temp2 = secretNumber;
		}
		
	}

	return 1;
}

int gameplay(int secretNumber){

	int input,firstcount,secondcount,digit;
	int countSecret=0,countInput=0,countGeneral = 1;
	int tempSecret = secretNumber;
	char inputArr[9];
	int length,i;
	
	bool endGame = false;
	
	while(!endGame){
	
		cin >> inputArr;
		
		length = strlen(inputArr);
		
		for(i=0;i<length;i++){ /* checks that if there is a letter in input */
			if(inputArr[i] < 48 || inputArr[i] > 57){
				cout << "E2" << endl;
				return 0;
			}
		}	
		
		input = atoi(inputArr);		
		
		int tempInput = input;
		tempSecret = secretNumber;
		firstcount = 0;
		secondcount = 0;
		
		if(input == secretNumber){ /* when user find the number, finishes the game */
			cout << "FOUND " << countGeneral << endl;
			endGame = true;
		}
		
		else{	

			while(tempInput > 0 || tempSecret > 0){ /* counts input's and secret number's digits to compare them */
				tempInput /= 10;
				if(tempInput != 0)countInput++;
				tempSecret /= 10;
				if(tempSecret != 0)countSecret++;			
			}
			
			int inputdiffControl = differentDigits(input); /* checks input that can it be secret number*/
			
			if(countInput != countSecret || inputdiffControl == 0){ /* if digits of secret number and ipput are different or input cant be secret number, gives E1 error*/
				cout << "E1" << endl;
				
				return 0;
			}
			
			tempSecret = secretNumber;
			tempInput = input;
			
			while(tempInput > 0 && tempSecret > 0){ /* calculates first count */
				if((tempInput % 10) == (tempSecret % 10)) firstcount++;
				tempInput /= 10;
				tempSecret /= 10;
			}
			
			tempInput = input;
			tempSecret = secretNumber;
			
			while(tempSecret > 0){	/* calculates total matched digits */
				while(tempInput > 0){	
					if((tempInput % 10) == (tempSecret % 10)) secondcount++;
					tempInput /= 10;		
				}
				tempSecret /= 10;
				tempInput = input;
			}
			
			secondcount -= firstcount; /* substract first count from total matched digits to calculate second count */
			
			cout << firstcount << " " << secondcount << endl;
			
			countGeneral++; /* counts steps */
			countInput = 0;
			countSecret = 0;
		
		}
		
		if(countGeneral > 100){ /* failure situation */
			cout << "FAILED" << endl;
			endGame = true;
		}
	}
	return 1;
}
