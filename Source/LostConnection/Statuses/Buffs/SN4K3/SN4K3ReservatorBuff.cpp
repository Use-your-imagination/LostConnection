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

	DOREPLIFETIME(USN4K3ReservatorBuff, naniteIncreasedDamage);
}

void USN4K3ReservatorBuff::setNaniteIncreasedDamage(float naniteIncreasedDamage)
{
	this->naniteIncreasedDamage = naniteIncreasedDamage;
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
	
	TArray<TWeakObjectPtr<UBaseWeapon>> weapons = character->getWeapons();
	ICaster* caster = Cast<ICaster>(character);

	for (auto& weapon : weapons)
	{
		if (weapon.IsValid() && (weapon->getDamageType() == ETypeOfDamage::nanite))
		{
			FSimpleDelegate reset;

			reset.BindLambda([this, weapon]() { weapon->removeIncreasedDamageCoefficient(naniteIncreasedDamage); });

			additionalNaniteDamage.Add(weapon, MoveTemp(reset));

			weapon->appendIncreasedDamageCoefficient(naniteIncreasedDamage);
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

				if (inflictor && (inflictor->getDamageType() == ETypeOfDamage::nanite))
				{
					FSimpleDelegate reset;

					reset.BindLambda([this, inflictor]() { inflictor->removeIncreasedDamageCoefficient(naniteIncreasedDamage); });

					additionalNaniteDamage.Add(ability, MoveTemp(reset));

					inflictor->removeIncreasedDamageCoefficient(naniteIncreasedDamage);
				}
			}
		}
	}

	return true;
}

void USN4K3ReservatorBuff::postRemove()
{
	ABaseCharacter* character = Cast<ABaseCharacter>(target);

	for (const auto& data : additionalNaniteDamage)
	{
		if (data.Key.IsValid())
		{
			data.Value.Execute();
		}
	}
}
