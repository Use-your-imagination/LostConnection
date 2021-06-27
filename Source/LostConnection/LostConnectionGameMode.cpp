// Copyright Epic Games, Inc. All Rights Reserved.

#include "UObject/ConstructorHelpers.h"

#include "LostConnectionGameMode.h"
#include "LostConnectionCharacter.h"

ALostConnectionGameMode::ALostConnectionGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
