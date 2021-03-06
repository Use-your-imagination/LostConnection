// Copyright (c) 2021 Use Your Imagination

#include "SN4K3Reservator.h"

#include "Characters/BaseDrone.h"
#include "Statuses/Buffs/SN4K3/SN4K3ReservatorBuff.h"

void USN4K3Reservator::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USN4K3Reservator, healthReservePercent);

	DOREPLIFETIME(USN4K3Reservator, naniteIcreasedDamage);

	DOREPLIFETIME(USN4K3Reservator, reservedHealth);
}

void USN4K3Reservator::setBuffDuration(float buffDuration)
{
	this->buffDuration = buffDuration;
}

void USN4K3Reservator::useSocketItem(ABaseCharacter* target)
{
	USN4K3ReservatorBuff* reservator = NewObject<USN4K3ReservatorBuff>(target);
	
	reservator->setNaniteIncreaseDamage(naniteIcreasedDamage);

	reservator->setDuration(buffDuration);
	
	reservator->applyStatus(nullptr, target, FHitResult());
}

void USN4K3Reservator::reserve(ABaseCharacter* target)
{
	reservedHealth = target->getHealth() * Utility::fromPercent(healthReservePercent);

	target->setReservedHealth(reservedHealth);
}

void USN4K3Reservator::restoreReserved(ABaseCharacter* target)
{
	target->setReservedHealth(target->getReservedHealth() - reservedHealth);
}
