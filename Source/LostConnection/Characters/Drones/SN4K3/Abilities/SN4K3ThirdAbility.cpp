#include "SN4K3ThirdAbility.h"

#include "Characters/Drones/SN4K3/SN4K3.h"
#include "Interfaces/Gameplay/Descriptions/Caster.h"

ASN4K3ThirdAbility::ASN4K3ThirdAbility()
{

}

void ASN4K3ThirdAbility::applyAbility(ABaseCharacter* target)
{
	ICaster::Execute_applyThirdAbilityEvent(Cast<UObject>(owner), target);
}

void ASN4K3ThirdAbility::useAbility()
{

}
