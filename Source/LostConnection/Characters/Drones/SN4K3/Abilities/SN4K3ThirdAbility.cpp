// Copyright (c) 2021 Use-your-imagination

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
	if (reservator.IsValid())
	{
		reservator->useSocketItem(target);

		ICaster::Execute_applyThirdAbilityEvent(Cast<UObject>(caster), target);
	}
}

void USN4K3ThirdAbility::useAbility()
{
	ASN4K3* drone = Cast<ASN4K3>(caster);
	FVector tem = drone->GetActorForwardVector() * 200;

	tem.Z += drone->GetMesh()->GetRelativeLocation().Z;

	ASN4K3ThirdAbilityFlag* flag = Utility::getGameState(drone)->spawn<ASN4K3ThirdAbilityFlag>({drone->GetActorRotation(), tem + drone->GetActorLocation()});

	flag->setLifetime(lifetime);

	flag->setRadius(radius);

	flag->setAbility(this);

	flag->setPeriod(period);

	flag->FinishSpawning({}, true);

	isFlagExist = true;

	Cast<USN4K3PassiveAbility>(drone->getPassiveAbility())->resetLastTimeAbilityUsed();
}

void USN4K3ThirdAbility::insert(const TScriptInterface<ISocketItem>& socketItem)
{
	reservator = StaticCast<IReservator*>(socketItem.GetInterface());
}

void USN4K3ThirdAbility::extract()
{
	reservator.Reset();
}

ISocketItem* USN4K3ThirdAbility::getSocketItem() const
{
	return reservator.IsValid() ? reservator.Get() : nullptr;
}
