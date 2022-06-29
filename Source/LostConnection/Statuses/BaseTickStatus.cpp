// Copyright (c) 2021 Use Your Imagination

#include "BaseTickStatus.h"

#include "NiagaraFunctionLibrary.h"

#include "Interfaces/Gameplay/Statuses/Base/StatusReceiver.h"
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

bool UBaseTickStatus::Tick(float DeltaSeconds)
{
	bool result = Super::Tick(DeltaSeconds);

	if (!result)
	{
		return result;
	}

	currentTickPeriod += DeltaSeconds;

	if (currentTickPeriod >= tickPeriod)
	{
		FHitResult hit;

		hit.Location = target->getMeshComponent()->GetComponentLocation();

		currentTickPeriod -= tickPeriod;

		return this->applyEffect(target, hit);
	}

	return true;
}
