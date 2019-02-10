#pragma once
#include "FBullCowGame.h"
#include <map>


// to make unreal friendly
#define Tmap std::map
using FString = std::string;
using int32 = int;

FBullCowGame::FBullCowGame()
{
	Reset();
}

void FBullCowGame::Reset()
{
	const FString Hidden_Word = ChoseHiddenWord(); /*"planet"*///this must be an isogram
	
	MyCurrentTry = 1;
	MyHiddenWord = Hidden_Word;
	bGameIsWon = false;
	return;
}

int32 FBullCowGame::GetCurrentTry() const { 	return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { 	return MyHiddenWord.length(); } 
bool FBullCowGame::IsGameWon() const {	return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const
{
	Tmap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,16}, {7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	Tmap<char, bool> LetterSeen; //create the map
	for (auto Letter : Word) //for all letters of the word
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) {// if the letter is in the map
			return false;// we do NOT have an isogram
		}
		else { LetterSeen[Letter] = true; } //add the letter to the map as seem  
	}


	return true;// for example in cases where /0 is entered
}

bool FBullCowGame::IsLowercase(FString WordL) const
{
	
	for (auto Letter : WordL) //for all letters of the word
	{
		

		if (!islower(Letter))//if not a lowercase letter
		{
			return false;// we do NOT have an isogram
		}
		else { return true; } //add the letter to the map as seem  
	}


	return true;// for example in cases where /0 is entered
}

FString FBullCowGame::ChoseHiddenWord(int32 Userchoice)
{
	Tmap<int32, FString> HiddenWord_and_Length{ { 3, "use" },{ 4, "four" },{ 5, "plains" },{ 6, "planet" },{ 7, "simpler" } };
	return HiddenWord_and_Length[Userchoice];
}


	

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))//if guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram; 
	}
	else if (!IsLowercase(Guess))// if the guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length()!= GetHiddenWordLength())//if the guess lenght is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else//otherwise
	{
		return EGuessStatus::Ok;
	}
}
		

//receives a valid guess, incriments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length();//assuming same length as guess
	//loop through all letters in the Hidden word
	for (int32 HdWdChar = 0; HdWdChar < WordLength; HdWdChar++)
		// compare letters against the Guess Word
		for (int32 GsChar = 0; GsChar < WordLength; GsChar++)
		{
			//if they match then
			if (Guess[GsChar] == MyHiddenWord[HdWdChar])
			{
				if (HdWdChar == GsChar)
				{
					//increment bulls if they match
					BullCowCount.Bulls++;
				}
				//else
				else
				{
					//increment cows if not
					BullCowCount.Cows++;
				}
			}

		}
	if (BullCowCount.Bulls == WordLength) 
		{
			bGameIsWon = true;
		}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}




