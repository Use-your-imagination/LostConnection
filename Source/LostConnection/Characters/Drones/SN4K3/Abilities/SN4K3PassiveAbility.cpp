// Copyright (c) 2021 Use Your Imagination

#include "SN4K3PassiveAbility.h"

#include "Misc/App.h"	
#include "Kismet/GameplayStatics.h"

#include "Characters/Drones/SN4K3/SN4K3.h"
#include "Interfaces/Gameplay/Descriptions/Caster.h"
#include "Utility/InitializationUtility.h"
#include "SN4K3UltimateAbility.h"

void USN4K3PassiveAbility::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USN4K3PassiveAbility, naniteMeter);

	DOREPLIFETIME(USN4K3PassiveAbility, cooldown);
}

USN4K3PassiveAbility::USN4K3PassiveAbility() :
	lastTimeAbilityUsed(0.0f),
	type(directionTypes::increase)
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
	TObjectPtr<ASN4K3PassiveAbilityHead> head = Utility::getGameState(target)->spawn<ASN4K3PassiveAbilityHead>(headClass, target->GetActorTransform());

	Utility::getPlayerController(target)->Possess(head);

	head->FinishSpawning({}, true);

	ICaster::Execute_applyPassiveAbilityEvent(caster.GetObject(), target);
}

void USN4K3PassiveAbility::useAbility()
{
	this->applyAbility(Cast<ASN4K3>(caster));
}

void USN4K3PassiveAbility::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	static constexpr float coeff = 5.0f;

	ASN4K3* drone = Cast<ASN4K3>(caster);
	USN4K3UltimateAbility* ultimateAbility = Cast<USN4K3UltimateAbility>(drone->getUltimateAbility());

	if (ultimateAbility->getIsUltimateAbilityUsed())
	{
		return;
	}

	if (lastTimeAbilityUsed < coeff)
	{
		type = directionTypes::increase;
	}
	else
	{
		type = directionTypes::decrease;
	}

	lastTimeAbilityUsed += DeltaSeconds;

	switch (type)
	{
	case directionTypes::increase:
		naniteMeter = FMath::Clamp(FMath::LogX(10, lastTimeAbilityUsed / coeff) / 2.0f + 1.0f, 0.5f, 1.0f) * 100;

		break;

	case directionTypes::decrease:
		naniteMeter = FMath::Clamp((FMath::Pow((lastTimeAbilityUsed - coeff) / 2.0f, 4) * -1 + 1.25f), 0.0f, 1.0f) * 100;

		break;

	default:
		break;
	}
}

float USN4K3PassiveAbility::getCooldown() const
{
	return cooldown->getCooldown();
}

float& USN4K3PassiveAbility::getCurrentCooldownReference()
{
	return cooldown->getCurrentCooldownReference();
}

float USN4K3PassiveAbility::getCurrentCooldown() const
{
	return cooldown->getCurrentCooldown();
}

bool USN4K3PassiveAbility::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool wroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	wroteSomething |= Channel->ReplicateSubobject(cooldown, *Bunch, *RepFlags);

	return wroteSomething;
}
