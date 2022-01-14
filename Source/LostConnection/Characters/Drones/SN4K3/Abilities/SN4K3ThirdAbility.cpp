// Copyright (c) 2021 Use-your-imagination

#include "SN4K3ThirdAbility.h"

#include "Characters/Drones/SN4K3/SN4K3.h"
#include "Interfaces/Gameplay/Descriptions/Caster.h"
#include "Utility/InitializationUtility.h"
#include "WorldPlaceables/SN4K3/SN4K3ThirdAbilityFlag.h"
#include "Engine/LostConnectionGameState.h"
#include "SN4K3PassiveAbility.h"
#include "Characters/Drones/SN4K3/SN4K3Reservator.h"
#include "AssetLoading/LostConnectionAssetManager.h"

#pragma warning(disable: 4458)

void USN4K3ThirdAbility::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USN4K3ThirdAbility, lifetime);

	DOREPLIFETIME(USN4K3ThirdAbility, radius);

	DOREPLIFETIME(USN4K3ThirdAbility, period);

	DOREPLIFETIME(USN4K3ThirdAbility, socketItem);
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
	if (!IsValid(socketItem))
	{
		return;
	}

	Cast<ISocketItem>(socketItem)->useSocketItem(target);

	ICaster::Execute_applyThirdAbilityEvent(Cast<UObject>(caster), target);
}

void USN4K3ThirdAbility::useAbility()
{
	if (!IsValid(socketItem))
	{
		return;
	}

	ASN4K3* drone = Cast<ASN4K3>(caster);
	FVector tem = drone->GetActorForwardVector() * 200;

	tem.Z += drone->GetMesh()->GetRelativeLocation().Z;

	USN4K3Reservator* defaultReservator = Cast<USN4K3Reservator>(socketItem);

	if (defaultReservator)
	{
		defaultReservator->setBuffDuration(period);
	}

	ASN4K3ThirdAbilityFlag* flag = Utility::getGameState(drone)->spawn<ASN4K3ThirdAbilityFlag>({ drone->GetActorRotation(), tem + drone->GetActorLocation() });

	flag->setLifetime(lifetime);

	flag->setRadius(radius);

	flag->setAbility(this);

	flag->setPeriod(period);

	flag->FinishSpawning({}, true);

	isFlagExist = true;

	Cast<USN4K3PassiveAbility>(drone->getPassiveAbility())->resetLastTimeAbilityUsed();
}

void USN4K3ThirdAbility::initAbility()
{
	Super::initAbility();

	socketItem = NewObject<USN4K3Reservator>(this, ULostConnectionAssetManager::get().getStatuses().getDefaultSN4K3Reservator());
}

void USN4K3ThirdAbility::insert(const TScriptInterface<ISocketItem>& socketItem)
{
	this->socketItem = Cast<UNetworkObject>(socketItem->_getUObject());
}

void USN4K3ThirdAbility::extract()
{
	socketItem = nullptr;
}

bool USN4K3ThirdAbility::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool wroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	if (IsValid(socketItem))
	{
		wroteSomething |= Channel->ReplicateSubobject(socketItem, *Bunch, *RepFlags);

		wroteSomething |= socketItem->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	return wroteSomething;
}

ISocketItem* USN4K3ThirdAbility::getSocketItem() const
{
	return Cast<ISocketItem>(socketItem);
}
