// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomButton.h"

#include "Blueprint/UserWidget.h"
#include "Engine/GameInstance.h"
#include "GEOGameInstance.generated.h"

UENUM(BlueprintType)
enum EDifficulty {
	ED_Easy			UMETA(DisplayName="Easy"),
	ED_Medium		UMETA(DisplayName = "Medium"),
	ED_Hard			UMETA(DisplayName = "Hard"),
	ED_MAX
};

UENUM(BlueprintType)
enum EGameOverReason {
	EGOR_CorrectGuess		UMETA(DisplayName="Guessed Correctly"),
	EGOR_RanOutOfGuesses	UMETA(DisplayName="Ran out of Guesses"),
	EGOR_MAX
};

USTRUCT()
struct FButtonCode {

	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Custom Attributes")
	TArray<ACustomButton*> ButtonCode;
};
/**
 * 
 */
UCLASS()
class GAMEEXPERIENCEONE_API UGEOGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere, Category = "Custom Attributes")
	TArray<ACustomButton*> Buttons;

	UPROPERTY(VisibleAnywhere, Category = "Custom Attributes")
	TEnumAsByte<EDifficulty> DifficultyLevel;

	/* Property for the code the player needs to guess in order to win. */
	UPROPERTY(VisibleAnywhere, Category = "Custom Attributes")
	FButtonCode CorrectButtonCode;

	/* Property for the code that the player as input by pressing the buttons. */
	UPROPERTY(VisibleAnywhere, Category = "Custom Attributes")
	FButtonCode GuessedButtonCode;

	UPROPERTY(VisibleAnywhere, Category = "Custom Attributes")
	TArray<FButtonCode> PreviouslyGuessedCodes;

	UPROPERTY(VisibleAnywhere, Category = "Custom Attributes")
	int TotalGuessCount;

	UPROPERTY(VisibleAnywhere, Category = "Custom Attributes")
	int CurrentGuessCount;

	UPROPERTY(VisibleAnywhere, Category = "Custom Attributes")
	int CodeSize;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom Attributes")
	bool bIsGameOver;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom Attributes")
	TEnumAsByte<EGameOverReason> GameOverReason;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Custom Attributes")
	class UMainMenuWidget* MainMenuWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Custom Attributes")
	class UCurrentCodeWidget* CurrentCodeWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Custom Attributes")
	class UPreviousCodesWidget* PreviousCodeWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Custom Attributes")
	class UGameOverWidget* GameOverWidget;

	virtual void Init() override;

	/* Sets Difficulty level, coide size and correct button code based on user input. Called in the MainMenuWidget Blueprint.*/
	UFUNCTION(BlueprintCallable)
	void UpdateDifficulty(TEnumAsByte<EDifficulty> Difficulty);

	UFUNCTION(BlueprintCallable)
	void StoreButtons(TArray<ACustomButton*> ButtonList);

	UFUNCTION(BlueprintCallable)
	void AddButtonToGuess(ACustomButton* Button);

	UFUNCTION()
	void CheckGuess();

	UFUNCTION()
	void GameOver(TEnumAsByte<EGameOverReason> Reason);

	UFUNCTION(BlueprintCallable)
	void ResetGame();
};
