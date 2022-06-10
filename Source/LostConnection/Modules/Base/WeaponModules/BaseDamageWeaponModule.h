// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Modules/Base/WeaponModules/BaseWeaponModule.h"
#include "Interfaces/Modules/Damage/DamageModule.h"

#include "BaseDamageWeaponModule.generated.h"

UCLASS(Abstract)
class LOSTCONNECTION_API UBaseDamageWeaponModule :
	public UBaseWeaponModule,
	public IDamageModule
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(Category = Module, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float addedDamage;

	UPROPERTY(Category = Module, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float increaseDamageCoefficient;

	UPROPERTY(Category = Module, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float moreDamageCoefficient;

	UPROPERTY(Category = Module, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float additionalDamage;

public:
	UBaseDamageWeaponModule() = default;

	virtual bool applyCondition(TObjectPtr<AActor> caller) const override;

	virtual float getAddedDamage() const final override;

	virtual float getIncreaseDamageCoefficient() const final override;

	virtual float getMoreDamageCoefficient() const final override;

	virtual float getAdditionalDamage() const final override;

	virtual ~UBaseDamageWeaponModule() = default;
};
