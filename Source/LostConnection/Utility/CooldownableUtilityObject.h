// Copyright (c) 2022 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/NoExportTypes.h"
#include "Net/UnrealNetwork.h"

#include "Interfaces/Gameplay/Descriptions/Cooldownable.h"

#include "CooldownableUtilityObject.generated.h"

UCLASS(BlueprintType, DefaultToInstanced)
class LOSTCONNECTION_API UCooldownableUtilityObject : 
	public UObject,
	public ICooldownable
{
	GENERATED_BODY()
	
private:
	bool IsSupportedForNetworking() const override;

private:
	UPROPERTY(Category = Cooldown, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float cooldown;

	UPROPERTY(Category = Cooldown, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float currentCooldown;

private:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UCooldownableUtilityObject() = default;

	float getCooldown() const override;

	float& getCurrentCooldownReference() override;

	float getCurrentCooldown() const override;

	~UCooldownableUtilityObject() = default;
};
