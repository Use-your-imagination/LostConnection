// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Network/NetworkObject.h"

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
	float baseInflictorDamage;

	UPROPERTY(Category = DamageInflictor, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float addedInflictorDamage;

	UPROPERTY(Category = DamageInflictor, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float additionalInflictorDamage;

	UPROPERTY(Category = DamageInflictor, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	TArray<float> increaseInflictorDamageCoefficients;

	UPROPERTY(Category = DamageInflictor, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	TArray<float> moreInflictorDamageCoefficients;

	UPROPERTY(Category = Instigator, Replicated, BlueprintReadOnly)
	TObjectPtr<AController> damageInstigator;

private:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UDamageInflictorUtility() = default;

	UFUNCTION(Server, Reliable)
	void setDamageInstigator(AController* newDamageInstigator);

	void PostInitProperties() override;

	void appendIncreaseDamageCoefficient(float coefficient) override;

	void removeIncreaseDamageCoefficient(float coefficient) override;

	void appendMoreDamageCoefficient(float coefficient) override;

	void removeMoreDamageCoefficient(float coefficient) override;

	UFUNCTION(Server, Reliable)
	void setBaseDamage(float newDamage) override;

	UFUNCTION(Server, Reliable)
	void setAddedDamage(float newAddedDamage) override;

	UFUNCTION(Server, Reliable)
	void setAdditionalDamage(float newAdditionalDamage) override;

	float getBaseDamage() const override;

	float getAddedDamage() const override;

	float getAdditionalDamage() const override;

	const TArray<float>& getIncreaseDamageCoefficients() const override;

	const TArray<float>& getMoreDamageCoefficients() const override;

	TObjectPtr<AController> getDamageInstigator() const override;

	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	~UDamageInflictorUtility() = default;
};
