// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeWidget.h"
#include "CustomButton.h"
#include "GEOGameInstance.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Border.h"
#include "Components/CanvasPanel.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"


void UCodeWidget::NativeConstruct()
{
	// Call the Blueprint "Event Construct" node
	Super::NativeConstruct();

	// CodeContainer can be nullptr if we haven't created it in the
	// Blueprint subclass
	if (CodeContainer)
	{
		UGEOGameInstance* GameInstance = GetGameInstance<UGEOGameInstance>();

		int CodeSize = GameInstance->CodeSize;
		ButtonCode = GameInstance->GuessedButtonCode.ButtonCode;

		for (int i = 0; i < CodeSize; i++)
		{
			FLinearColor BorderColor = FLinearColor::Gray;

			UBorder* Border = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass(), FName(TEXT("CodeEntry" + i)));

			UHorizontalBoxSlot* BorderSlot = Cast<UHorizontalBoxSlot>(CodeContainer->AddChild(Border));
			

			FSlateChildSize BorderSize;
			BorderSize.SizeRule = ESlateSizeRule::Fill;
			
			FMargin BorderPadding = FMargin(10.f);

			/*switch (GameInstance->DifficultyLevel)
			{
				case EDifficulty::ED_Easy:
					BorderPadding = FMargin(50.f, 100.f);
					break;
				case EDifficulty::ED_Medium:
					BorderPadding = FMargin(20.f);
					break;
				case EDifficulty::ED_Hard:
					BorderPadding = FMargin(10.f, 30.f);
					break;
			}*/

			BorderSlot->SetSize(BorderSize);
			BorderSlot->SetPadding(BorderPadding);

			if (ButtonCode.Num())
			{
				switch (ButtonCode[i]->Color)
				{
					case EButtonColor::EBC_Blue:
						BorderColor = FLinearColor::Blue;
						break;
					case EButtonColor::EBC_Green:
						BorderColor = FLinearColor::Green;
						break;
					case EButtonColor::EBC_Yellow:
						BorderColor = FLinearColor::Yellow;
						break;
					case EButtonColor::EBC_Red:
						BorderColor = FLinearColor::Red;
						break;
				}
			}

			Border->SetBrushColor(BorderColor);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CodeContainer nullptr"));
	}
}

void UCodeWidget::UpdateCodeDisplay(TArray<ACustomButton*> Code)
{
	for (int i = 0; i < Code.Num(); i++)
	{
		ACustomButton* Button = Code[i];
		UBorder* Border = Cast<UBorder>(CodeContainer->GetChildAt(i));

		FLinearColor BorderColor = FLinearColor::Gray;

		switch (Button->Color)
		{
			case EButtonColor::EBC_Blue:
				BorderColor = FLinearColor::Blue;
				break;
			case EButtonColor::EBC_Green:
				BorderColor = FLinearColor::Green;
				break;
			case EButtonColor::EBC_Yellow:
				BorderColor = FLinearColor::Yellow;
				break;
			case EButtonColor::EBC_Red:
				BorderColor = FLinearColor::Red;
				break;
		}

		Border->SetBrushColor(BorderColor);
	}
}

void UCodeWidget::ResetCodeDisplay()
{
	TArray<UWidget*> WidgetList = CodeContainer->GetAllChildren();

	for (UWidget* Widget : WidgetList)
	{
		UBorder* Border = Cast<UBorder>(Widget);
		Border->SetBrushColor(FLinearColor::Gray);
	}
}