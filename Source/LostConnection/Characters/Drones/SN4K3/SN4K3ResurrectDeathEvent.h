// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/NoExportTypes.h"
#include "UObject/WeakInterfacePtr.h"

#include "Interfaces/Gameplay/Descriptions/Observers/GameplayEvents/OnDeathEvent.h"

#include "SN4K3ResurrectDeathEvent.generated.h"

#pragma warning(disable: 4458)

UCLASS()
class LOSTCONNECTION_API USN4K3ResurrectDeathEvent :
	public UObject,
	public IOnDeathEvent
{
	GENERATED_BODY()

private:
	TWeakInterfacePtr<class IDeathEventsHolder> holder;

	TWeakObjectPtr<class ASN4K3PassiveAbilityHead> head;
	
public:
	USN4K3ResurrectDeathEvent() = default;

	void initHead(class ASN4K3PassiveAbilityHead* head);

	void initDeathEvent(class IDeathEventsHolder* holder) override;

	void deathEventAction() override;

	class IDeathEventsHolder* getDeathEventsHolder() const override;

	~USN4K3ResurrectDeathEvent() = default;
};
