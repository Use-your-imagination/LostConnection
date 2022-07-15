// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Interfaces/Gameplay/Descriptions/Base/DamageInflictor.h"

#include "DamageInflictorUtility.generated.h"

UCLASS(BlueprintType, DefaultToInstanced, EditInlineNew)
class LOSTCONNECTION_API UDamageInflictorUtility :
	public UNetworkObject,
	public IDamageInflictor
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = DamageInflictor, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	FDamageStructure damage;

	UPROPERTY(Category = Affecters, Replicated, BlueprintReadOnly, Meta = (MustImplement = DamageAffecter))
	TArray<TObjectPtr<UNetworkObject>> damageAffecters;

	UPROPERTY()
	TObjectPtr<AController> damageInstigator;

private:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UDamageInflictorUtility() = default;

	UFUNCTION(Server, Reliable)
	void setDamageInstigator(AController* newDamageInstigator);

	bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	float calculateTotalDamage() const override;

	FDamageStructure& getDamage() override;

	const TObjectPtr<AController>& getDamageInstigator() const override;

	~UDamageInflictorUtility() = default;
};
