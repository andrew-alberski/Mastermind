//Not working version of code, check clion for working version
#include <cstdlib>
#include <vector>
#include <iostream>
using namespace std;
class Code{
public:
	vector<int> corrCode;
	vector<int> guessCode;
//Finction definitions for Code class
	void genRandCode(){ //will generate and assign random code to corrCode vector
		int randInt;
		for(int i=1; i<=4; i++){
			randInt = (rand() % 5);
			corrCode.push_back (randInt);
		}
	}

	int checkCorrect(){ //will check the number of digits in correct locations
		int correct_digits=0;
		for(unsigned i = 0; i<corrCode.size(); i++){
			if( corrCode[i] == guessCode[i])
				correct_digits++;
		}
		return correct_digits;
	}

	int checkIncorrect(){ //will check the number of digits in incorrect locations
		int incorrect_digits=0;
		for(unsigned i=0; i< corrCode.size(); i++){ //cycle through correct code
			for(unsigned j=0; j<guessCode.size(); j++){ //cycle through guess
				if((corrCode[i] == guessCode[j]) && (i != j))
					incorrect_digits++;
			}
		}
		return incorrect_digits;
	}
};

class Response : public Code{
public:
	vector<vector<int>> prevResponses{{0,0,0,0}};
	vector<int> storeCorrect;
	vector<int> storeIncorrect;
	int correct_digits=0;
	int incorrect_digits=0;

//Function definitions for Response class
	void getCorr_InCorrDigits(){
		//Check and Store Correct Digits
		correct_digits = checkCorrect();
		storeCorrect.push_back(correct_digits);
		
		//Check and Store Incorrect Digits
		incorrect_digits = checkIncorrect();
		storeIncorrect.push_back(incorrect_digits);
	}

	bool compareResponses(){
		for( unsigned i = 0; i<prevResponses.size(); i++){
			if(prevResponses[i]==guessCode)
				return true; //There exists an identical entry
			}
		prevResponses.push_back(guessCode); //Adds current to previous guess vector
		return false;
	}
		

	void printResponse(){
	cout<<"\nThe number of correct digits is: "<< correct_digits <<endl;
	cout<<"The number of correct digits in incorrect locations is: "<< incorrect_digits;
	}
};

class mastermind{
public:
	Response response;
//Function definitions for mastermind class
	void printSecretCode(){
		cout<<"\nThe random code is: ";
		for (int i:response.corrCode)
			cout<<i;
		cout<<"\n";
	}

	void humanGuess(){
		int guess;
		cout<<"\nEnter Guess for 1st digit: ";
		cin>> guess;
		response.guessCode.push_back(guess);
		cout<<"\nEnter Guess for 2nd digit: ";
		cin>> guess;
		response.guessCode.push_back(guess);
		cout<<"\nEnter Guess for 3rd digit: ";
		cin>> guess;
		response.guessCode.push_back(guess);
		cout<<"\nEnter Guess for 4th digit: ";
		cin>> guess;
		response.guessCode.push_back(guess);
	}

	bool isSolved(){
		if(response.guessCode == response.corrCode)
			return true; //solved
		else
			return false;
	}
	
	void playGame(){
		int attempts = 0;
		response.genRandCode();
		printSecretCode();
		while((attempts<10) && !isSolved()){
			START:
			humanGuess();
			if(response.compareResponses()){
			cout<< "You already tried this combination. TRY AGAIN!"<<endl;
			goto START; 
			}
			cout<<"\nGuessed code:";
			response.getCorr_InCorrDigits();
			//potential store previous respnse issue
			//print 2d vector
			response.printResponse();
			attempts++;
		}
	}
};
