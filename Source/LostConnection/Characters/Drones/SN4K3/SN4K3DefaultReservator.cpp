// Copyright (c) 2021 Use-your-imagination

#include "SN4K3DefaultReservator.h"

#include "Characters/BaseDrone.h"
#include "Interfaces/Gameplay/Descriptions/Derived/AilmentInflictor.h"

bool USN4K3DefaultReservator::IsSupportedForNetworking() const
{
	return true;
}

void USN4K3DefaultReservator::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USN4K3DefaultReservator, healthReservePercent);

	DOREPLIFETIME(USN4K3DefaultReservator, naniteAdditionalDamagePercent);
}

void USN4K3DefaultReservator::useSocketItem(ABaseCharacter* target)
{
	TArray<TWeakObjectPtr<UBaseWeapon>> weapons = target->getWeapons();
	ICaster* caster = Cast<ICaster>(target);

	for (auto& weapon : weapons)
	{
		if (weapon.IsValid() && (weapon->getDamageType() == typeOfDamage::nanite))
		{
			weapon->setDamage(weapon->getDamage() * (naniteAdditionalDamagePercent / 100.0f));
		}
	}

	if (caster)
	{
		TArray<TWeakObjectPtr<UBaseAbility>> abilities = caster->getAbilities();

		for (auto& ability : abilities)
		{
			if (ability.IsValid())
			{
				IAilmentInflictor* inflictor = Cast<IAilmentInflictor>(ability);

				if (inflictor && (inflictor->getDamageType() == typeOfDamage::nanite))
				{
					inflictor->setAdditionalInflictorDamage(inflictor->getAdditionalInflictorDamage() + inflictor->getInflictorDamage() * 2.0f);
				}
			}
		}
	}
}

void USN4K3DefaultReservator::reserve(ABaseCharacter* target)
{
	float newHealth = target->getHealth() * 0.5f;

	target->setHealth(newHealth);

	if (target->getCurrentHealth() > newHealth)
	{
		target->setCurrentHealth(newHealth);
	}
}

void USN4K3DefaultReservator::restoreReserved(ABaseCharacter* target)
{
	target->setHealth(target->getHealth() * 2.0f);
}
