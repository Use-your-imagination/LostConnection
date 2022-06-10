// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Modules/Base/WeaponModules/BaseDamageWeaponModule.h"

#include "PowderHeavy.generated.h"

UCLASS()
class LOSTCONNECTION_API UPowderHeavy : public UBaseDamageWeaponModule
{
	GENERATED_BODY()
	
public:
	UPowderHeavy() = default;

	~UPowderHeavy() = default;
};
