// Copyright (c) 2021 Use Your Imagination

#include "BaseStatus.h"

#include "NiagaraFunctionLibrary.h"

#include "Interfaces/Gameplay/Statuses/Base/StatusReceiver.h"
#include "Characters/BaseCharacter.h"
#include "Utility/Utility.h"
#include "Engine/LostConnectionGameState.h"

#pragma warning(disable: 4458)

FString UBaseStatus::getStatusCountKey() const
{
	return this->getStatusName() + "Count";
}

void UBaseStatus::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UBaseStatus, duration);

	DOREPLIFETIME(UBaseStatus, currentDuration);
}

FString UBaseStatus::getStatusName() const
{
	PURE_VIRTUAL(UBaseStatus::getStatusName, return "";);
}

int32 UBaseStatus::calculateUnderStatusEffect() const
{
	return 1;
}

void UBaseStatus::applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<IStatusReceiver>& target, const FHitResult& hit)
{
	this->target = StaticCast<IStatusReceiver*>(target.GetInterface());

	inflictorDamage = inflictor->getBaseDamage();

	inflictorAddedDamage = inflictor->getAddedDamage();

	inflictorAdditionalDamage = inflictor->getAdditionalDamage();

	inflictorMoreDamageCoefficients = inflictor->getMoreDamageCoefficients();

	inflictorIncreaseDamageCoefficients = inflictor->getIncreaseDamageCoefficients();

	target->addStatus(this);

	target->spawnStatusVFX(onApplyStatus, hit);

	target->setUnderStatusIntVariable(this->getStatusCountKey(), this->calculateUnderStatusEffect());
}

bool UBaseStatus::applyEffect(IStatusReceiver* target, const FHitResult& hit)
{
	target->spawnStatusVFX(onApplyEffect, hit);

	return true;
}

void UBaseStatus::postRemove()
{
	target->setUnderStatusIntVariable(this->getStatusCountKey(), 0);
}

bool UBaseStatus::Tick(float DeltaSeconds)
{
	currentDuration += DeltaSeconds;

	if (currentDuration >= duration)
	{
		return false;
	}

	return true;
}

void UBaseStatus::refreshDuration()
{
	currentDuration = 0.0f;
}

void UBaseStatus::setDuration(float duration)
{
	this->duration = duration;
}

UNiagaraSystem* UBaseStatus::getOnApplyStatus() const
{
	return onApplyStatus;
}

UNiagaraSystem* UBaseStatus::getOnApplyEffect() const
{
	return onApplyEffect;
}

float UBaseStatus::getCurrentDuration() const
{
	return currentDuration;
}

float UBaseStatus::getRemainingDuration() const
{
	return duration - currentDuration;
}
