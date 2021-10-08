#include "SN4K3PassiveAbility.h"

#include "Misc/App.h"	

#include "Characters/Drones/SN4K3/SN4K3.h"
#include "Interfaces/Gameplay/Descriptions/Caster.h"

void ASN4K3PassiveAbility::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASN4K3PassiveAbility, naniteMeter);
}

ASN4K3PassiveAbility::ASN4K3PassiveAbility() :
	lastTimeAbilityUsed(0.0f),
	type(directionTypes::up)
{
	NetUpdateFrequency = 60;
}

void ASN4K3PassiveAbility::applyAbility(ABaseCharacter* target)
{
	// TODO: second part

	ICaster::Execute_applyPassiveAbilityEvent(Cast<UObject>(owner), target);
}

void ASN4K3PassiveAbility::useAbility()
{
	static constexpr float coeff = 5.0f;

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
		naniteMeter = FMath::Clamp((FMath::Pow((lastTimeAbilityUsed - coeff) / 2.0f, 4) * -1 + 1), 0.0f, 1.0f) * 100;

		break;

	default:
		break;
	}
}

void ASN4K3PassiveAbility::resetLastTimeAbilityUsed()
{
	lastTimeAbilityUsed = 0.0f;
}