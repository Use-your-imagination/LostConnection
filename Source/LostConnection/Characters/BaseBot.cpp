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

	mainTree->BlackboardAsset = mainBlackboard;
	offensiveTree->BlackboardAsset = offensiveBlackboard;
	movementTree->BlackboardAsset = movementBlackboard;
	otherTree->BlackboardAsset = otherBlackboard;

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

ABaseBot::ABaseBot() :
	smallAmmoDropChance(45.0f),
	largeAmmoDropChance(45.0f),
	energyAmmoDropChance(45.0f)
{
	static ConstructorHelpers::FClassFinder<AAIController> aiControllerFinder(TEXT("/Game/Engine/AIControllers/BP_LostConnectionAIController"));

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> mainTreeFinder(TEXT("BehaviorTree'/Game/AI/Base/BehaviorTrees/BaseMainTree.BaseMainTree'"));
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> offensiveTreeFinder(TEXT("BehaviorTree'/Game/AI/Base/BehaviorTrees/BaseOffensiveTree.BaseOffensiveTree'"));
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> movementTreeFinder(TEXT("BehaviorTree'/Game/AI/Base/BehaviorTrees/BaseMovementTree.BaseMovementTree'"));
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> otherTreeFinder(TEXT("BehaviorTree'/Game/AI/Base/BehaviorTrees/BaseOtherTree.BaseOtherTree'"));

	static ConstructorHelpers::FObjectFinder<UBlackboardData> mainBlackboardFinder(TEXT("BlackboardData'/Game/AI/Base/Blackboards/BaseMainBlackboard.BaseMainBlackboard'"));
	static ConstructorHelpers::FObjectFinder<UBlackboardData> offensiveBlackboardFinder(TEXT("BlackboardData'/Game/AI/Base/Blackboards/BaseOffensiveBlackboard.BaseOffensiveBlackboard'"));
	static ConstructorHelpers::FObjectFinder<UBlackboardData> movementBlackboardFinder(TEXT("BlackboardData'/Game/AI/Base/Blackboards/BaseMovementBlackboard.BaseMovementBlackboard'"));
	static ConstructorHelpers::FObjectFinder<UBlackboardData> otherBlackboardFinder(TEXT("BlackboardData'/Game/AI/Base/Blackboards/BaseOtherBlackboard.BaseOtherBlackboard'"));

	isAlly = false;

	mainTree = mainTreeFinder.Object;
	offensiveTree = offensiveTreeFinder.Object;
	movementTree = movementTreeFinder.Object;
	otherTree = otherTreeFinder.Object;

	mainBlackboard = mainBlackboardFinder.Object;
	offensiveBlackboard = offensiveBlackboardFinder.Object;
	movementBlackboard = movementBlackboardFinder.Object;
	otherBlackboard = otherBlackboardFinder.Object;

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
