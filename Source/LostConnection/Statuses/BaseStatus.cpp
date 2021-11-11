#include "BaseStatus.h"

#include "NiagaraFunctionLibrary.h"

#include "Interfaces/Gameplay/Descriptions/StatusReceiver.h"
#include "Characters/BaseCharacter.h"
#include "Utility/Utility.h"

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

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(Utility::getWorld(), onApplyStatus, hit.Location, FRotator::ZeroRotator, FVector::OneVector, true, true, ENCPoolMethod::AutoRelease);

	UNiagaraFunctionLibrary::SpawnSystemAttached(underStatus, target->getMeshComponent(), NAME_None, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, true, true, ENCPoolMethod::AutoRelease);
}

void UBaseStatus::applyEffect(IStatusReceiver* target, const FHitResult& hit)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(Utility::getWorld(), onApplyEffect, hit.Location, FRotator::ZeroRotator, FVector::OneVector, true, true, ENCPoolMethod::AutoRelease);
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
