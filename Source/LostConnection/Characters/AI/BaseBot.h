// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"

#include "Characters/BaseCharacter.h"
#include "Utility/Utility.h"
#include "Interfaces/Economy/LootPointsGiver.h"
#include "Interfaces/Loot/AmmoDropable.h"
#include "AI/ActionsChain.h"

#include "BaseBot.generated.h"

UCLASS(Abstract)
class LOSTCONNECTION_API ABaseBot :
	public ABaseCharacter,
	public ILootPointsGiver,
	public IAmmoDropable
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = Economy, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	int32 lootPointsReward;

	UPROPERTY(Category = "Loot|Ammo", EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float smallAmmoDropChance;

	UPROPERTY(Category = "Loot|Ammo", EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float largeAmmoDropChance;

	UPROPERTY(Category = "Loot|Ammo", EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float energyAmmoDropChance;

	UPROPERTY(Category = "AI|Assets", EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UBlackboardData> blackboard;

	UPROPERTY(Category = "AI|Assets", EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UBehaviorTree> behaviorTree;

	ActionsChain<TScriptInterface<IAITargeted>> offensiveChain;
	ActionsChain<FVector> movementChain;
	double resetTime;

protected:
	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	virtual void destroyAssociatedActors();

	virtual void deathLogic() override;

protected:
	virtual ActionsChain<TScriptInterface<IAITargeted>> initOffensiveChain();

	virtual ActionsChain<FVector> initMovementChain();

public:
	ABaseBot();

	UFUNCTION(Category = Offensive, BlueprintNativeEvent, BlueprintCallable)
	bool offensiveStage(const TScriptInterface<IAITargeted>& target);

	UFUNCTION(Category = Offensive, BlueprintNativeEvent, BlueprintCallable)
	bool movementStage(const FVector& movementPoint);

	UFUNCTION(Category = Offensive, BlueprintNativeEvent, BlueprintCallable)
	bool otherStage();

	virtual int32 getLootPoints() const final override;

	virtual float getSmallAmmoDropChance_Implementation() const final override;

	virtual float getLargeAmmoDropChance_Implementation() const final override;

	virtual float getEnergyAmmoDropChance_Implementation() const final override;

	virtual ~ABaseBot() = default;
};
