// Copyright (c) 2021 Use Your Imagination

#include "BaseBot.h"

#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "AIController.h"
#include "Kismet/KismetMathLibrary.h"
#include "NavigationSystem.h"

#include "Weapons/Pistols/Gauss.h"
#include "Engine/LostConnectionGameMode.h"
#include "Statuses/Ailments/SwarmAilment.h"
#include "Loot/LootManager.h"
#include "WorldPlaceables/AI/WavesController.h"

void ABaseBot::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ABaseBot::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		this->changeToDefaultWeapon();

		this->runDefaultBehavior();
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

void ABaseBot::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	behaviorTree->BlackboardAsset = blackboard;

	chasingBehaviorTree->BlackboardAsset = chasingBlackboard;
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
	TObjectPtr<ALostConnectionGameState> gameState = Utility::getGameState(this);

	if (!isAlly)
	{
		gameState->verteilenLootPoints(this);
	}

	gameState->dropAmmo(this);

	this->destroyAssociatedActors();

	if (!isAlly)
	{
		Cast<AWavesController>(UGameplayStatics::GetActorOfClass(this, AWavesController::StaticClass()))->getSpawnManager().notify();
	}
}

ABaseBot::ABaseBot() :
	isChaser(true),
	smallAmmoDropChance(45.0f),
	largeAmmoDropChance(45.0f),
	energyAmmoDropChance(45.0f)
{
	static ConstructorHelpers::FClassFinder<AAIController> aiControllerFinder(TEXT("/Game/Engine/AIControllers/BP_BaseAIController"));

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> behaviorTreeFinder(TEXT("BehaviorTree'/Game/AI/Base/BaseBehaviorTree.BaseBehaviorTree'"));
	static ConstructorHelpers::FObjectFinder<UBlackboardData> blackboardFinder(TEXT("BlackboardData'/Game/AI/Base/BaseBlackboard.BaseBlackboard'"));

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> chasingBehaviorTreeFinder(TEXT("BehaviorTree'/Game/AI/Base/BaseChasingBehaviorTree.BaseChasingBehaviorTree'"));
	static ConstructorHelpers::FObjectFinder<UBlackboardData> chasingBlackboardFinder(TEXT("BlackboardData'/Game/AI/Base/BaseChasingBlackboard.BaseChasingBlackboard'"));

	isAlly = false;

	AIControllerClass = aiControllerFinder.Class;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	behaviorTree = behaviorTreeFinder.Object;
	blackboard = blackboardFinder.Object;

	chasingBehaviorTree = chasingBehaviorTreeFinder.Object;
	chasingBlackboard = chasingBlackboardFinder.Object;
}

void ABaseBot::runDefaultBehavior_Implementation()
{
	GetController<AAIController>()->RunBehaviorTree(behaviorTree);
}

void ABaseBot::runChasingBehavior_Implementation()
{
	GetController<AAIController>()->RunBehaviorTree(chasingBehaviorTree);
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
