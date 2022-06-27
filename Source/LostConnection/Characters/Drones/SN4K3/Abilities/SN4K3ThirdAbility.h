// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Abilities/BaseAbility.h"
#include "Interfaces/Gameplay/Descriptions/Sockets/Socketed.h"
#include "Interfaces/Gameplay/Descriptions/Sockets/Reservator.h"
#include "Characters/Drones/SN4K3/SN4K3Reservator.h"

#include "SN4K3ThirdAbility.generated.h"

UCLASS()
class LOSTCONNECTION_API USN4K3ThirdAbility :
	public UBaseAbility,
	public ISocketed
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = SN4K3, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float lifetime;

	UPROPERTY(Category = SN4K3, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float radius;

	UPROPERTY(Category = SN4K3, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float period;

	UPROPERTY(Category = SN4K3, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (MustImplement = SocketItem, AllowPrivateAccess = "true"))
	TObjectPtr<UNetworkObject> socketItem;

	TWeakObjectPtr<class ASN4K3ThirdAbilityFlag> flagPointer;

private:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	USN4K3ThirdAbility();

	void applyAbility(class ABaseCharacter* target) override;

	void useAbility() override;

	void insert(const TScriptInterface<ISocketItem>& socketItem) override;

	void extract() override;

	bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	ISocketItem* getSocketItem() const override;

	~USN4K3ThirdAbility() = default;
};
