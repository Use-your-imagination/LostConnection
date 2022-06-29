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

		behaviorTree->BlackboardAsset = blackboard;

		offensiveChain = this->initOffensiveChain();

		movementChain = this->initMovementChain();

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

ActionsChain<TScriptInterface<IAITargeted>> ABaseBot::initOffensiveChain()
{
	ActionsChain<TScriptInterface<IAITargeted>> result;

	result.addAction
	(
		[](const TScriptInterface<IAITargeted>& target) -> bool
		{
			return IsValid(target.GetObject());
		},
		[this](const TScriptInterface<IAITargeted>& target) -> bool
		{
			if (!movementChain.isExecutionEnd())
			{
				GetController<AAIController>()->StopMovement();

				movementChain.resetExecution();
			}

			FRotator newRotation = GetActorRotation();

			newRotation.Yaw = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Cast<AActor>(target.GetObject())->GetActorLocation()).Yaw;

			SetActorRotation(newRotation);

			return true;
		}
	);

	result.addAction
	(
		[](const TScriptInterface<IAITargeted>& target) -> bool
		{
			return IsValid(target.GetObject());
		},
		[this](const TScriptInterface<IAITargeted>& target) -> bool
		{
			this->shoot();
			
			return true;
		}
	);

	result.addAction
	(
		[](const TScriptInterface<IAITargeted>& target) -> bool
		{
			return true;
		},
		[this](const TScriptInterface<IAITargeted>& target) -> bool
		{
			if (resetTime)
			{
				resetTime = FMath::Max(0.0, resetTime - FApp::GetDeltaTime());
			}
			else
			{
				resetTime = 1.0;
			}

			return !StaticCast<bool>(resetTime);
		},
		[](bool) { return true; }
	);

	result.addAction
	(
		[](const TScriptInterface<IAITargeted>& target) -> bool
		{
			return true;
		},
		[this](const TScriptInterface<IAITargeted>& target) -> bool
		{
			this->resetShoot();

			return true;
		}
	);

	return result;
}

ActionsChain<FVector> ABaseBot::initMovementChain()
{
	ActionsChain<FVector> result;

	result.addAction
	(
		[](const FVector& movementPoint) -> bool
		{
			return true;
		},
		[this](const FVector& movementPoint) -> bool
		{
			TObjectPtr<AAIController> controller = GetController<AAIController>();
			FAIRequestID id = controller->GetCurrentMoveRequestID();

			if (id.IsValid())
			{
				return true;
			}

			TObjectPtr<UNavigationSystemV1> navigationSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

			if (!navigationSystem)
			{
				return false;
			}

			FNavLocation moveToLocation;

			navigationSystem->GetRandomReachablePointInRadius(GetActorLocation(), 1000.0f, moveToLocation);

			controller->MoveToLocation(moveToLocation.Location, -1.0f, false);

			return false;
		}
	);

	return result;
}

ABaseBot::ABaseBot() :
	smallAmmoDropChance(45.0f),
	largeAmmoDropChance(45.0f),
	energyAmmoDropChance(45.0f),
	resetTime(0.0)
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
	return offensiveChain.process(target);
}

bool ABaseBot::movementStage_Implementation(const FVector& movementPoint)
{
	return movementChain.process(movementPoint);
}

bool ABaseBot::otherStage_Implementation()
{
	return false;
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
