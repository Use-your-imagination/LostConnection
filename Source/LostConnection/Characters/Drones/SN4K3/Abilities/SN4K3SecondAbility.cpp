// Copyright (c) 2021 Use-your-imagination

#include "SN4K3SecondAbility.h"

#include "Characters/Drones/SN4K3/SN4K3.h"
#include "Interfaces/Gameplay/Descriptions/Caster.h"
#include "Utility/InitializationUtility.h"
#include "SN4K3PassiveAbility.h"
#include "Statuses/Ailments/SwarmStatus.h"
#include "Interfaces/Gameplay/Descriptions/ObserverHolders/GameplayEvents/DeathEventsHolder.h"

void USN4K3SecondAbility::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USN4K3SecondAbility, distance);

	DOREPLIFETIME(USN4K3SecondAbility, thresholdedHealthHeal);
}

USN4K3SecondAbility::USN4K3SecondAbility() :
	distance(5000.0f)
{
	InitializationUtility::initAbilityId(__FILE__, id);
}

float USN4K3SecondAbility::getDistance() const
{
	return distance;
}

void USN4K3SecondAbility::applyAbility(ABaseCharacter* target)
{
	IDeathEventsHolder* holder = this->getDeathEventsHolder();

	this->target = target;

	if (holder)
	{
		holder->detachDeathEvent(this);
	}

	Cast<IDeathEventsHolder>(target)->attachDeathEvent(this);

	ICaster::Execute_applySecondAbilityEvent(Cast<UObject>(caster), target);
}

void USN4K3SecondAbility::useAbility()
{
	ASN4K3* drone = Cast<ASN4K3>(caster);
	FHitResult hit;
	UWorld* world = drone->GetWorld();
	ABaseCharacter* target = nullptr;
	FCollisionQueryParams ignoreParameters;

	ignoreParameters.AddIgnoredActor(drone);

	world->LineTraceSingleByChannel(hit, drone->getStartActionLineTrace(), drone->getEndActionLineTrace() + (distance * drone->GetFollowCamera()->GetForwardVector()), ECollisionChannel::ECC_Camera, ignoreParameters);

	target = Cast<ABaseCharacter>(hit.Actor);

	if (!target || target->getIsAlly())
	{
		return;
	}

	this->applyAbility(target);

	Cast<USN4K3PassiveAbility>(drone->getPassiveAbility())->resetLastTimeAbilityUsed();
}

void USN4K3SecondAbility::deathEventAction()
{
	TWeakObjectPtr<USwarmStatus> swarm = target->getSwarm();

	if (swarm.IsValid())
	{
		Cast<ASN4K3>(caster)->restoreHealth(swarm->getThreshold() * (thresholdedHealthHeal / 100.0f));
	}
}

IDeathEventsHolder* USN4K3SecondAbility::getDeathEventsHolder() const
{
	return Cast<IDeathEventsHolder>(target);
}
