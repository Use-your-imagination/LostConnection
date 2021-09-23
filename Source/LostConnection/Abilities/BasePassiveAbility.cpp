#include "BasePassiveAbility.h"

#include "Characters/BaseCharacter.h"

void ABasePassiveAbility::applyAbility(ABaseCharacter* target)
{
	PURE_VIRTUAL(ABasePassiveAbility::applyAbility);
}

void ABasePassiveAbility::useAbility()
{
	PURE_VIRTUAL(ABasePassiveAbility::useAbility);
}
