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
	TWeakObjectPtr<class ABaseCharacter> target;
	
	UPROPERTY(Category = SN4K3, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float distance;

	UPROPERTY(Category = SN4K3, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float thresholdedHealthHeal;

	UPROPERTY(Category = SN4K3, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	FVector2D maxHealDistance;

	UPROPERTY(Category = SN4K3, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	FVector2D linearDecreaseHealDistance;

	UPROPERTY(Category = SN4K3, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float naniteMeterCoefficient;

private:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	USN4K3SecondAbility();

	void setTarget(class ABaseCharacter* target);

	float getDistance() const;

	void applyAbility(class ABaseCharacter* target) override;

	void useAbility() override;

	void deathEventAction() override;

	class IDeathEventsHolder* getDeathEventsHolder() const override;

	~USN4K3SecondAbility() = default;
};
