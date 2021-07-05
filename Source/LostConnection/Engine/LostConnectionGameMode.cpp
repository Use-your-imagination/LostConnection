#include "LostConnectionGameMode.h"

#include "UObject/ConstructorHelpers.h"
#include "GameFramework/HUD.h"

#include "LostConnectionPlayerState.h"

void ALostConnectionGameMode::BeginPlay()
{
	Super::BeginPlay();
}

ALostConnectionGameMode::ALostConnectionGameMode()
{
	/*static*/ ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/LostConnectionCPP/Blueprints/BP_LostConnectionCharacter"));
	/*static*/ ConstructorHelpers::FClassFinder<AHUD> PlayerHUDBPClass(TEXT("/Game/HUD/BP_HUD"));

	DefaultPawnClass = PlayerPawnBPClass.Class;
	PlayerStateClass = ALostConnectionPlayerState::StaticClass();
	HUDClass = PlayerHUDBPClass.Class;
}
