// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Network/NetworkObject.h"
#include "Interfaces/Gameplay/Statuses/Base/AilmentInflictor.h"
#include "DamageInflictorUtility.h"

#include "AilmentInflictorUtility.generated.h"

UCLASS(BlueprintType, DefaultToInstanced, EditInlineNew)
class LOSTCONNECTION_API UAilmentInflictorUtility :
	public UNetworkObject,
	public IAilmentInflictor
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = AilmentInflictor, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float baseCrushingHitChance;

	UPROPERTY(Category = AilmentInflictor, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float additionalCrushingHitChance;

	UPROPERTY(Category = AilmentInflictor, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	ETypeOfDamage damageType;

	UPROPERTY(Category = AilmentInflictor, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	TObjectPtr<UDamageInflictorUtility> damageInflictorUtility;

private:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UAilmentInflictorUtility();

	bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

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

	UFUNCTION(Server, Reliable)
	void setDamageType(ETypeOfDamage type) override;

	float getBaseDamage() const override;

	float getAddedDamage() const override;

	float getAdditionalDamage() const override;

	const TArray<float>& getIncreaseDamageCoefficients() const override;

	const TArray<float>& getMoreDamageCoefficients() const override;

	UFUNCTION(Server, Reliable)
	void setBaseCrushingHitChance(float crushingHitChance) override;

	UFUNCTION(Server, Reliable)
	void setAdditionalCrushingHitChance(float newAdditionalCrushingHitChance) override;

	ETypeOfDamage getDamageType() const override;

	float getBaseCrushingHitChance() const override;

	float getAdditionalCrushingHitChance() const override;

	TObjectPtr<AController> getDamageInstigator() const override;

	~UAilmentInflictorUtility() = default;

	friend class AAmmo;
};
