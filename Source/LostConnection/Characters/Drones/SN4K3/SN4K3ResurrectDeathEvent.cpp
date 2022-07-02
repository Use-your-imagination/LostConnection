// Copyright (c) 2021 Use Your Imagination

#include "SN4K3ResurrectDeathEvent.h"

#include "Kismet/GameplayStatics.h"

#include "Interfaces/Gameplay/Descriptions/ObserverHolders/DeathEventsHolder.h"
#include "SN4K3PassiveAbilityHead.h"
#include "SN4K3.h"
#include "Engine/LostConnectionGameState.h"
#include "AssetLoading/LostConnectionAssetManager.h"

void USN4K3ResurrectDeathEvent::init(TObjectPtr<ALostConnectionPlayerController> controller, const FTransform& respawnTransform)
{
	this->respawnTransform = respawnTransform;
	this->controller = controller;
}

void USN4K3ResurrectDeathEvent::deathEventAction()
{
	if (!IsValid(controller) || controller->GetPawn<ASN4K3>())
	{
		return;
	}

	TSubclassOf<ABaseDrone> droneClass = Utility::findDroneClass(ULostConnectionAssetManager::get().getDrones(), ASN4K3::StaticClass());
	TObjectPtr<ASN4K3> drone = Utility::getGameState(controller)->spawn<ASN4K3>(droneClass, respawnTransform);

	controller->GetPlayerState<ALostConnectionPlayerState>()->resetCurrentUI();

	controller->Possess(drone);

	drone->FinishSpawning({}, true);
}

TWeakInterfacePtr<IDeathEventsHolder>& USN4K3ResurrectDeathEvent::getDeathEventsHolder()
{
	return holder;
}
