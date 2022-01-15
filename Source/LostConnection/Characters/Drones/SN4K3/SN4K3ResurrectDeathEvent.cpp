// Copyright (c) 2021 Use-your-imagination

#include "SN4K3ResurrectDeathEvent.h"

#include "Interfaces/Gameplay/Descriptions/ObserverHolders/GameplayEvents/DeathEventsHolder.h"
#include "SN4K3PassiveAbilityHead.h"
#include "SN4K3.h"
#include "Engine/LostConnectionGameState.h"
#include "AssetLoading/LostConnectionAssetManager.h"

TWeakInterfacePtr<IDeathEventsHolder>& USN4K3ResurrectDeathEvent::getDeathEventsHolder()
{
	return holder;
}

void USN4K3ResurrectDeathEvent::init(ALostConnectionPlayerController* controller, const FTransform& respawnTransform)
{
	this->respawnTransform = respawnTransform;
	this->controller = controller;
}

void USN4K3ResurrectDeathEvent::deathEventAction()
{
	if (!IsValid(controller))
	{
		return;
	}

	TSubclassOf<ABaseDrone> droneClass = Utility::findDroneClass(ULostConnectionAssetManager::get().getDrones(), ASN4K3::StaticClass());
	ASN4K3* drone = Utility::getGameState(controller)->spawn<ASN4K3>(droneClass, respawnTransform);

	controller->GetPlayerState<ALostConnectionPlayerState>()->resetCurrentUI();

	controller->Possess(drone);

	drone->FinishSpawning({}, true);
}

IDeathEventsHolder* USN4K3ResurrectDeathEvent::getDeathEventsHolder() const
{
	return holder.IsValid() ? holder.Get() : nullptr;
}
