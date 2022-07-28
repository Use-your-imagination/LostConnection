// Copyright (c) 2022 Use Your Imagination

#include "BaseEnergyShield.h"

#include "Interfaces/Gameplay/Descriptions/Base/DamageInflictor.h"
#include "Interfaces/Gameplay/Descriptions/Base/DamageReceiver.h"
#include "Characters/BaseCharacter.h"

void UBaseEnergyShield::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UBaseEnergyShield, capacity);

	DOREPLIFETIME(UBaseEnergyShield, currentCapacity);

	DOREPLIFETIME(UBaseEnergyShield, rechargeDelay);

	DOREPLIFETIME(UBaseEnergyShield, rechargeRate);

	DOREPLIFETIME(UBaseEnergyShield, addedEffectiveness);

	DOREPLIFETIME(UBaseEnergyShield, remainingTimeToRestoreShield);

	DOREPLIFETIME(UBaseEnergyShield, isRecharging);

	DOREPLIFETIME(UBaseEnergyShield, owner);
}

void UBaseEnergyShield::onCapacityChange()
{
	if (owner)
	{
		owner->onHealthChange();
	}
}

void UBaseEnergyShield::onCurrentCapacityChange()
{
	if (owner)
	{
		owner->onCurrentHealthChange();
	}
}

void UBaseEnergyShield::startRechargeDelay()
{
	remainingTimeToRestoreShield = rechargeDelay;

	isRecharging = false;
}

void UBaseEnergyShield::init(const TObjectPtr<ABaseCharacter>& owner)
{
	this->owner = owner;

	capacity = owner->getStartEnergyShieldCapacity();
	currentCapacity = capacity;

	timers.addTimer([this]()
		{
			if (isRecharging)
			{
				currentCapacity = FMath::Min(capacity, currentCapacity + capacity * Utility::fromPercent(rechargeRate) / rechargesPerSecond);

				this->onCurrentCapacityChange();

				if (currentCapacity == capacity)
				{
					this->onEndRechargeShield();
				}
			}
		}, 1.0f / rechargesPerSecond);
}

float UBaseEnergyShield::takeDamageFromInflictor(const TScriptInterface<IDamageInflictor>& inflictor, const TScriptInterface<IDamageReceiver>& receiver)
{
	float tem = currentCapacity - inflictor->calculateTotalDamage(receiver);
	float remainingDamage = 0.0f;

	if (tem <= 0.0f)
	{
		remainingDamage = FMath::Abs(tem);

		currentCapacity = 0.0f;

		this->onDestroyShield();
	}
	else
	{
		currentCapacity = tem;
	}

	this->startRechargeDelay();

	this->onCurrentCapacityChange();

	return remainingDamage;
}

void UBaseEnergyShield::restoreShield_Implementation()
{
	this->onStartRechargeShield();
}

void UBaseEnergyShield::onDestroyShield()
{
	this->startRechargeDelay();
}

void UBaseEnergyShield::onStartRechargeShield()
{
	isRecharging = true;
}

void UBaseEnergyShield::onEndRechargeShield()
{
	isRecharging = false;
}

void UBaseEnergyShield::Tick(float DeltaSeconds)
{
	timers.processTimers(DeltaSeconds);

	if (remainingTimeToRestoreShield)
	{
		remainingTimeToRestoreShield = FMath::Max(0.0f, remainingTimeToRestoreShield - DeltaSeconds);

		if (!remainingTimeToRestoreShield)
		{
			this->restoreShield();
		}
	}
}

const FLinearColor& UBaseEnergyShield::getEnergyShieldColor() const
{
	return energyShieldColor;
}

float UBaseEnergyShield::getRechargeDelay() const
{
	return rechargeDelay;
}

float UBaseEnergyShield::getAddedEffectiveness() const
{
	return addedEffectiveness;
}

float UBaseEnergyShield::getRemainingTimeToRestoreShield() const
{
	return remainingTimeToRestoreShield;
}

bool UBaseEnergyShield::getIsRecharging() const
{
	return isRecharging;
}
