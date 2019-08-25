#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int32;

void PrintIntro();
void PlayGame();
FText GetGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;

int main()
{
	do
	{
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain());

	std::cout << std::endl;
	return 0;
}

void PrintIntro()
{
	// Introduce the game
	int32 WordLength = BCGame.GetHiddenWordLength();
	std::cout << "Welcome to Bulls and Cows, a fun word game. \n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << WordLength;
	std::cout << " letter isogram I'm thinking of? \n";

	return;
}

void PlayGame()
{

	BCGame.Reset();

	int32 MaxTries = BCGame.GetMaxTries();

	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetGuess();

		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}

FText GetGuess()
{
	FText Guess = "";
	EWordStatus Status = EWordStatus::Invalid_Status;
	do {
		// Get a guess from the player
		std::cout << "Try " << BCGame.GetCurrentTry() << " of " << BCGame.GetMaxTries() << ": ";
		getline(std::cin, Guess);

		EWordStatus Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EWordStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n\n";
			break;
		case EWordStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters. \n\n";
			break;
		case EWordStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters. \n\n";
			break;
		default:
			return Guess;
		}
	} while(Status != EWordStatus::OK); // keep looping until we get no errors
	return Guess;
}

bool AskToPlayAgain()
{

	std::cout << "Do you want to play again? (y/n) ";
	FText Response;
	getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary() {
	if(BCGame.IsGameWon())
	{
		std::cout << "WELL DONE!\nYOU WIN!\n\n";
	}
	else
	{
		std::cout << "Better luck next time!\n\n";
	}
}