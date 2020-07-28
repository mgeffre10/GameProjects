// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomButton.h"
#include "GEOGameInstance.h"

#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "TimerManager.h"

// Sets default values
ACustomButton::ACustomButton()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
	TriggerVolume->SetupAttachment(GetRootComponent());

	TriggerVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerVolume->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	TriggerVolume->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	TriggerVolume->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	ButtonFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonFrame"));
	ButtonFrame->SetupAttachment(GetRootComponent());

	Button = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button"));
	Button->SetupAttachment(ButtonFrame);

	bIsPressed = false;
	ResetDelay = 0;
	OverlappingActors = 0;
}

// Called when the game starts or when spawned
void ACustomButton::BeginPlay()
{
	Super::BeginPlay();

	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ACustomButton::OnOverlapBegin);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &ACustomButton::OnOverlapEnd);

	InitialButtonPosition = Button->GetComponentLocation();
}

void ACustomButton::ResetButton()
{
	if (OverlappingActors == 0)
	{
		bIsPressed = false;
		UGameplayStatics::PlaySoundAtLocation(this, ButtonReleasedSound, GetActorLocation());
		ReleaseButton();
	}
}

void ACustomButton::UpdateButtonPosition(float Z)
{
	FVector Location = InitialButtonPosition;
	Location.Z += Z;
	Button->SetWorldLocation(Location);
}

void ACustomButton::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OverlappingActors++;

	if (!bIsPressed)
	{
		PushButton();
		bIsPressed = true;
		UGameplayStatics::PlaySoundAtLocation(this, ButtonPushedSound, GetActorLocation());
		GetGameInstance<UGEOGameInstance>()->AddButtonToGuess(this);
	}
}

void ACustomButton::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OverlappingActors--;

	if (ResetDelay > 0)
	{
		GetWorldTimerManager().SetTimer(DelayHandle, this, &ACustomButton::ResetButton, ResetDelay);
	}
	else
	{
		ResetButton();
	}
}

