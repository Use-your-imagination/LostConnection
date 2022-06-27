// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "BasePersonalModule.h"
#include "Interfaces/Modules/Damage/DamageModule.h"

#include "BaseDamagePersonalModule.generated.h"

UCLASS(Abstract)
class LOSTCONNECTION_API UBaseDamagePersonalModule :
	public UBasePersonalModule,
	public IDamageModule
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = Module, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	float addedDamage;

	UPROPERTY(Category = Module, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	float increaseDamageCoefficient;

	UPROPERTY(Category = Module, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	float moreDamageCoefficient;

	UPROPERTY(Category = Module, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	float additionalDamage;
	
public:
	UBaseDamagePersonalModule() = default;

	virtual bool applyCondition(TObjectPtr<AActor> caller) const override;

	virtual float getAddedDamage() const final override;

	virtual float getIncreaseDamageCoefficient() const final override;

	virtual float getMoreDamageCoefficient() const final override;

	virtual float getAdditionalDamage() const final override;

	virtual ~UBaseDamagePersonalModule() = default;
};
