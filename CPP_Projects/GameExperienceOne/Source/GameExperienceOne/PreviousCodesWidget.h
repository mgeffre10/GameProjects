// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PreviousCodesWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class GAMEEXPERIENCEONE_API UPreviousCodesWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UVerticalBox* PreviousGuesses = nullptr;

	UFUNCTION()
	void AddGuessToWidget(TArray<class ACustomButton*> Code);
};
