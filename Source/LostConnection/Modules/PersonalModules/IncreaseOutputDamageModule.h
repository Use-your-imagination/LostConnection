// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Modules/BasePersonalModule.h"
#include "Interfaces/Modules/Damage/DamageModule.h"

#include "IncreaseOutputDamageModule.generated.h"

UCLASS()
class LOSTCONNECTION_API UIncreaseOutputDamageModule : 
	public UBasePersonalModule,
	public IDamageModule
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = Module, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float moreDamageCoefficient;
	
public:
	UIncreaseOutputDamageModule() = default;

	bool applyCondition(TObjectPtr<AActor> caller) const override;

	float getAddedDamage() const override;

	float getIncreaseDamageCoefficient() const override;

	float getMoreDamageCoefficient() const override;

	float getAdditionalDamage() const override;

	~UIncreaseOutputDamageModule() = default;
};
