/* The game logic (no view code or direct user interaction)
 The game is a simple guess the word game based on Mastermind*/

#pragma once
#include <string>

 // to make unreal friendly
using FString = std::string;
using int32 = int;

//all values initialized to zero
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	Ok,
	Not_Isogram,
	Not_Lowercase,
	Odd_Symbols,
	Wrong_Length
};

class FBullCowGame
{
public:
	//FBullCowGame(); //constructor

	
	int32 GetMaxTries() const;//number of tries to actually have
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	FString ChoseHiddenWord(int32 Userchoice);
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;
	void SetWordLength(int32 Userchoice);
	FBullCowCount SubmitValidGuess(FString Guess);

private:
	//see constructor for initialization

	//individual items
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;
	
	//methods or bunch of codes
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
	
	//void CheckingMethod();// see how many letters are correct. todo make richer return value. probably string
	//oid PickWord();
};

