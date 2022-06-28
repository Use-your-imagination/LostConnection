// Copyright (c) 2021 Use Your Imagination

#include "Caster.h"

#include "Characters/BaseDrone.h"
#include "Characters/AI/BaseCasterBot.h"

void ICaster::castAbility(UBaseAbility* ability, const TFunction<void()>& callback)
{
	TObjectPtr<AActor> actor = Cast<AActor>(this->_getUObject());

	Utility::executeOnlyOnServerFromMulticast(actor, [this, ability, callback]()
		{
			this->getCurrentEnergy() -= ability->getCost();

			ability->useAbility();

			callback();
		});
}

void ICaster::setEnergy_Implementation(float newEnergy)
{

}

void ICaster::setCurrentEnergy_Implementation(float newCurrentEnergy)
{

}

void ICaster::setEnergyRestorationPerSecond_Implementation(float newEnergyRestorationPerSecond)
{

}

void ICaster::setCooldownReduction_Implementation(float newCooldownReduction)
{

}

void ICaster::setCurrentAbility(UBaseAbility* ability)
{

}

const TArray<UAnimMontage*>& ICaster::getAbilitiesAnimations() const
{
	static TArray<TObjectPtr<UAnimMontage>> filler;

	PURE_VIRTUAL(ICaster::getAbilitiesAnimations, return filler;);
}

void ICaster::cancelCurrentAbilityAnimation()
{
	TObjectPtr<ABaseDrone> drone = Cast<ABaseDrone>(this);

	if (drone)
	{
		TObjectPtr<UBaseAbility> currentAbility = drone->getCurrentAbility();

		if (currentAbility && currentAbility->getIsCancelable())
		{
			drone->GetMesh()->GetAnimInstance()->Montage_StopGroupByName(currentAbility->getCancelBlendOutTime(), "Skills");
		}

		drone->setCurrentAbility(nullptr);

		return;
	}

	TObjectPtr<ABaseCasterBot> bot = Cast<ABaseCasterBot>(this);

	if (bot)
	{
		TObjectPtr<UBaseAbility> currentAbility = bot->getCurrentAbility();

		if (currentAbility && currentAbility->getIsCancelable())
		{
			bot->GetMesh()->GetAnimInstance()->Montage_StopGroupByName(currentAbility->getCancelBlendOutTime(), "Skills");
		}

		bot->setCurrentAbility(nullptr);
	}
}

TArray<TWeakObjectPtr<UBaseAbility>> ICaster::getAbilities() const
{
	TArray<TWeakObjectPtr<UBaseAbility>> result;

	if (TObjectPtr<UBaseAbility> passive = this->getPassiveAbility())
	{
		result.Add(passive);
	}

	if (TObjectPtr<UBaseAbility> first = this->getFirstAbility())
	{
		result.Add(first);
	}

	if (TObjectPtr<UBaseAbility> second = this->getSecondAbility())
	{
		result.Add(second);
	}

	if (TObjectPtr<UBaseAbility> third = this->getThirdAbility())
	{
		result.Add(third);
	}

	if (TObjectPtr<UBaseAbility> ultimate = this->getUltimateAbility())
	{
		result.Add(ultimate);
	}

	return result;
}
