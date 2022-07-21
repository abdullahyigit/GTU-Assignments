#include<iostream>
#include<cstdlib>

using namespace std;

int main(){

	int i,j;
	bool prime;

	for(i=3;i<100;i++){
	
		prime = true;

		for(j=2;j<i;j++){
		
			if(i%j == 0) prime = false;   /* if a number has a divider which is smaller number than it, it means its not a prime number */
		
		}

		if(prime == true) cout << i <<" is prime number" << endl;

	}

	return 0;

}
