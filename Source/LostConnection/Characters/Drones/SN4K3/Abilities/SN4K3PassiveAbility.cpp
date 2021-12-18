// Copyright (c) 2021 Use-your-imagination

#include "SN4K3PassiveAbility.h"

#include "Misc/App.h"	

#include "Characters/Drones/SN4K3/SN4K3.h"
#include "Interfaces/Gameplay/Descriptions/Caster.h"
#include "Utility/InitializationUtility.h"
#include "SN4K3UltimateAbility.h"

void USN4K3PassiveAbility::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USN4K3PassiveAbility, naniteMeter);
}

USN4K3PassiveAbility::USN4K3PassiveAbility() :
	lastTimeAbilityUsed(0.0f),
	type(directionTypes::up)
{
	InitializationUtility::initAbilityId(__FILE__, id);
}

void USN4K3PassiveAbility::resetLastTimeAbilityUsed()
{
	if (Cast<USN4K3UltimateAbility>(Cast<ICaster>(caster)->getUltimateAbility())->getIsUltimateAbilityUsed())
	{
		return;
	}

	lastTimeAbilityUsed = 0.0f;
}

int32 USN4K3PassiveAbility::getNaniteMeter() const
{
	return naniteMeter;
}

void USN4K3PassiveAbility::applyAbility(ABaseCharacter* target)
{
	ASN4K3PassiveAbilityHead* head = target->GetWorld()->GetGameState<ALostConnectionGameState>()->spawn<ASN4K3PassiveAbilityHead>(headClass, target->GetActorTransform());

	head->FinishSpawning({}, true);

	target->GetController()->Possess(head);

	ICaster::Execute_applyPassiveAbilityEvent(Cast<UObject>(caster), target);
}

void USN4K3PassiveAbility::useAbility()
{
	this->applyAbility(Cast<ASN4K3>(caster));
}

void USN4K3PassiveAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	static constexpr float coeff = 5.0f;

	ASN4K3* drone = Cast<ASN4K3>(caster);
	USN4K3UltimateAbility* ultimateAbility = Cast<USN4K3UltimateAbility>(drone->getUltimateAbility());

	if (ultimateAbility->getIsUltimateAbilityUsed())
	{
		return;
	}

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
