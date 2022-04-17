// Copyright (c) 2021 Use-your-imagination

#include "BaseBot.h"

#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "AIController.h"

#include "Weapons/Pistols/Gauss.h"
#include "Engine/LostConnectionGameMode.h"
#include "Statuses/Ailments/SwarmAilment.h"
#include "Loot/LootManager.h"

void ABaseBot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseBot::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		this->changeToDefaultWeapon();
	}
}

void ABaseBot::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseBot, lootPointsReward);

	DOREPLIFETIME(ABaseBot, smallAmmoDropChance);

	DOREPLIFETIME(ABaseBot, largeAmmoDropChance);

	DOREPLIFETIME(ABaseBot, energyAmmoDropChance);
}

void ABaseBot::deathLogic()
{
	TObjectPtr<UWorld> world = GetWorld();
	TObjectPtr<ALostConnectionGameState> gameState = world->GetGameState<ALostConnectionGameState>();

	if (!isAlly)
	{
		gameState->verteilenLootPoints(this);
	}

	gameState->dropAmmo(this);

	this->destroyAssociatedActors();

	if (!isAlly)
	{
		world->GetAuthGameMode<ALostConnectionGameMode>()->getSpawnManager().notify(world);
	}
}

void ABaseBot::destroyAssociatedActors()
{
	TObjectPtr<AAIController> controller = GetController<AAIController>();
	TObjectPtr<ALostConnectionPlayerState> playerState = Utility::getPlayerState(this);
	TObjectPtr<AInventory> inventory = playerState->getInventory();

	inventory->Destroy();

	playerState->Destroy();

	controller->UnPossess();

	controller->Destroy();

	Destroy();
}

ABaseBot::ABaseBot() :
	smallAmmoDropChance(45.0f),
	largeAmmoDropChance(45.0f),
	energyAmmoDropChance(45.0f)
{
	static ConstructorHelpers::FClassFinder<AAIController> aiControllerFinder(TEXT("/Game/Engine/BP_LostConnectionAIController"));
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> mainBehaviorTree(TEXT("BehaviorTree'/Game/AI/Behavior/DefaultMain.DefaultMain'"));
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> defaultOffensiveBehaviorTree(TEXT("BehaviorTree'/Game/AI/Behavior/DefaultOffensive.DefaultOffensive'"));
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> defaultMovementBehaviorTree(TEXT("BehaviorTree'/Game/AI/Behavior/DefaultMovement.DefaultMovement'"));
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> defaultOtherBehaviorTree(TEXT("BehaviorTree'/Game/AI/Behavior/DefaultOther.DefaultOther'"));

	isAlly = false;
	main = mainBehaviorTree.Object;
	offensive = defaultOffensiveBehaviorTree.Object;
	movement = defaultMovementBehaviorTree.Object;
	other = defaultOtherBehaviorTree.Object;

	AIControllerClass = aiControllerFinder.Class;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

int32 ABaseBot::getLootPoints() const
{
	return lootPointsReward;
}

float ABaseBot::getSmallAmmoDropChance_Implementation() const
{
	return smallAmmoDropChance;
}

float ABaseBot::getLargeAmmoDropChance_Implementation() const
{
	return largeAmmoDropChance;
}

float ABaseBot::getEnergyAmmoDropChance_Implementation() const
{
	return energyAmmoDropChance;
}
