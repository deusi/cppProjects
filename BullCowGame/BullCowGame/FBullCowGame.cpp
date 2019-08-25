#pragma once

#include "FBullCowGame.h"
#include <map>
#define TMap std::map


FBullCowGame::FBullCowGame()
{
	Reset();
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet";
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthTries {{3,4}, {4,7}, {5,10}, {6,16}, {7,20}};
	return WordLengthTries[MyHiddenWord.length()];
}

int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	int32 value = MyHiddenWord.length();
	return value;
}

bool FBullCowGame::IsGameWon() const
{
	return bGameIsWon;
}

EWordStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if(!IsIsogram(Guess))
	{
		return EWordStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess))
	{
		return EWordStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EWordStatus::Wrong_Length;
	}
	else 
	{
		return EWordStatus::OK;
	}
	return EWordStatus::OK;
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;

	FBullCowCount BullCowCount;

	int32 HiddenWordLength = MyHiddenWord.length();
	int32 GuessLength = Guess.length();
	for (int32 i = 0; i < GuessLength; i++) {
		char checkGuess = Guess[i];
		for (int32 j = 0; j < HiddenWordLength; j++) {
			char checkHidden = MyHiddenWord[j];
			if ((checkGuess == checkHidden) && i == j) {
				BullCowCount.Bulls++;
			}
			else if (checkGuess == checkHidden) {
				BullCowCount.Cows++;
			}
			else {
				continue;
			}
		}
	}
	if (BullCowCount.Bulls == GetHiddenWordLength()) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const 
{
	if(Word.length() <= 1)
	{
		return true;
	}
	
	TMap<char, bool> LetterSeen;
	for(auto Letter : Word)	
	{
		Letter = tolower(Letter);
		if(LetterSeen[Letter]) {
			return false;
		}
		else {
			LetterSeen[Letter] = true;
		}
	}

	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const 
{
	for(auto Letter : Word)
	{
		if(!islower(Letter))
		{
			return false;
		}
	}
	return true;
}
