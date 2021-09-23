#include "LostConnectionGameMode.h"

#include "UObject/ConstructorHelpers.h"
#include "GameFramework/HUD.h"

#include "LostConnectionPlayerState.h"
#include "LostConnectionGameState.h"

#pragma warning(disable: 4458)

void ALostConnectionGameMode::BeginPlay()
{
	Super::BeginPlay();

#ifndef UE_BUILD_DEBUG
	for (size_t i = 0; i < 3; i++)
	{
		FVector location(FMath::RandRange(-11000.0f, -5900.0f), FMath::RandRange(0.0f, 1000.0f), FMath::RandRange(131.0f, 1650.0f));
		FRotator rotation(0.0f, FMath::RandRange(0.0f, 360.0f), 0.0f);

		GetWorld()->SpawnActor(defaultAI, &location, &rotation);
	}
#endif // !UE_BUILD_DEBUG
}

ALostConnectionGameMode::ALostConnectionGameMode()
{
	ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Characters/BP_BaseDrone"));
	ConstructorHelpers::FClassFinder<AHUD> PlayerHUDBPClass(TEXT("/Game/HUD/BP_HUD"));
	ConstructorHelpers::FClassFinder<APawn> DefaultAIClass(TEXT("/Game/AI/Enemies/EnemyBlueprints/Default/BP_DefaultEnemy"));

	DefaultPawnClass = PlayerPawnBPClass.Class;
	PlayerStateClass = ALostConnectionPlayerState::StaticClass();
	HUDClass = PlayerHUDBPClass.Class;
	GameStateClass = ALostConnectionGameState::StaticClass();

	defaultAI = DefaultAIClass.Class;
}

void ALostConnectionGameMode::spawnAI_Implementation() const
{
	FActorSpawnParameters parameters;

	parameters.bNoFail = true;
	parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	for (size_t i = 0; i < count; i++)
	{
		FRotator rotation(0.0f, FMath::RandRange(0.0f, 360.0f), 0.0f);

		GetWorld()->SpawnActor(defaultAI, &location, &rotation, parameters);
	}
}
