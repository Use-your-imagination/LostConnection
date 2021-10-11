#include "SN4K3PassiveAbility.h"

#include "Misc/App.h"	

#include "Characters/Drones/SN4K3/SN4K3.h"
#include "Interfaces/Gameplay/Descriptions/Caster.h"

USN4K3PassiveAbility::USN4K3PassiveAbility() :
	lastTimeAbilityUsed(0.0f),
	type(directionTypes::up)
{
	
}

void USN4K3PassiveAbility::applyAbility(ABaseCharacter* target)
{
	// TODO: second part

	ICaster::Execute_applyPassiveAbilityEvent(Cast<UObject>(caster), target);
}

void USN4K3PassiveAbility::useAbility()
{
	static constexpr float coeff = 5.0f;

	ASN4K3* drone = Cast<ASN4K3>(caster);

	if (drone->getIsUltimateAbilityUsed())
	{
		return;
	}

	int32& naniteMeter = drone->getNaniteMeter();

	if (lastTimeAbilityUsed < coeff)
	{
		type = directionTypes::up;
	}
	else
	{
		type = directionTypes::down;
	}

	lastTimeAbilityUsed += FApp::GetDeltaTime();

	switch (type)
	{
	case directionTypes::up:
		naniteMeter = FMath::Clamp(FMath::LogX(10, lastTimeAbilityUsed / coeff) / 2.0f + 1.0f, 0.5f, 1.0f) * 100;

		break;

	case directionTypes::down:
		naniteMeter = FMath::Clamp((FMath::Pow((lastTimeAbilityUsed - coeff) / 2.0f, 4) * -1 + 1.25f), 0.0f, 1.0f) * 100;

		break;

	default:
		break;
	}
}

void USN4K3PassiveAbility::resetLastTimeAbilityUsed()
{
	if (Cast<ASN4K3>(caster)->getIsUltimateAbilityUsed())
	{
		return;
	}

	lastTimeAbilityUsed = 0.0f;
}
