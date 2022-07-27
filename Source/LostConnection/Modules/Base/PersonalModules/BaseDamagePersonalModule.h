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
	FDamageStructure moduleDamage;
	
public:
	UBaseDamagePersonalModule() = default;

	virtual bool applyCondition(TObjectPtr<AActor> caller) const override;

	virtual bool affectCondition(const TScriptInterface<IDamageInflictor>& inflictor, const TScriptInterface<IDamageReceiver>& receiver) const override;

	void affect(FDamageStructure& damage) override;

	virtual ~UBaseDamagePersonalModule() = default;
};
