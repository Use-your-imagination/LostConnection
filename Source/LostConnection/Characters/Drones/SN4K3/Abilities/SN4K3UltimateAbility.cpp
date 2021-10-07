#include "SN4K3UltimateAbility.h"

#include "Characters/Drones/SN4K3/SN4K3.h"
#include "Interfaces/Gameplay/Descriptions/Caster.h"

ASN4K3UltimateAbility::ASN4K3UltimateAbility()
{

}

void ASN4K3UltimateAbility::applyAbility(ABaseCharacter* target)
{
	ICaster::Execute_applyUltimateAbilityEvent(Cast<UObject>(owner), target);
}

void ASN4K3UltimateAbility::useAbility()
{

}
