#include "BasePassiveAbility.h"

#include "Characters/BaseCharacter.h"

void UBasePassiveAbility::applyAbility(ABaseCharacter* target)
{
	PURE_VIRTUAL(UBasePassiveAbility::applyAbility);
}

void UBasePassiveAbility::useAbility()
{
	PURE_VIRTUAL(UBasePassiveAbility::useAbility);
}
