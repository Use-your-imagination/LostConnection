// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "Modules/Base/WeaponModules/BaseWeaponModule.h"
#include "Inventory/InventoryCell.h"

#include "WeaponModulesHolder.generated.h"

UINTERFACE(BlueprintType)
class UWeaponModulesHolder : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IWeaponModulesHolder
{
	GENERATED_BODY()

public:
	IWeaponModulesHolder() = default;

	virtual void addWeaponModule(TObjectPtr<UBaseWeaponModule> module) = 0;

	virtual const TArray<UInventoryCell*>& getWeaponModules() const = 0;

	virtual const TArray<TObjectPtr<UInventoryCell>>& getActiveWeaponModules() const = 0;
};
