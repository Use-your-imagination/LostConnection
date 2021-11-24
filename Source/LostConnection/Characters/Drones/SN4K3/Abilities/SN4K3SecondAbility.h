// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Abilities/BaseAbility.h"
#include "Interfaces/Gameplay/Descriptions/Observers/GameplayEvents/OnDeathEvent.h"

#include "SN4K3SecondAbility.generated.h"

UCLASS()
class LOSTCONNECTION_API USN4K3SecondAbility :
	public UBaseAbility,
	public IOnDeathEvent
{
	GENERATED_BODY()

private:
	class ABaseCharacter* target;
	
	UPROPERTY(Category = SN4K3, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float distance;

	UPROPERTY(Category = SN4K3, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float thresholdedHealthHeal;

	UPROPERTY(Category = SN4K3, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	FVector2D maxHealDistance;

	UPROPERTY(Category = SN4K3, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	FVector2D linearDecreaseHealDistance;

private:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	USN4K3SecondAbility();

	float getDistance() const;

	void applyAbility(class ABaseCharacter* target) override;

	void useAbility() override;

	void deathEventAction() override;

	class IDeathEventsHolder* getDeathEventsHolder() const override;

	~USN4K3SecondAbility() = default;
};
