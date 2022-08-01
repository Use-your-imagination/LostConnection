// Copyright (c) 2021 Use Your Imagination

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

	DOREPLIFETIME(USN4K3ReservatorBuff, naniteIncreaseDamage);
}

void USN4K3ReservatorBuff::setNaniteIncreaseDamage(float naniteIncreaseDamage)
{
	this->naniteIncreaseDamage = naniteIncreaseDamage;
}

void USN4K3ReservatorBuff::applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<IStatusReceiver>& target, const FHitResult& hit)
{
	if (Utility::isTargetAlreadyUnderStatus<USN4K3ReservatorBuff>(target))
	{
		this->refreshDuration();
	}
	else
	{
		this->target = target;
		
		target->addStatus(this);

		this->applyEffect(target, hit);
	}
}

bool USN4K3ReservatorBuff::applyEffect(const TScriptInterface<IStatusReceiver>& target, const FHitResult& hit)
{
	TObjectPtr<ABaseCharacter> character = Cast<ABaseCharacter>(target);
	
	TArray<TWeakObjectPtr<UBaseWeapon>> weapons = character->getWeapons();
	TScriptInterface<ICaster> caster = character.Get();

	for (auto& weapon : weapons)
	{
		if (weapon.IsValid() && (weapon->getDamageType() == ETypeOfDamage::nanite))
		{
			FSimpleDelegate reset;

			reset.BindLambda([this, weapon]() { weapon->removeIncreaseDamageCoefficient(naniteIncreaseDamage); });

			additionalNaniteDamage.Add(weapon, MoveTemp(reset));

			weapon->appendIncreaseDamageCoefficient(naniteIncreaseDamage);
		}
	}

	if (caster)
	{
		TArray<TWeakObjectPtr<UBaseAbility>> abilities = caster->getAbilities();

		for (auto& ability : abilities)
		{
			if (ability.IsValid())
			{
				TScriptInterface<IAilmentInflictor> inflictor = ability.Get();

				if (inflictor && (inflictor->getDamageType() == ETypeOfDamage::nanite))
				{
					FSimpleDelegate reset;

					reset.BindLambda([this, inflictor]() { inflictor->getDamage().increaseDamageCoefficients.RemoveSingle(naniteIncreaseDamage); });

					additionalNaniteDamage.Add(ability, MoveTemp(reset));

					inflictor->getDamage().increaseDamageCoefficients.Add(naniteIncreaseDamage);
				}
			}
		}
	}

	return true;
}

void USN4K3ReservatorBuff::postRemove()
{
	TObjectPtr<ABaseCharacter> character = Cast<ABaseCharacter>(target);

	for (const auto& data : additionalNaniteDamage)
	{
		if (data.Key.IsValid())
		{
			data.Value.Execute();
		}
	}
}