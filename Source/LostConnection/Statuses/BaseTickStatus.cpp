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

bool UBaseTickStatus::applyEffect(IStatusReceiver* target, const FHitResult& hit)
{
	target->spawnApplyEffect(onApplyEffect, hit);

	return true;
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
		FHitResult hit;

		hit.Location = target->getMeshComponent()->GetComponentLocation();

		currentTickPeriod -= tickPeriod;

		return this->applyEffect(target, hit);
	}

	return true;
}
