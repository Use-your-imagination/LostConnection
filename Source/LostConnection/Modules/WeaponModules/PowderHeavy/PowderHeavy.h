// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Modules/Base/WeaponModules/BaseDamageWeaponModule.h"

#include "PowderHeavy.generated.h"

UCLASS()
class LOSTCONNECTION_API UPowderHeavy : public UBaseDamageWeaponModule
{
	GENERATED_BODY()

protected:
	virtual TArray<FFormatArgumentValue> getFormatArguments() const override;
	
public:
	UPowderHeavy() = default;

	bool applyCondition(TObjectPtr<AActor> caller) const override;

	~UPowderHeavy() = default;
};
