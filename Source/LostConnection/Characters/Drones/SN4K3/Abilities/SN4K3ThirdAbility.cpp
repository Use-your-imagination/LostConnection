#include "SN4K3ThirdAbility.h"

#include "Characters/Drones/SN4K3/SN4K3.h"
#include "Interfaces/Gameplay/Descriptions/Caster.h"
#include "Utility/InitializationUtility.h"
#include "WorldPlaceables/SN4K3/SN4K3ThirdAbilityFlag.h"
#include "Engine/LostConnectionGameState.h"
#include "SN4K3PassiveAbility.h"

#pragma warning(disable: 4458)

void USN4K3ThirdAbility::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USN4K3ThirdAbility, lifetime);

	DOREPLIFETIME(USN4K3ThirdAbility, radius);

	DOREPLIFETIME(USN4K3ThirdAbility, period);
}

USN4K3ThirdAbility::USN4K3ThirdAbility() :
	lifetime(10.0f),
	radius(350.0f),
	period(1.0f)
{
	InitializationUtility::initAbilityId(__FILE__, id);
}

void USN4K3ThirdAbility::removeAbilityEffect(ABaseCharacter* target)
{
	target->setHealth(target->getHealth() * 2);

	TArray<UBaseWeapon*> weapons;

	weapons.Add(target->getDefaultWeapon());

	ABaseDrone* drone = Cast<ABaseDrone>(target);

	if (drone)
	{
		weapons.Add(drone->getFirstWeapon());

		weapons.Add(drone->getSecondWeapon());
	}

	for (auto& i : weapons)
	{
		if (i)
		{
			i->setDamage(i->getDamage() * 2.0f / 3.0f);
		}
	}
}

void USN4K3ThirdAbility::setIsFlagExist(bool isFlagExist)
{
	this->isFlagExist = isFlagExist;
}

bool USN4K3ThirdAbility::getIsFlagExist() const
{
	return isFlagExist;
}

void USN4K3ThirdAbility::applyAbility(ABaseCharacter* target)
{
	float health;
	float currentHealth = target->getCurrentHealth();
	
	target->setHealth(target->getHealth() * 0.5f);

	health = target->getHealth();

	if (health < currentHealth)
	{
		target->setCurrentHealth(health);
	}

	TArray<UBaseWeapon*> weapons;

	weapons.Add(target->getDefaultWeapon());

	ABaseDrone* drone = Cast<ABaseDrone>(target);

	if (drone)
	{
		weapons.Add(drone->getFirstWeapon());

		weapons.Add(drone->getSecondWeapon());
	}

	for (auto& i : weapons)
	{
		if (i)
		{
			i->setDamage(i->getDamage() * 1.5f);
		}
	}

	ICaster::Execute_applyThirdAbilityEvent(Cast<UObject>(caster), target);
}

void USN4K3ThirdAbility::useAbility()
{
	ASN4K3* drone = Cast<ASN4K3>(caster);
	FVector tem = drone->GetActorForwardVector() * 200;

	tem.Z += drone->GetMesh()->GetRelativeLocation().Z;

	ASN4K3ThirdAbilityFlag* flag = drone->GetWorld()->GetGameState<ALostConnectionGameState>()->spawn<ASN4K3ThirdAbilityFlag>({ drone->GetActorRotation(), tem + drone->GetActorLocation() });

	flag->setLifetime(lifetime);

	flag->setRadius(radius);

	flag->setAbility(this);

	flag->setPeriod(period);

	flag->FinishSpawning({}, true);

	isFlagExist = true;

	Cast<USN4K3PassiveAbility>(drone->getPassiveAbility())->resetLastTimeAbilityUsed();
}
