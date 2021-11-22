// Copyright (c) 2021 Use-your-imagination

#include "BaseStatus.h"

#include "NiagaraFunctionLibrary.h"

#include "Interfaces/Gameplay/Descriptions/Derived/StatusReceiver.h"
#include "Characters/BaseCharacter.h"
#include "Utility/Utility.h"
#include "Engine/LostConnectionGameState.h"

FString UBaseStatus::getStatusCountKey() const
{
	return this->getStatusName() + "Count";
}

bool UBaseStatus::IsSupportedForNetworking() const
{
	return true;
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

void UBaseStatus::applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<IStatusReceiver>& target, const FHitResult& hit)
{
	this->target = static_cast<IStatusReceiver*>(target.GetInterface());

	inflictorDamage = inflictor->getInflictorDamage();
	inflictorDamageType = inflictor->getDamageType();

	target->addStatus(this);

	target->spawnApplyStatus(onApplyStatus, hit);

	target->setUnderStatusIntVariable(this->getStatusCountKey(), 1);
}

bool UBaseStatus::applyEffect(IStatusReceiver* target, const FHitResult& hit)
{
	target->spawnApplyEffect(onApplyEffect, hit);

	return true;
}

void UBaseStatus::postRemove()
{
	target->setUnderStatusIntVariable(this->getStatusCountKey(), 0);
}

bool UBaseStatus::Tick(float DeltaTime)
{
	currentDuration += DeltaTime;

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

UNiagaraSystem* UBaseStatus::getOnApplyStatus()
{
	return onApplyStatus;
}

UNiagaraSystem* UBaseStatus::getOnApplyEffect()
{
	return onApplyEffect;
}
