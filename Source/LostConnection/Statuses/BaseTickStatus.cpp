#include "BaseTickStatus.h"

#include "NiagaraFunctionLibrary.h"

#include "Interfaces/Gameplay/Descriptions/StatusReceiver.h"
#include "Characters/BaseCharacter.h"

FString UBaseTickStatus::getStatusName() const
{
	PURE_VIRTUAL(UBaseTickStatus::getStatusName, return "";);
}

void UBaseTickStatus::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UBaseTickStatus, tickPeriod);

	DOREPLIFETIME(UBaseTickStatus, currentTickPeriod);
}

UBaseTickStatus::UBaseTickStatus() :
	currentTickPeriod(tickPeriod)
{

}

void UBaseTickStatus::applyEffect(IStatusReceiver* target, const FHitResult& hit)
{
	UNiagaraFunctionLibrary::SpawnSystemAttached(onApplyEffect, target->getMeshComponent(), NAME_None, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, true, true, ENCPoolMethod::AutoRelease);
}

bool UBaseTickStatus::Tick(float DeltaTime)
{
	bool result = Super::Tick(DeltaTime);

	if (!result)
	{
		return result;
	}

	currentTickPeriod += DeltaTime;

	if (currentTickPeriod >= tickPeriod)
	{
		currentTickPeriod -= tickPeriod;

		this->applyEffect(target, FHitResult());
	}

	return true;
}
