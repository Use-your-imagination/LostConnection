// Copyright (c) 2021 Use-your-imagination

#include "SN4K3Reservator.h"

#include "Characters/BaseDrone.h"
#include "Interfaces/Gameplay/Descriptions/Derived/AilmentInflictor.h"
#include "Statuses/Buffs/SN4K3/SN4K3ReservatorBuff.h"

bool USN4K3Reservator::IsSupportedForNetworking() const
{
	return true;
}

void USN4K3Reservator::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USN4K3Reservator, healthReservePercent);

	DOREPLIFETIME(USN4K3Reservator, naniteAdditionalDamagePercent);
}

void USN4K3Reservator::useSocketItem(ABaseCharacter* target)
{
	USN4K3ReservatorBuff* reservator = NewObject<USN4K3ReservatorBuff>(target);
	
	reservator->setHealthReservePercent(healthReservePercent);

	reservator->setNaniteAdditionalDamagePercent(naniteAdditionalDamagePercent);
	
	reservator->applyStatus(nullptr, target, FHitResult());
}

void USN4K3Reservator::reserve(ABaseCharacter* target)
{
	
}

void USN4K3Reservator::restoreReserved(ABaseCharacter* target)
{
	
}
