#include "LostConnectionGameMode.h"

#include "UObject/ConstructorHelpers.h"
#include "GameFramework/HUD.h"

#include "LostConnectionPlayerState.h"
#include "LostConnectionGameState.h"

void ALostConnectionGameMode::BeginPlay()
{
	Super::BeginPlay();

	/// @brief Second week release ai spawning
	for (size_t i = 0; i < 0; i++)
	{
		FVector location(FMath::RandRange(-11000.0f, -5900.0f), FMath::RandRange(0.0f, 1000.0f), FMath::RandRange(131.0f, 1650.0f));
		FRotator rotation(0.0f, FMath::RandRange(0.0f, 360.0f), 0.0f);
	
		GetWorld()->SpawnActor(defaultAI, &location, &rotation);
	}
}

ALostConnectionGameMode::ALostConnectionGameMode()
{
	ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/LostConnectionCPP/Blueprints/BP_LostConnectionCharacter"));
	ConstructorHelpers::FClassFinder<AHUD> PlayerHUDBPClass(TEXT("/Game/HUD/BP_HUD"));
	ConstructorHelpers::FClassFinder<APawn> DefaultAIClass(TEXT("/Game/AI/Enemies/EnemyBlueprints/Default/BP_DefaultEnemy"));

	DefaultPawnClass = PlayerPawnBPClass.Class;
	PlayerStateClass = ALostConnectionPlayerState::StaticClass();
	HUDClass = PlayerHUDBPClass.Class;
	GameStateClass = ALostConnectionGameState::StaticClass();

	defaultAI = DefaultAIClass.Class;
}
