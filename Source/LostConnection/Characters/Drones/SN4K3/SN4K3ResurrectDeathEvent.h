// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/NoExportTypes.h"

#include "Interfaces/Gameplay/Descriptions/Observers/GameplayEvents/OnDeathEvent.h"
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
	FTransform respawnTransform;
	ALostConnectionPlayerController* controller;

private:
	TWeakInterfacePtr<class IDeathEventsHolder>& getDeathEventsHolder() override;
	
public:
	USN4K3ResurrectDeathEvent() = default;

	void init(ALostConnectionPlayerController* controller, const FTransform& respawnTransform);

	void deathEventAction() override;

	class IDeathEventsHolder* getDeathEventsHolder() const override;

	~USN4K3ResurrectDeathEvent() = default;
};
