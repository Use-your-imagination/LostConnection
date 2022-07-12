// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Abilities/BaseAbility.h"
#include "Interfaces/Holders/AilmentInflictorHolder.h"

#include "SN4K3FirstAbility.generated.h"

UCLASS()
class LOSTCONNECTION_API USN4K3FirstAbility :
	public UBaseAbility,
	public IAilmentInflictorHolder
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = SN4K3, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	float distance;

	UPROPERTY(Category = SN4K3, Instanced, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TObjectPtr<UAilmentInflictorUtility> ailmentInflictorUtility;

private:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	USN4K3FirstAbility();

	void initAbility(const TObjectPtr<AController>& instigator) override;

	void applyAbility(class ABaseCharacter* target) override;

	void useAbility() override;

	bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;
	
	UAilmentInflictorUtility* getAilmentInflictorUtility() const override;

	~USN4K3FirstAbility() = default;
};
