// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Task.generated.h"

/**
 * 
 */
UCLASS()
class JACKOFALLPERSONAS_API UTask : public UObject
{
	GENERATED_BODY()
	
public:

	UTask() {}

	UTask(FString Title, FString Description, bool bIsCompleted)
	{
		this->Title = Title;
		this->Description = Description;
		this->bIsCompleted = bIsCompleted;
	}

	UPROPERTY()
	FString Title;

	UPROPERTY()
	FString Description;

	UPROPERTY()
	bool bIsCompleted;

	FORCEINLINE FString GetTitle() { return Title; }
	FORCEINLINE FString GetDescription() { return Description; }
	FORCEINLINE bool IsTaskCompleted() { return bIsCompleted; }
};
