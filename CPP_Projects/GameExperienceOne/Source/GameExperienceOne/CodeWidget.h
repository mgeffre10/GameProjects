// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CodeWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEEXPERIENCEONE_API UCodeWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	class UTexture2D* CheckmarkImage;

	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UHorizontalBox* CodeContainer = nullptr;

	UPROPERTY(BlueprintReadWrite)
	TArray<class ACustomButton*> ButtonCode;

	void UpdateCodeDisplay(TArray<ACustomButton*> Code);

	void ShowCorrectSelections(TArray<ACustomButton*> GuessedCode, TArray<ACustomButton*> CorrectCode);

	void ResetCodeDisplay();
};
