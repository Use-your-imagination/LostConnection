#include "LostConnectionGameMode.h"

#include "UObject/ConstructorHelpers.h"

ALostConnectionGameMode::ALostConnectionGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/LostConnectionCPP/Blueprints/LostConnectionCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
