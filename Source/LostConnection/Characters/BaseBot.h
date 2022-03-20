// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Components/MaterialBillboardComponent.h"
#include "Components/TextRenderComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

#include "BaseCharacter.h"
#include "Utility/Utility.h"
#include "Interfaces/Economy/LootPointsGiver.h"

#include "BaseBot.generated.h"

UCLASS()
class LOSTCONNECTION_API ABaseBot :
	public ABaseCharacter,
	public ILootPointsGiver
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = Economy, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	int32 lootPointsReward;

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

	virtual ~ABaseBot() = default;
};
