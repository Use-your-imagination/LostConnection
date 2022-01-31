// Copyright (c) 2021 Use-your-imagination

#include "Caster.h"

#include "Characters/BaseDrone.h"
#include "Characters/BaseBotCaster.h"

void ICaster::castAbility(UBaseAbility* ability, const TFunction<void()>& callback)
{
	AActor* actor = Cast<AActor>(this->_getUObject());

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
	static TArray<UAnimMontage*> filler;

	PURE_VIRTUAL(ICaster::getAbilitiesAnimations, return filler;);
}

void ICaster::cancelCurrentAbilityAnimation()
{
	ABaseDrone* drone = Cast<ABaseDrone>(this);

	if (drone)
	{
		UBaseAbility* currentAbility = drone->getCurrentAbility();

		if (currentAbility && currentAbility->getIsCancelable())
		{
			drone->GetMesh()->GetAnimInstance()->Montage_StopGroupByName(currentAbility->getCancelBlendOutTime(), "Skills");
		}

		drone->setCurrentAbility(nullptr);

		return;
	}

	ABaseBotCaster* bot = Cast<ABaseBotCaster>(this);

	if (bot)
	{
		UBaseAbility* currentAbility = bot->getCurrentAbility();

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

	UBaseAbility* passive = this->getPassiveAbility();
	UBaseAbility* first = this->getFirstAbility();
	UBaseAbility* second = this->getSecondAbility();
	UBaseAbility* third = this->getThirdAbility();
	UBaseAbility* ultimate =this->getUltimateAbility();

	if (passive)
	{
		result.Add(passive);
	}

	if (first)
	{
		result.Add(first);
	}

	if (second)
	{
		result.Add(second);
	}

	if (third)
	{
		result.Add(third);
	}

	if (ultimate)
	{
		result.Add(ultimate);
	}

	return result;
}
