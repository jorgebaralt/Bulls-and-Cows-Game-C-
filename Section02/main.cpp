/*
this is the console ex, that makes us of the BullCowClass
this acts as the view in a MVC pattern, and is responsible for all
user interation. for game logic see the fBullCowGame class.
*/

#include<iostream>
#include<string>
#include "FBullCowGame.h"
//using namespace std; //so qe dont have to keep using std::std::cout << "";

using FText = std::string;
using int32 = int;


void PrintIntro();
void PlayGame();	
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();


FBullCowGame BCGame; //make instance of a new game

int main()
{
	bool playagain = false;
	do {
		PrintIntro();
		PlayGame();
		playagain = AskToPlayAgain();
	} while (playagain);
	return 0;
}

void PlayGame()
{
	BCGame.Reset();
	int32 maxtries = BCGame.GetMaxTries();
	//TODO change to while once we are validating tries.
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= maxtries)
	{
		FText Guess = GetValidGuess();

		//submit number of bulls and cows
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		//Print number of bulls and cows.
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " Cows = " << BullCowCount.Cows << "\n\n" ;
	}
	PrintGameSummary();
}

//introduce the game.
void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows" << std::endl; //same as \n 
	std::cout << "can you guess the " << BCGame.GetHiddenWordLenght();
	std::cout << " letter isogram I am thinking of? \n";
	std::cout << std::endl;
	return;
}

//get Valid guess from player.
FText GetValidGuess()
{
	FText Guess;
	EGuessStatus Status = EGuessStatus::Invalid;
	do {
		//get word from user
		int32 currentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << currentTry << " enter your guess: ";
		std::getline(std::cin, Guess);

		//check the word
		 Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
			case EGuessStatus::Wrong_length:
				std::cout << "Please enter a " << BCGame.GetHiddenWordLenght() << " letter word\n";
				break;
			case EGuessStatus::Not_Isogram:
				std::cout << "Please enter a word wihtout repeating letters.\n";
				break;
			case EGuessStatus::Not_lowercase:
				std::cout << "Please enter the letters all lowecase\n";
				break;
			default:
				break;
		}
		std::cout << "\n";
	} while (Status != EGuessStatus::OK);//keep looping until we get no errors.
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you Wanna play Again(y/n)?" << std::endl;
	FText response;
	std::getline(std::cin, response);
	return (response[0] == 'y' || response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
		std::cout << "Well Done you win.\n";
	else
		std::cout << "sorry, you have lost.";
}
