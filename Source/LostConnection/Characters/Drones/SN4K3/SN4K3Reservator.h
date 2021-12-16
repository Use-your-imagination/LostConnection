// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/NoExportTypes.h"

#include "Interfaces/Gameplay/Descriptions/Sockets/Reservator.h"

#include "SN4K3Reservator.generated.h"

UCLASS(BlueprintType, Blueprintable)
class LOSTCONNECTION_API USN4K3Reservator : 
	public UObject,
	public IReservator
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = SN4K3, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float healthReservePercent;

	UPROPERTY(Category = SN4K3, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float naniteIcreasedDamage;

	UPROPERTY(Category = SN4K3, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float reservedHealth;

	float buffDuration;

private:
	virtual bool IsSupportedForNetworking() const final override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
public:
	USN4K3Reservator() = default;

	void setBuffDuration(float buffDuration);

	void useSocketItem(class ABaseCharacter* target) override;

	void reserve(class ABaseCharacter* target) override;

	void restoreReserved(class ABaseCharacter* target) override;

	virtual ~USN4K3Reservator() = default;
};
