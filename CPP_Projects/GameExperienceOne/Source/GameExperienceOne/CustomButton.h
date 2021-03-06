// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CustomButton.generated.h"

UENUM(BlueprintType)
enum EButtonColor {
	EBC_Blue		UMETA(DisplayName = "Blue"),
	EBC_Green		UMETA(DisplayName = "Green"),
	EBC_Red			UMETA(DisplayName = "Red"),
	EBC_Yellow		UMETA(DisplayName = "Yellow"),
	EBC_MAX
};

UCLASS()
class GAMEEXPERIENCEONE_API ACustomButton : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ACustomButton();

	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class UBoxComponent* TriggerVolume;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UStaticMeshComponent* ButtonFrame;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UStaticMeshComponent* Button;

	UPROPERTY(VisibleAnywhere, Category = "Button Attributes")
	bool bIsPressed;

	UPROPERTY(EditInstanceOnly, Category = "Button Attributes")
	TEnumAsByte<EButtonColor> Color;

	/* This property specifies if the button should set bIsPressed to false after the player has stepped off it for a x number of seconds*/
	UPROPERTY(EditAnywhere, Category = "Button Attributes", meta = (ClampMin = "0"))
	int ResetDelay;

	UPROPERTY(EditAnywhere, Category = "Button Attributes")
	class USoundBase* ButtonPushedSound;

	UPROPERTY(EditAnywhere, Category = "Button Attributes")
	class USoundBase* ButtonReleasedSound;

	FVector InitialButtonPosition;

	FTimerHandle DelayHandle;

	int OverlappingActors;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void ResetButton();

	UFUNCTION(BlueprintImplementableEvent)
	void PushButton();

	UFUNCTION(BlueprintImplementableEvent)
	void ReleaseButton();

	UFUNCTION(BlueprintCallable)
	void UpdateButtonPosition(float Z);
};
