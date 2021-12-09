// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Statuses/BaseImpactStatus.h"
#include "Interfaces/Gameplay/Statuses/Ailment.h"

#include "IrradiationAilment.generated.h"

UCLASS()
class LOSTCONNECTION_API UIrradiationAilment :
	public UBaseImpactStatus,
	public IDamageInflictor,
	public IAilment
{
	GENERATED_BODY()
	
private:
	float damage;
	float additionalDamage;

private:
	FString getStatusName() const override;

	SIZE_T getActiveStatusesCount() const override;

public:
	UIrradiationAilment() = default;

	void applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<class IStatusReceiver>& target, const FHitResult& hit) override;

	UFUNCTION(Server, Reliable)
	void setInflictorDamage(float newDamage) override;

	UFUNCTION(Server, Reliable)
	void setAdditionalInflictorDamage(float newAdditionalDamage) override;

	float getInflictorDamage() const override;

	float getAdditionalInflictorDamage() const override;

	typeOfDamage getAilmentDamageType() const override;

	virtual ~UIrradiationAilment() = default;
};
