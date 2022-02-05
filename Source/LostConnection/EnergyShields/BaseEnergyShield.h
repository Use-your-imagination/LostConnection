// Copyright (c) 2022 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Network/NetworkObject.h"

#include "BaseEnergyShield.generated.h"

UCLASS(BlueprintType, Blueprintable)
class LOSTCONNECTION_API UBaseEnergyShield : public UNetworkObject
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(Category = EnergyShield, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float capacity;

	UPROPERTY(Category = EnergyShield, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float rechargeDelay;

	UPROPERTY(Category = EnergyShield, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float rechargeRate;

	UPROPERTY(Category = EnergyShield, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float addedEffectiveness;

	UPROPERTY(Category = EnergyShield, Replicated, BlueprintReadOnly)
	float remainingTimeToRestoreShield;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UBaseEnergyShield() = default;

	UFUNCTION(Server, Reliable)
	void restoreShield();

	virtual void onDestroyShield();

	virtual void onRestoreShield();

	virtual void Tick(float DeltaTime);

	virtual ~UBaseEnergyShield() = default;
};
