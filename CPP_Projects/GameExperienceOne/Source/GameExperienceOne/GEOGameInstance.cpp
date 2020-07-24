// Fill out your copyright notice in the Description page of Project Settings.


#include "GEOGameInstance.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"

void UGEOGameInstance::Init()
{
	TotalGuessCount = 10;
	CurrentGuessCount = 0;
	bIsGameOver = false;
}

void UGEOGameInstance::UpdateDifficulty(TEnumAsByte<EDifficulty> Difficulty)
{
	DifficultyLevel = Difficulty;

	switch (Difficulty)
	{
		case EDifficulty::ED_Easy:
			CodeSize = 4;
			break;
		case EDifficulty::ED_Medium:
			CodeSize = 6;
			break;
		case EDifficulty::ED_Hard:
			CodeSize = 8;
			break;
	}

	for (int i = 0; i < CodeSize; i++)
	{
		ACustomButton* Button = Buttons[FMath::RandRange(0, Buttons.Num() - 1)];
		CorrectButtonCode.ButtonCode.Add(Button);
	}

	UE_LOG(LogTemp, Warning, TEXT("Printing CorrectButtonCode"));

	for (ACustomButton* Button : CorrectButtonCode.ButtonCode)
	{
		UE_LOG(LogTemp, Warning, TEXT("Button: %s"), *Button->GetName())
	}
}

void UGEOGameInstance::StoreButtons(TArray<ACustomButton*> ButtonList)
{
	Buttons = ButtonList;
}

void UGEOGameInstance::AddButtonToGuess(ACustomButton* Button)
{
	GuessedButtonCode.ButtonCode.Add(Button);

	UE_LOG(LogTemp, Warning, TEXT("%s added to current guess."), *Button->GetName());

	if (GuessedButtonCode.ButtonCode.Num() == CorrectButtonCode.ButtonCode.Num())
	{
		CheckGuess();
	}
}

void UGEOGameInstance::CheckGuess()
{
	UE_LOG(LogTemp, Warning, TEXT("Guessed Button Code Length: %d"), GuessedButtonCode.ButtonCode.Num());
	UE_LOG(LogTemp, Warning, TEXT("Correct Button Code Length: %d"), CorrectButtonCode.ButtonCode.Num());
	UE_LOG(LogTemp, Warning, TEXT("Total Guess Count: %d"), TotalGuessCount);

	for (int i = 0; i < CorrectButtonCode.ButtonCode.Num(); i++)
	{
		if (CorrectButtonCode.ButtonCode[i] != GuessedButtonCode.ButtonCode[i])
		{
			UE_LOG(LogTemp, Warning, TEXT("Incorrect Guess!"));
			CurrentGuessCount++;
			GuessedButtonCode.ButtonCode.Empty();
			
			if (CurrentGuessCount == TotalGuessCount)
			{
				GameOver(EGameOverReason::EGOR_RanOutOfGuesses);
			}

			return;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("You have guessed the code!"));

	GameOver(EGameOverReason::EGOR_CorrectGuess);
}

void UGEOGameInstance::GameOver(TEnumAsByte<EGameOverReason> Reason)
{
	bIsGameOver = true;
	GameOverReason = Reason;	
}

void UGEOGameInstance::ResetGame()
{
	Buttons.Empty();
	GuessedButtonCode.ButtonCode.Empty();
	CorrectButtonCode.ButtonCode.Empty();
	PreviouslyGuessedCodes.Empty();
	CurrentGuessCount = 0;
	bIsGameOver = false;
}