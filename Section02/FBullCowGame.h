#pragma once
#include<string>
using int32 = int;
using FString = std::string;

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};
enum class EGuessStatus
{
	Invalid,
	OK,
	Not_Isogram,
	Wrong_length,
	Not_lowercase,
};

class FBullCowGame {
public:
	class FBullCowGame(); //constructor

	void Reset(); //make a more rich return value.

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLenght() const;

	bool IsGameWon() const;

	EGuessStatus CheckGuessValidity(FString) const;//return value later
	
	//counts bulls & cows, increases try# assuming valid guess.
	FBullCowCount SubmitValidGuess(FString);


private:
	//initialize in constructor.
	int32 currentTry;
	int32 maxTries;
	FString MyHiddenWord; 
	bool bGameIsWon;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
	//provide a method for bounting bulls and o
};