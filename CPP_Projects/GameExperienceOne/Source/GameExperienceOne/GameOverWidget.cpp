// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverWidget.h"
#include "Components/CanvasPanel.h"

void UGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UE_LOG(LogTemp, Warning, TEXT("Creating GameOverWidget"));

	//UCanvasPanel* CanvasPanel = Cast<UCanvasPanel>(GetRootWidget());

	if (GetRootWidget())
	{
		UE_LOG(LogTemp, Warning, TEXT("RootWidget Not Null"));
	}

	//UE_LOG(LogTemp, Warning, TEXT("Children in GameOverWidget: %d"), CanvasPanel->GetAllChildren().Num());

}