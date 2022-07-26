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
	UPROPERTY(Category = Module, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	FDamageStructure moduleDamage;

public:
	UBaseDamageWeaponModule() = default;

	virtual bool applyCondition(TObjectPtr<AActor> caller) const override;

	virtual bool affectCondition(const TObjectPtr<AActor>& affectedActor) const override;

	void affect(FDamageStructure& damage) override;

	virtual ~UBaseDamageWeaponModule() = default;
};
