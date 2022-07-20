// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Network/NetworkObject.h"
#include "Interfaces/Gameplay/Descriptions/Cooldownable.h"

#include "CooldownableUtility.generated.h"

UCLASS(BlueprintType, DefaultToInstanced, EditInlineNew)
class LOSTCONNECTION_API UCooldownableUtility : 
	public UNetworkObject,
	public ICooldownable
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Category = Cooldown, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	float cooldown;

	UPROPERTY(Category = Cooldown, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	float currentCooldown;

private:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UCooldownableUtility() = default;

	float getCooldown() const override;

	float& getCurrentCooldownReference() override;

	float getCurrentCooldown() const override;

	~UCooldownableUtility() = default;
};
