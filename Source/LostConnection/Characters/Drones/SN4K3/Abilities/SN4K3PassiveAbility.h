// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Abilities/BasePassiveAbility.h"
#include "Characters/Drones/SN4K3/SN4K3PassiveAbilityHead.h"
#include "Interfaces/Gameplay/Descriptions/Cooldownable.h"
#include "Holders/Utility/CooldownableUtility.h"

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
		increase,
		decrease
	};

private:
	UPROPERTY(Category = SN4K3, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	int32 naniteMeter;

	UPROPERTY(Category = SN4K3, Instanced, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	UCooldownableUtility* cooldown;

	UPROPERTY(Category = SN4K3, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
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

	void Tick(float DeltaSeconds) override;

	float getCooldown() const override;

	float& getCurrentCooldownReference() override;

	float getCurrentCooldown() const override;

	bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	~USN4K3PassiveAbility() = default;
};
