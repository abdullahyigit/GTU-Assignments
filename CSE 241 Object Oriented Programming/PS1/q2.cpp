#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

int humanTurn(int humanTotalScore);
int computerTurn(int computerTotalScore);
int rolling();

int main(){

	srand(static_cast<int>(time(NULL)));
	
	int humanTotalScore = 0;
	int computerTotalScore = 0;
	bool gameover = false;
	
	while(!gameover){
	
		humanTotalScore += humanTurn(humanTotalScore);  /* human starts game first */
	
		if(humanTotalScore < 100) computerTotalScore += computerTurn(computerTotalScore);
	
		if(humanTotalScore >= 100){ /*if human's total score is bigger than 100, it means human won*/
			cout << "Congratulations, you win!" << endl;
			gameover = true;
		}
		
		else if(computerTotalScore >= 100){  /* if computer's total score is bigger than 100, it means computer won */
			cout << "Sorry, the computer won." << endl;
			gameover = true;
		}
		
	}

	return 0;
}

int rolling(){

	return (rand() % 6) +1; /* getting random number between 1-6 including 1 and 6 */

}


int humanTurn(int humanTotalScore){

	char input;
	int score = 0, dice;
	bool turnover = false;
	
	cout << "It's your turn! Enter 'r' to roll." << endl;
	cin >> input;
	if(input != 'r' || input != 'h')
	
	while(!turnover){
	
		dice = rolling();
		cout << "You rolled " << dice << endl;
		
		if(dice == 1){ /* if rolling is 1, turn passes to opponent */
		
			cout << "You lose your turn. " << "Enter 'c' to continue." << endl;
			cin >> input;
			return 0;
			
		}
		
		else{
		
			score += dice;
			
			/* shows player's round and total points */
			
			cout << "Your score this round is "<< score << endl;
			cout << "If you hold, your total score would be: " << humanTotalScore + score << endl;
			
			if((score + humanTotalScore) >= 100){ /* if player's total point is bigger than 100, ends game */
			
				cout << "Enter 'c' to continue." << endl;
				cin >> input;
				turnover = true;

			}			
			
			else{ /* ask the user if he wants keep rolling or holds the points */
			
				cout << "Press 'h' to hold or 'r' to roll again." << endl;
				cin >> input;
				
				if(input == 'h') turnover = true;
			
			}
			
		}
	
	}
	
	return score;
}


int computerTurn(int computerTotalScore){

	int score = 0, dice = 0;
	char input;
	bool turnover = false;
	
	cout << "It's the computer's turn!" << endl;

	while(!turnover){
	
		dice = rolling();
		cout << "The computer rolled " << dice << endl;

		if(dice == 1){ /* if rolling is 1, turn passes to opponent */
		
			cout << "The computer loses its turn. " << "Enter 'c' to continue." << endl;
			cin >> input;
			return 0;
			
		}
		
		else{
		
			score += dice;
			
			/* shows player's round and total points */
			
			cout << "The computer's score this round is "<< score << endl;
			cout << "If the computer holds, its total score would be: " << computerTotalScore + score << endl;
			
			/* if computer's total point is bigger than 100, ends game or round point is bigger than 20, end its turn */
			
			if(score >= 20 || (score + computerTotalScore) >= 100){ 
				cout << "The computer holds.  " << "Enter 'c' to continue." << endl;
				cin >> input;
				turnover = true;
				
			}
		}
	
	}

	return score;

}
