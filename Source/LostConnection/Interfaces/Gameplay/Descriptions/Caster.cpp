#include "Caster.h"

#include "Characters/BaseDrone.h"
#include "Characters/BaseBotCaster.h"

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
	}

	ABaseBotCaster* bot = Cast<ABaseBotCaster>(this);

	if (bot)
	{
		UBaseAbility* currentAbility = bot->getCurrentAbility();

		if (currentAbility && currentAbility->getIsCancelable())
		{
			bot->GetMesh()->GetAnimInstance()->Montage_StopGroupByName(currentAbility->getCancelBlendOutTime(), TEXT("Skills"));
		}
	}
}
