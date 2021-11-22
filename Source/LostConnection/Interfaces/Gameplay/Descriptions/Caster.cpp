// Copyright (c) 2021 Use-your-imagination

#include "Caster.h"

#include "Characters/BaseDrone.h"
#include "Characters/BaseBotCaster.h"

static TArray<UAnimMontage*> filler;

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
			drone->GetMesh()->GetAnimInstance()->Montage_StopGroupByName(currentAbility->getCancelBlendOutTime(), TEXT("Skills"));
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
			bot->GetMesh()->GetAnimInstance()->Montage_StopGroupByName(currentAbility->getCancelBlendOutTime(), TEXT("Skills"));
		}

		bot->setCurrentAbility(nullptr);
	}
}
