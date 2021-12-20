// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Abilities/BasePassiveAbility.h"
#include "Characters/Drones/SN4K3/SN4K3PassiveAbilityHead.h"
#include "Interfaces/Gameplay/Descriptions/Cooldownable.h"

#include "SN4K3PassiveAbility.generated.h"

UCLASS()
class LOSTCONNECTION_API USN4K3PassiveAbility : 
	public UBasePassiveAbility,
	public ICooldownable
{
	GENERATED_BODY()

private:
	enum class directionTypes
	{
		up,
		down
	};

private:
	UPROPERTY(Category = SN4K3, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	int32 naniteMeter;

	UPROPERTY(Category = SN4K3, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float cooldown;

	UPROPERTY(Category = SN4K3, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float currentCooldown;

	UPROPERTY(Category = SN4K3, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ASN4K3PassiveAbilityHead> headClass;

	float lastTimeAbilityUsed;

	directionTypes type;

private:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
public:
	USN4K3PassiveAbility();

	void resetLastTimeAbilityUsed();

	int32 getNaniteMeter() const;

	void applyAbility(class ABaseCharacter* target) override;

	void useAbility() override;

	void Tick(float DeltaTime) override;

	float getCooldown() const override;

	float& getCurrentCooldown() override;

	~USN4K3PassiveAbility() = default;
};
