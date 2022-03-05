// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Abilities/BasePassiveAbility.h"
#include "Characters/Drones/SN4K3/SN4K3PassiveAbilityHead.h"
#include "Interfaces/Gameplay/Descriptions/Cooldownable.h"
#include "Utility/CooldownableUtilityObject.h"

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
	UPROPERTY(Category = SN4K3, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	int32 naniteMeter;

	UPROPERTY(Category = SN4K3, Instanced, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	UCooldownableUtilityObject* cooldown;

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

	float& getCurrentCooldownReference() override;

	float getCurrentCooldown() const override;

	bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	~USN4K3PassiveAbility() = default;
};
