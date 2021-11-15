#include "BaseStatus.h"

#include "NiagaraFunctionLibrary.h"

#include "Interfaces/Gameplay/Descriptions/StatusReceiver.h"
#include "Characters/BaseCharacter.h"
#include "Utility/Utility.h"
#include "Engine/LostConnectionGameState.h"

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

void UBaseStatus::applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<IStatusReceiver>& target, const FHitResult& hit)
{
	this->inflictor = static_cast<IStatusInflictor*>(inflictor.GetInterface());

	this->target = static_cast<IStatusReceiver*>(target.GetInterface());

	target->addStatus(this);

	target->spawnApplyStatus(this, hit);

	target->spawnUnderStatus(this);
}

void UBaseStatus::applyEffect(IStatusReceiver* target, const FHitResult& hit)
{
	target->spawnApplyEffect(this, hit);
}

void UBaseStatus::removeStatus(IStatusReceiver* target)
{
	const_cast<TArray<UBaseStatus*>&>(target->getStatuses()).Remove(this);
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

UNiagaraSystem* UBaseStatus::getOnApplyStatus()
{
	return onApplyStatus;
}

UNiagaraSystem* UBaseStatus::getOnApplyEffect()
{
	return onApplyEffect;
}

UNiagaraSystem* UBaseStatus::getUnderStatus()
{
	return underStatus;
}

TWeakObjectPtr<UNiagaraComponent>& UBaseStatus::getUnderStatusComponent()
{
	return underStatusComponent;
}
