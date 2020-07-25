// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UE_LOG(LogTemp, Warning, TEXT("Creating UMainMenuWidget"));

	//UCanvasPanel* CanvasPanel = Cast<UCanvasPanel>(GetRootWidget());

	if (GetRootWidget())
	{
		UE_LOG(LogTemp, Warning, TEXT("RootWidget Not Null"));
	}

	//UE_LOG(LogTemp, Warning, TEXT("Children in GameOverWidget: %d"), CanvasPanel->GetAllChildren().Num());

}