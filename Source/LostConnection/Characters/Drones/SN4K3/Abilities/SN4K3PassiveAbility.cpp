#include "SN4K3PassiveAbility.h"

#include "Characters/BaseCharacter.h"

void ASN4K3PassiveAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
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

		lastTimeAbilityUsed += DeltaTime;

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
}

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
}

void ASN4K3PassiveAbility::useAbility()
{

}

void ASN4K3PassiveAbility::resetLastTimeAbilityUsed()
{
	lastTimeAbilityUsed = 0.0f;
}
