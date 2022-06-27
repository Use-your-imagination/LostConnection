// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Network/NetworkObject.h"
#include "Interfaces/Gameplay/Descriptions/Sockets/Reservator.h"

#include "SN4K3Reservator.generated.h"

UCLASS(BlueprintType, Blueprintable)
class LOSTCONNECTION_API USN4K3Reservator : 
	public UNetworkObject,
	public IReservator
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = SN4K3, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	float healthReservePercent;

	UPROPERTY(Category = SN4K3, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	float naniteIcreasedDamage;

	UPROPERTY(Category = SN4K3, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	float reservedHealth;

	float buffDuration;

private:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
public:
	USN4K3Reservator() = default;

	void setBuffDuration(float buffDuration);

	void useSocketItem(class ABaseCharacter* target) override;

	void reserve(class ABaseCharacter* target) override;

	void restoreReserved(class ABaseCharacter* target) override;

	~USN4K3Reservator() = default;
};
