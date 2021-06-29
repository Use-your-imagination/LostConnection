#include "LostConnectionGameMode.h"

#include "UObject/ConstructorHelpers.h"

void ALostConnectionGameMode::BeginPlay()
{
	Super::BeginPlay();
}

ALostConnectionGameMode::ALostConnectionGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/LostConnectionCPP/Blueprints/BP_LostConnectionCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
