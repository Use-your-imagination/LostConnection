// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Components/MaterialBillboardComponent.h"
#include "Components/TextRenderComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "BehaviorTree/BehaviorTree.h"

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

	UPROPERTY(Category = BehaviourTrees, EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UBehaviorTree> main;

	UPROPERTY(Category = BehaviourTrees, EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UBehaviorTree> offensive;

	UPROPERTY(Category = BehaviourTrees, EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UBehaviorTree> movement;

	UPROPERTY(Category = BehaviourTrees, EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UBehaviorTree> other;

protected:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	virtual void deathLogic() override;

	virtual void destroyAssociatedActors();

public:
	ABaseBot();

	virtual int32 getLootPoints() const final override;

	virtual float getSmallAmmoDropChance_Implementation() const final override;

	virtual float getLargeAmmoDropChance_Implementation() const final override;

	virtual float getEnergyAmmoDropChance_Implementation() const final override;

	virtual ~ABaseBot() = default;
};
