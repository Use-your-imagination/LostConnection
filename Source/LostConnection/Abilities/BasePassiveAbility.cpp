#include "BasePassiveAbility.h"

#include "Characters/BaseDrone.h"

void ABasePassiveAbility::applyAbility(ABaseDrone* target)
{
	PURE_VIRTUAL(ABasePassiveAbility::applyAbility);
}

void ABasePassiveAbility::useAbility()
{
	PURE_VIRTUAL(ABasePassiveAbility::useAbility);
}
