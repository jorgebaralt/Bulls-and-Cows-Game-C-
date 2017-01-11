#include "FBullCowGame.h"
#include<map>
#define Tmap std::map

using int32 = int;
//get funtions

int32 FBullCowGame::GetCurrentTry() const { return currentTry; }
int32 FBullCowGame::GetHiddenWordLenght() const{return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const {
	Tmap<int32, int32> WordLenghtTMaxTries{ {3,3},{4,5},{5,7},{6,10} };
	return WordLenghtTMaxTries[MyHiddenWord.length()];
}

FBullCowGame::FBullCowGame() {
	Reset();
}

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	const FString HIDEN_WORD = "car";
	MyHiddenWord = HIDEN_WORD;
	currentTry = 1;
	bGameIsWon = false;
	maxTries = MAX_TRIES;
	return;
}



EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess)const 
{
	if (!IsIsogram(Guess))//if the guess isnt an isogram;
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess))//all lower case
	{
		return EGuessStatus::Not_lowercase;
;
	}
	else if (Guess.length()!=MyHiddenWord.length())//guess lenght is wrong
	{
		return EGuessStatus::Wrong_length;
	}
	else
		return EGuessStatus::OK;
	return EGuessStatus::OK;
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	currentTry++;
	//setup a return variable(the struct)
	FBullCowCount BullCowCount;

	//loop through all letters in the guess
	for (int32 i = 0; i < MyHiddenWord.length(); i++){
		for (int32 j = 0; j < MyHiddenWord.length(); j++) {
			if (Guess[j] == MyHiddenWord[i]) {
				if (i == j)//if they are at same place
					BullCowCount.Bulls++;//increment bull
				else
					BullCowCount.Cows++;//increment cows
			}

		}
	}
		//copare letters against the hidden word. 
	if (BullCowCount.Bulls == MyHiddenWord.length())
		bGameIsWon = true;
	else
		bGameIsWon = false;

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	//check each letter in Guess.
	if (Word.length() <= 1) { return true; }
	Tmap<char, bool> LetterSeen; //set the map.
	for (auto Letter : Word) {
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) //if it is already true, then is not isogram.
			return false;
		else // set to true, so we have it in our map.
			LetterSeen[Letter] = true;
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (char Letter : Word) {
		if (!islower(Letter))
			return false;
		else
			return true;
	}

}
