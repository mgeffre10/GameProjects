// Fill out your copyright notice in the Description page of Project Settings.


#include "PreviousCodesWidget.h"
#include "CodeWidget.h"
#include "CustomButton.h"
#include "GEOGameInstance.h"

#include "Components/HorizontalBox.h"
#include "Components/VerticalBox.h"

void UPreviousCodesWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPreviousCodesWidget::AddGuessToWidget(TArray<ACustomButton*> Code)
{
	if (PreviousGuesses)
	{
		UGEOGameInstance* GameInstance = GetGameInstance<UGEOGameInstance>();

		int GuessToUpdate = GameInstance->CurrentGuessCount - 1;

		UHorizontalBox* Container = Cast<UHorizontalBox>(PreviousGuesses->GetChildAt(GuessToUpdate));

		UCodeWidget* CodeWidget = Cast<UCodeWidget>(Container->GetChildAt(1));
		CodeWidget->UpdateCodeDisplay(Code);
		CodeWidget->ShowCorrectSelections(Code, GameInstance->CorrectButtonCode.ButtonCode);
	}
}