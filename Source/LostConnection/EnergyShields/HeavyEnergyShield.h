// Copyright (c) 2022 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "EnergyShields/BaseEnergyShield.h"

#include "HeavyEnergyShield.generated.h"

UCLASS()
class LOSTCONNECTION_API UHeavyEnergyShield : public UBaseEnergyShield
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(Category = HeavyEnergyShield, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float basePoolConversion;

	UPROPERTY(Category = HeavyEnergyShield, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float poolRechargeRate;

	UPROPERTY(Category = HeavyEnergyShield, Replicated, BlueprintReadOnly)
	float poolCapacity;

	UPROPERTY(Category = HeavyEnergyShield, Replicated, BlueprintReadOnly)
	float currentPoolCapacity;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UHeavyEnergyShield() = default;

	float getBasePoolConversion() const;

	float getPoolRechargeRate() const;

	float getPoolCapacity() const;

	float getCurrentPoolCapacity() const;

	void init(class ABaseCharacter* owner) override;

	virtual ~UHeavyEnergyShield() = default;
};
