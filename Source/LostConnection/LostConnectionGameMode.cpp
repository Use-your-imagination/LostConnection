// Copyright Epic Games, Inc. All Rights Reserved.

#include "LostConnectionGameMode.h"
#include "LostConnectionCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALostConnectionGameMode::ALostConnectionGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
