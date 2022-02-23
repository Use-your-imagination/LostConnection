// Copyright (c) 2022 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Network/NetworkObject.h"
#include "Utility/TimersUtility.h"
#include "Utility/Utility.h"

#include "BaseEnergyShield.generated.h"

#pragma warning(disable: 4458)

UCLASS(BlueprintType, Blueprintable)
class LOSTCONNECTION_API UBaseEnergyShield : public UNetworkObject
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(Category = EnergyShield, EditDefaultsOnly, BlueprintReadOnly)
	FLinearColor energyShieldColor;

	UPROPERTY(Category = EnergyShield, EditDefaultsOnly, BlueprintReadOnly)
	FLinearColor energyShieldInterpColor;

	UPROPERTY(Category = EnergyShield, ReplicatedUsing = onCapacityChange, BlueprintReadOnly)
	float capacity;

	UPROPERTY(Category = EnergyShield, ReplicatedUsing = onCurrentCapacityChange, BlueprintReadOnly)
	float currentCapacity;

	UPROPERTY(Category = EnergyShield, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float rechargeDelay;

	UPROPERTY(Category = EnergyShield, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float rechargeRate;

	UPROPERTY(Category = EnergyShield, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float addedEffectiveness;

	UPROPERTY(Category = EnergyShield, EditDefaultsOnly, BlueprintReadOnly)
	int32 rechargesPerSecond;

	UPROPERTY(Category = EnergyShield, Replicated, BlueprintReadOnly)
	float remainingTimeToRestoreShield;

	UPROPERTY(Category = EnergyShield, Replicated, BlueprintReadOnly)
	bool isRecharging;

	UPROPERTY(Replicated)
	class ABaseCharacter* owner;

	TimersUtility timers;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	virtual void onCapacityChange();

	UFUNCTION()
	virtual void onCurrentCapacityChange();

private:
	void startRechargeDelay();

public:
	UBaseEnergyShield() = default;

	virtual void init(class ABaseCharacter* owner);

	virtual float takeDamage(const TScriptInterface<class IDamageInflictor>& inflictor);

	UFUNCTION(Server, Reliable)
	virtual void restoreShield();

	virtual void onDestroyShield();

	virtual void onStartRechargeShield();

	virtual void onEndRechargeShield();

	virtual void Tick(float DeltaTime);

	const FLinearColor& getEnergyShieldColor() const;

	float getCapacity() const;

	float getCurrentCapacity() const;

	float getRechargeDelay() const;

	float getAddedEffectiveness() const;

	float getRemainingTimeToRestoreShield() const;

	bool getIsRecharging() const;

	virtual ~UBaseEnergyShield() = default;
};

inline float UBaseEnergyShield::getCapacity() const
{
	return capacity;
}

inline float UBaseEnergyShield::getCurrentCapacity() const
{
	return currentCapacity;
}
