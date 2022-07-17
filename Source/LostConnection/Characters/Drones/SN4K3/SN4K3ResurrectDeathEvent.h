// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/NoExportTypes.h"

#include "Interfaces/Gameplay/Descriptions/Observers/OnDeathEvent.h"
#include "Network/NetworkObject.h"
#include "Engine/LostConnectionPlayerController.h"

#include "SN4K3ResurrectDeathEvent.generated.h"

#pragma warning(disable: 4458)

UCLASS()
class LOSTCONNECTION_API USN4K3ResurrectDeathEvent :
	public UNetworkObject,
	public IOnDeathEvent
{
	GENERATED_BODY()

private:
	TWeakInterfacePtr<class IDeathEventsHolder> holder;
	FVector respawnLocation;
	TObjectPtr<ALostConnectionPlayerController> controller;
	
public:
	USN4K3ResurrectDeathEvent() = default;

	void init(TObjectPtr<ALostConnectionPlayerController> controller, const FVector& respawnLocation);

	void deathEventAction(TObjectPtr<class ABaseCharacter> character) override;

	TWeakInterfacePtr<class IDeathEventsHolder>& getDeathEventsHolder() override;

	~USN4K3ResurrectDeathEvent() = default;
};
