// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "BaseAbility.h"
#include "Interfaces/Gameplay/Descriptions/Cooldownable.h"
#include "Holders/Utility/CooldownableUtility.h"

#include "BaseUltimateAbility.generated.h"

UCLASS()
class LOSTCONNECTION_API UBaseUltimateAbility : 
	public UBaseAbility,
	public ICooldownable
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(Category = Cooldown, Instanced, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	UCooldownableUtility* cooldown;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UBaseUltimateAbility();

	virtual void applyAbility(class ABaseCharacter* target) override;

	virtual void useAbility() override;

	virtual float getCooldown() const final override;

	virtual float& getCurrentCooldownReference() final override;

	virtual float getCurrentCooldown() const final override;

	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	virtual ~UBaseUltimateAbility() = default;
};
