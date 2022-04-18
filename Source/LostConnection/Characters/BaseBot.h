// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Components/MaterialBillboardComponent.h"
#include "Components/TextRenderComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"

#include "BaseCharacter.h"
#include "Utility/Utility.h"
#include "Interfaces/Economy/LootPointsGiver.h"
#include "Interfaces/Loot/AmmoDropable.h"

#include "BaseBot.generated.h"

UCLASS()
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

	UPROPERTY(Category = BehaviorTrees, EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UBehaviorTree> mainTree;

	UPROPERTY(Category = BehaviorTrees, EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UBehaviorTree> offensiveTree;

	UPROPERTY(Category = BehaviorTrees, EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UBehaviorTree> movementTree;

	UPROPERTY(Category = BehaviorTrees, EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UBehaviorTree> otherTree;

	UPROPERTY(Category = Blackboards, EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UBlackboardData> mainBlackboard;

	UPROPERTY(Category = Blackboards, EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UBlackboardData> offensiveBlackboard;

	UPROPERTY(Category = Blackboards, EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UBlackboardData> movementBlackboard;

	UPROPERTY(Category = Blackboards, EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UBlackboardData> otherBlackboard;

protected:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	virtual void destroyAssociatedActors();

	virtual void deathLogic() override;

public:
	ABaseBot();

	virtual int32 getLootPoints() const final override;

	virtual float getSmallAmmoDropChance_Implementation() const final override;

	virtual float getLargeAmmoDropChance_Implementation() const final override;

	virtual float getEnergyAmmoDropChance_Implementation() const final override;

	virtual ~ABaseBot() = default;
};
