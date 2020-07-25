// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CurrentCodeWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class GAMEEXPERIENCEONE_API UCurrentCodeWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UCodeWidget* CodeWidget = nullptr;

};
