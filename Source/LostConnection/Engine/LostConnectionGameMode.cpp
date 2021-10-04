#include "LostConnectionGameMode.h"

#include "UObject/ConstructorHelpers.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"

#include "LostConnectionGameState.h"

#pragma warning(disable: 4458)

void ALostConnectionGameMode::BeginPlay()
{
	Super::BeginPlay();

	for (size_t i = 0; i < 1; i++)
	{
		FVector location(FMath::RandRange(-11000.0f, -5900.0f), FMath::RandRange(0.0f, 1000.0f), FMath::RandRange(131.0f, 1650.0f));
		FRotator rotation(0.0f, FMath::RandRange(0.0f, 360.0f), 0.0f);

		GetWorld()->SpawnActor(defaultAI, &location, &rotation);
	}
}

ALostConnectionGameMode::ALostConnectionGameMode()
{
	ConstructorHelpers::FClassFinder<APawn> defaultPawnClassFinder(TEXT("/Game/Drones/BP_BaseDrone"));
	ConstructorHelpers::FClassFinder<APawn> defaultAIClassFinder(TEXT("/Game/AI/Enemies/EnemyBlueprints/Default/BP_DefaultEnemy"));
	ConstructorHelpers::FClassFinder<APlayerController> defaultPlayerControllerClassFinder(TEXT("/Game/Engine/PlayerControllers/BP_LostConnectionPlayerController"));
	ConstructorHelpers::FClassFinder<APlayerState> defaultPlayerStateClassFinder(TEXT("/Game/Engine/PlayerStates/BP_LostConnectionPlayerState"));
	
	count = 1;
	DefaultPawnClass = defaultPawnClassFinder.Class;
	PlayerControllerClass = defaultPlayerControllerClassFinder.Class;
	PlayerStateClass = defaultPlayerStateClassFinder.Class;
	GameStateClass = ALostConnectionGameState::StaticClass();

	defaultAI = defaultAIClassFinder.Class;
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
