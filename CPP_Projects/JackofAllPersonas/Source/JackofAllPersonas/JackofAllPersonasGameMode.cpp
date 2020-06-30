// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "JackofAllPersonasGameMode.h"
#include "JackofAllPersonasCharacter.h"
#include "UObject/ConstructorHelpers.h"

AJackofAllPersonasGameMode::AJackofAllPersonasGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
