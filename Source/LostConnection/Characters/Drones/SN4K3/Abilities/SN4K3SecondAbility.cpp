// Copyright (c) 2021 Use-your-imagination

#include "SN4K3SecondAbility.h"

#include "Kismet/KismetMathLibrary.h"

#include "Characters/Drones/SN4K3/SN4K3.h"
#include "Interfaces/Gameplay/Descriptions/Caster.h"
#include "Utility/InitializationUtility.h"
#include "SN4K3PassiveAbility.h"
#include "Statuses/Ailments/SwarmStatus.h"
#include "Interfaces/Gameplay/Descriptions/ObserverHolders/GameplayEvents/DeathEventsHolder.h"

#pragma warning(disable: 4701)

void USN4K3SecondAbility::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USN4K3SecondAbility, distance);

	DOREPLIFETIME(USN4K3SecondAbility, thresholdedHealthHeal);

	DOREPLIFETIME(USN4K3SecondAbility, maxHealDistance);

	DOREPLIFETIME(USN4K3SecondAbility, linearDecreaseHealDistance);
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
		ASN4K3* drone = Cast<ASN4K3>(caster);
		float distance = (target->GetActorLocation() - drone->GetActorLocation()).Size();
		float distanceCofficient;
		float health = (swarm->getThreshold() * (thresholdedHealthHeal / 100.0f) * Cast<USN4K3PassiveAbility>(drone->getPassiveAbility())->getNaniteMeter());

		if (UKismetMathLibrary::InRange_FloatFloat(distance, maxHealDistance.X, maxHealDistance.Y))
		{
			distance = 1.0f;
		}
		else if (UKismetMathLibrary::InRange_FloatFloat(distance, linearDecreaseHealDistance.X, linearDecreaseHealDistance.Y))
		{
			distanceCofficient = UKismetMathLibrary::NormalizeToRange(distance, linearDecreaseHealDistance.X, linearDecreaseHealDistance.Y);
		}
		else
		{
			distanceCofficient = 0.0f;
		}

		drone->restoreHealth(health * distanceCofficient);
	}
}

IDeathEventsHolder* USN4K3SecondAbility::getDeathEventsHolder() const
{
	return Cast<IDeathEventsHolder>(target);
}
