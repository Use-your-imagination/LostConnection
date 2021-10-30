#include "Caster.h"

#include "Characters/BaseCharacter.h"

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
	Cast<ABaseCharacter>(this)->GetMesh()->GetAnimInstance()->Montage_Play(nullptr);
}
