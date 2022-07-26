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

	UPROPERTY()
	TObjectPtr<AController> damageInstigator;

private:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UDamageInflictorUtility() = default;

	UFUNCTION(Server, Reliable)
	void setDamageInstigator(AController* newDamageInstigator);

	float calculateTotalDamage(const TScriptInterface<class IDamageReceiver>& receiver = nullptr) const override;

	FDamageStructure& getDamage() override;

	const TObjectPtr<AController>& getDamageInstigator() const override;

	~UDamageInflictorUtility() = default;
};
