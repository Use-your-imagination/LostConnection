#include "BaseStatus.h"

#include "NiagaraFunctionLibrary.h"

#include "Interfaces/Gameplay/Descriptions/StatusReceiver.h"
#include "Characters/BaseCharacter.h"

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

void UBaseStatus::applyStatus_Implementation(const TScriptInterface<IStatusReceiver>& target, const FHitResult& hit)
{
	this->target = static_cast<IStatusReceiver*>(target.GetInterface());

	target->addStatus(this);

	ABaseCharacter* character = Cast<ABaseCharacter>(target.GetObject());

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(character->GetWorld(), onApplyStatus, hit.Location, FRotator::ZeroRotator, FVector::OneVector, true, true, ENCPoolMethod::AutoRelease);

	UNiagaraFunctionLibrary::SpawnSystemAttached(underStatus, character->GetMesh(), NAME_None, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, true, true, ENCPoolMethod::AutoRelease);
}

void UBaseStatus::applyEffect(IStatusReceiver* target, const FHitResult& hit)
{
	ABaseCharacter* character = Cast<ABaseCharacter>(target);

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(character->GetWorld(), onApplyEffect, hit.Location, FRotator::ZeroRotator, FVector::OneVector, true, true, ENCPoolMethod::AutoRelease);
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
