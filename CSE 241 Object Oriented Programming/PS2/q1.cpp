#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

void shooting(char shooterName, bool &shooter, bool &target_1, bool &target_2);


int main(){

	srand(static_cast<int>(time(NULL)));

	bool Aaron = true, Bob = true, Charlie = true;
	double duelCount = 0, AaronCount = 0, BobCount = 0, CharlieCount = 0;
	const int maxDuel = 10000;
	int duel;
	int tour = 1;
	
	while(duelCount != maxDuel){
	
		/* tour determines the shooter. Aaron becomes shooter at tour 1, Bob becomes at tour 2 and Charlie becomes at tour 3*/
	
		if(tour == 1 && Aaron == true) shooting('A',Aaron,Charlie,Bob);  
		else if(tour == 2 && Bob == true) shooting('B',Bob,Charlie,Aaron);
		else if(tour == 3 && Charlie == true) shooting('C',Charlie,Bob,Aaron);	
		
		/* determines winners */
	
		if(Aaron == true && Bob == false && Charlie == false){
			duelCount++;
			AaronCount++;
			Aaron = true, Bob = true, Charlie = true;
			tour = 1;
		}
		
		else if(Aaron == false && Bob == true && Charlie == false){
			duelCount++;
			BobCount++;
			Aaron = true, Bob = true, Charlie = true;
			tour = 1;
		}
		
		else if(Aaron == false && Bob == false && Charlie == true){
			duelCount++;
			CharlieCount++;
			Aaron = true, Bob = true, Charlie = true;
			tour = 1;
		}
		
		/* icreases tour, if Charlie shoot and duel has not over yet, tour becomes 1 to Aaron become shooter */
		
		else{
			if(tour == 3) tour = 1;
			else tour++;				
		}
	}

	cout << "Aaron won: %" << AaronCount/100 << endl;
	cout << "Bob won: %" << BobCount/100 << endl;
	cout << "Charlie won: %" << CharlieCount/100 << endl;

	return 0;

}

void shooting(char shooterName, bool &shooter, bool &target_1, bool &target_2){

	int hit = 0;
	
	/* calculates hit percentages of shooter */
	
	if(shooterName == 'A') hit = rand()%3 + 1;
	else if (shooterName == 'B') hit = rand()%2 + 1;
	else if (shooterName == 'C') hit = 1;
	
	/* if hit is 1, shooter kills the next player which has highest hit percentage. If he is dead, shoots the other */

	if(hit == 1){
		if(target_1) target_1 = false;
		else if(target_2) target_2 = false;	
	}

}
