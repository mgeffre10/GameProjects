// Fill out your copyright notice in the Description page of Project Settings.


#include "GEOGameInstance.h"
#include "CodeWidget.h"
#include "CurrentCodeWidget.h"
#include "GameOverWidget.h"
#include "PreviousCodesWidget.h"

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
	CurrentCodeWidget->CodeWidget->UpdateCodeDisplay(GuessedButtonCode.ButtonCode);


	if (GuessedButtonCode.ButtonCode.Num() == CorrectButtonCode.ButtonCode.Num())
	{
		CheckGuess();
	}
}

void UGEOGameInstance::CheckGuess()
{
	for (int i = 0; i < CorrectButtonCode.ButtonCode.Num(); i++)
	{
		if (CorrectButtonCode.ButtonCode[i] != GuessedButtonCode.ButtonCode[i])
		{
			CurrentGuessCount++;

			if (CurrentGuessCount == TotalGuessCount)
			{
				GameOver(EGameOverReason::EGOR_RanOutOfGuesses);
				return;
			}

			CurrentCodeWidget->CodeWidget->ResetCodeDisplay();
			PreviousCodeWidget->AddGuessToWidget(GuessedButtonCode.ButtonCode);
			GuessedButtonCode.ButtonCode.Empty();
			return;
		}
	}

	GameOver(EGameOverReason::EGOR_CorrectGuess);
}

void UGEOGameInstance::GameOver(TEnumAsByte<EGameOverReason> Reason)
{
	bIsGameOver = true;
	GameOverReason = Reason;

	CurrentCodeWidget->RemoveFromParent();
	PreviousCodeWidget->RemoveFromParent();
	GameOverWidget->AddToViewport();

	APlayerController* PlayerController = GetFirstLocalPlayerController();

	
	PlayerController->SetInputMode(FInputModeUIOnly());
	PlayerController->bShowMouseCursor = true;
	PlayerController->GetPawn()->DisableInput(PlayerController);
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