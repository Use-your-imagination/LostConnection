// Copyright (c) 2021 Use Your Imagination

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

	behaviorTree->BlackboardAsset = blackboard;

	if (HasAuthority())
	{
		this->changeToDefaultWeapon();

		GetController<AAIController>()->RunBehaviorTree(behaviorTree);
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
	static ConstructorHelpers::FClassFinder<AAIController> aiControllerFinder(TEXT("/Game/Engine/AIControllers/BP_BaseAIController"));

	static ConstructorHelpers::FObjectFinder<UBlackboardData> blackboardFinder(TEXT("BlackboardData'/Game/AI/Base/BaseBlackboard.BaseBlackboard'"));
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> behaviorTreeFinder(TEXT("BehaviorTree'/Game/AI/Base/BaseBehaviorTree.BaseBehaviorTree'"));

	isAlly = false;

	AIControllerClass = aiControllerFinder.Class;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	blackboard = blackboardFinder.Object;
	behaviorTree = behaviorTreeFinder.Object;
}

bool ABaseBot::offensiveStage_Implementation(const TScriptInterface<IAITargeted>& target)
{
	return true;
}

bool ABaseBot::movementStage_Implementation(const FVector& movementPoint)
{
	return true;
}

bool ABaseBot::otherStage_Implementation()
{
	return true;
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
