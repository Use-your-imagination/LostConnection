// Copyright (c) 2021 Use Your Imagination

#include "SN4K3SecondAbility.h"

#include "Kismet/KismetMathLibrary.h"

#include "Characters/Drones/SN4K3/SN4K3.h"
#include "Interfaces/Gameplay/Descriptions/Caster.h"
#include "Utility/InitializationUtility.h"
#include "SN4K3PassiveAbility.h"
#include "Statuses/Ailments/SwarmAilment.h"
#include "Interfaces/Gameplay/Descriptions/ObserverHolders/DeathEventsHolder.h"
#include "Utility/Utility.h"

#pragma warning(disable: 4701)

void USN4K3SecondAbility::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USN4K3SecondAbility, distance);

	DOREPLIFETIME(USN4K3SecondAbility, thresholdedHealthHeal);

	DOREPLIFETIME(USN4K3SecondAbility, maxHealDistance);

	DOREPLIFETIME(USN4K3SecondAbility, linearDecreaseHealDistance);

	DOREPLIFETIME(USN4K3SecondAbility, naniteMeterCoefficient);
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

void USN4K3SecondAbility::applyAbility(ABaseCharacter* holder)
{
	naniteMeterCoefficient = StaticCast<float>(Cast<USN4K3PassiveAbility>(caster->getPassiveAbility())->getNaniteMeter()) / 50.0f;

	ICaster::Execute_applySecondAbilityEvent(Cast<UObject>(caster), holder);
}

void USN4K3SecondAbility::useAbility()
{
	this->applyAbility(Cast<ABaseCharacter>(holder.GetObject()));

	Cast<USN4K3PassiveAbility>(Cast<ASN4K3>(caster)->getPassiveAbility())->resetLastTimeAbilityUsed();
}

void USN4K3SecondAbility::deathEventAction()
{
	TObjectPtr<ABaseCharacter> target = Cast<ABaseCharacter>(holder.GetObject());
	TWeakObjectPtr<USwarmAilment> swarm = target->getSwarm();

	if (swarm.IsValid())
	{
		TObjectPtr<ASN4K3> drone = Cast<ASN4K3>(caster);

		if (drone.IsNull())
		{
			return;
		}

		float distance = (target->GetActorLocation() - drone->GetActorLocation()).Size();
		float distanceCofficient;
		float health = target->getHealth() * Utility::fromPercent(swarm->getThreshold()) * (naniteMeterCoefficient * Utility::fromPercent(thresholdedHealthHeal));

		if (UKismetMathLibrary::InRange_FloatFloat(distance, maxHealDistance.X, maxHealDistance.Y))
		{
			distanceCofficient = 1.0f;
		}
		else if (UKismetMathLibrary::InRange_FloatFloat(distance, linearDecreaseHealDistance.X, linearDecreaseHealDistance.Y))
		{
			distanceCofficient = 1.0f - UKismetMathLibrary::NormalizeToRange(distance, linearDecreaseHealDistance.X, linearDecreaseHealDistance.Y);
		}
		else
		{
			distanceCofficient = 0.0f;
		}

		drone->restoreHealth(health * distanceCofficient);
	}
}

TWeakInterfacePtr<IDeathEventsHolder>& USN4K3SecondAbility::getDeathEventsHolder()
{
	return holder;
}
