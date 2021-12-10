// Copyright (c) 2021 Use-your-imagination

#include "SN4K3ReservatorBuff.h"

#include "Characters/BaseCharacter.h"
#include "Interfaces/Gameplay/Statuses/Base/StatusReceiver.h"
#include "Interfaces/Gameplay/Descriptions/Caster.h"
#include "Utility/Utility.h"

#pragma warning(disable: 4458)

FString USN4K3ReservatorBuff::getStatusName() const
{
	return "SN4K3ReservatorBuff";
}

void USN4K3ReservatorBuff::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USN4K3ReservatorBuff, healthReservePercent);

	DOREPLIFETIME(USN4K3ReservatorBuff, naniteAdditionalDamagePercent);

	DOREPLIFETIME(USN4K3ReservatorBuff, reservedHealth);
}

USN4K3ReservatorBuff::USN4K3ReservatorBuff()
{
	duration = 8.0f;
}

void USN4K3ReservatorBuff::setHealthReservePercent(float healthReservePercent)
{
	this->healthReservePercent = healthReservePercent;
}

void USN4K3ReservatorBuff::setNaniteAdditionalDamagePercent(float naniteAdditionalDamagePercent)
{
	this->naniteAdditionalDamagePercent = naniteAdditionalDamagePercent;
}

void USN4K3ReservatorBuff::applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<IStatusReceiver>& target, const FHitResult& hit)
{
	if (Utility::isTargetAlreadyUnderStatus<USN4K3ReservatorBuff>(target))
	{
		this->refreshDuration();
	}
	else
	{
		IAilmentReceiver* receiver = StaticCast<IAilmentReceiver*>(target.GetInterface());

		this->target = receiver;
		
		target->addStatus(this);

		this->applyEffect(receiver, hit);
	}
}

bool USN4K3ReservatorBuff::applyEffect(IStatusReceiver* target, const FHitResult& hit)
{
	ABaseCharacter* character = Cast<ABaseCharacter>(target);
	float newHealth = character->getHealth() * (healthReservePercent / 100.0f);

	reservedHealth = character->getHealth() - newHealth;

	character->setHealth(newHealth);

	if (character->getCurrentHealth() > newHealth)
	{
		character->setCurrentHealth(newHealth);
	}

	TArray<TWeakObjectPtr<UBaseWeapon>> weapons = character->getWeapons();
	ICaster* caster = Cast<ICaster>(character);

	for (auto& weapon : weapons)
	{
		if (weapon.IsValid() && (weapon->getDamageType() == typeOfDamage::nanite))
		{
			float additionalDamage = weapon->getDamage() * (naniteAdditionalDamagePercent / 100.0f);
			FSimpleDelegate reset;

			reset.BindLambda([weapon, additionalDamage]() { weapon->decreaseAdditionalDamage(additionalDamage); });

			additionalNaniteDamage.Add(weapon, MoveTemp(reset));

			weapon->setAdditionalDamage(weapon->getAdditionalDamage() + additionalDamage);
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
					float additionalDamage = inflictor->getBaseDamage() * (naniteAdditionalDamagePercent / 100.0f);
					FSimpleDelegate reset;

					reset.BindLambda([inflictor, additionalDamage]() { inflictor->decreaseAdditionalDamage(additionalDamage); });

					additionalNaniteDamage.Add(ability, MoveTemp(reset));

					inflictor->setAdditionalDamage(inflictor->getAdditionalDamage() + additionalDamage);
				}
			}
		}
	}

	return true;
}

void USN4K3ReservatorBuff::postRemove()
{
	ABaseCharacter* character = Cast<ABaseCharacter>(target);

	character->setHealth(character->getHealth() + reservedHealth);

	for (const auto& data : additionalNaniteDamage)
	{
		if (data.Key.IsValid())
		{
			data.Value.Execute();
		}
	}
}
