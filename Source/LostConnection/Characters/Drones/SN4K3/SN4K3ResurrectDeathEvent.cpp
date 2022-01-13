// Copyright (c) 2021 Use-your-imagination

#include "SN4K3ResurrectDeathEvent.h"

#include "Interfaces/Gameplay/Descriptions/ObserverHolders/GameplayEvents/DeathEventsHolder.h"
#include "SN4K3PassiveAbilityHead.h"
#include "SN4K3.h"
#include "Engine/LostConnectionGameState.h"
#include "AssetLoading/LostConnectionAssetManager.h"

void USN4K3ResurrectDeathEvent::initHead(ASN4K3PassiveAbilityHead* head)
{
	this->head = head;
}

void USN4K3ResurrectDeathEvent::initDeathEvent(IDeathEventsHolder* holder)
{
	if (this->holder.IsValid())
	{
		this->holder->detachDeathEvent(this);
	}

	this->holder = holder;

	holder->attachDeathEvent(this);
}

void USN4K3ResurrectDeathEvent::deathEventAction()
{
	if (!head.IsValid())
	{
		return;
	}

	TSubclassOf<ABaseDrone> droneClass = Utility::findDroneClass(ULostConnectionAssetManager::get().getDrones(), ASN4K3::StaticClass());
	ASN4K3* drone = head->GetWorld()->GetGameState<ALostConnectionGameState>()->spawn<ASN4K3>(droneClass, head->GetActorTransform());

	Utility::getPlayerState(head.Get())->resetCurrentUI();

	head->GetController()->Possess(drone);

	drone->FinishSpawning({}, true);

	head->Destroy();
}

IDeathEventsHolder* USN4K3ResurrectDeathEvent::getDeathEventsHolder() const
{
	return holder.IsValid() ? holder.Get() : nullptr;
}
