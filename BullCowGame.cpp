/* This is the conosole executable that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic, see the FBullCowGame class.
*/

#pragma once

#include "stdafx.h"
#include <iostream>
#include <string>
#include "FBullCowGame.h"

//makes syntax unreal friendly
using FText = std::string;
using int32 = int;

//function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;  //instantiate a new game, which is re-used across plays

int main()
{

	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	   } 
	while (bPlayAgain);

	return 0; //exit the application
}


//introduce the game
void PrintIntro()
{
	std::cout << " ii\\   \\  //           //\\      ii \\       //\\         //\\        //\\                                                                         " << std::endl;
	std::cout << " ii \\   \\//           //  \\     ii   \\    //  \\       //  \\      //  \\                                                                        " << std::endl;
	std::cout << " ii===   ii          //====\\    ii   //   //====\\     //    \\    //    \\                                                                         " << std::endl;
	std::cout << " ii //   ii         //      \\   ii  //   //      \\    ii     \\  //     ii                                                                         " << std::endl;
	std::cout << " ii//    ii        //        \\  ii//    //        \\   ii      \\//      ii                                                                         " << std::endl;
	 
	std::cout << "\n\n Welcome to Bulls & Cows, The best word game ever created, by Adam\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram that i'm thinking of?	\n\n\n\n";
	return;
}

//plays a single game to completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	std::cout << "You have " << MaxTries;
	std::cout << " attempts.\n\n" << std::endl;
	std::cout << "Bulls represent correct letters in the correct spot" << std::endl;
	std::cout << "While cows represent correct letters that need to be rearranged.\n\n " << std::endl;


	//loop for the number of turns asking for guesses while the game is not won
	//and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess();

		//submit valid guess to the game and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";


		std::cout << "Your guess was: " << Guess << "\n\n";
	                                                                  }

		PrintGameSummary();
		return;
	
}

FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		//get a guess from the player 
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Attempt " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		//check status of guess and give feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "I'm not smart enough to allow uppercase letters yet. \n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Yeah, that's not an isogram bud... Don't repeat letters. \n\n";
			break;

		default:
			//assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); //keep looping until we get no errors
	return Guess;

}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? y/n? ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
	std::cout << std::endl;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
	std::cout << "HEY!!! YOU WON MY MEDIOCRE GAME!!!!\n";
	}
	else
	{
		std::cout << "Maybe try again? Or don't, I don't really care!!!\n";
	}

}
