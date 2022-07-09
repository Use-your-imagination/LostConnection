// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Abilities/BaseAbility.h"
#include "Interfaces/Gameplay/Descriptions/Observers/OnDeathEvent.h"

#include "SN4K3SecondAbility.generated.h"

UCLASS()
class LOSTCONNECTION_API USN4K3SecondAbility :
	public UBaseAbility,
	public IOnDeathEvent
{
	GENERATED_BODY()

private:
	TWeakInterfacePtr<class IDeathEventsHolder> holder;
	
	UPROPERTY(Category = SN4K3, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	float distance;

	UPROPERTY(Category = SN4K3, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	float thresholdedHealthHeal;

	UPROPERTY(Category = SN4K3, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	FVector2D maxHealDistance;

	UPROPERTY(Category = SN4K3, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	FVector2D linearDecreaseHealDistance;

	UPROPERTY(Category = SN4K3, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	float naniteMeterCoefficient;

private:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	USN4K3SecondAbility();

	float getDistance() const;

	void applyAbility(class ABaseCharacter* target) override;

	void useAbility() override;

	void deathEventAction(TObjectPtr<class ABaseCharacter> character) override;

	TWeakInterfacePtr<class IDeathEventsHolder>& getDeathEventsHolder() override;

	~USN4K3SecondAbility() = default;
};
