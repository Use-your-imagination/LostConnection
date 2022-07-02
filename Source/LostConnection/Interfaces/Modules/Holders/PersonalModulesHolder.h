// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "Modules/Base/PersonalModules/BasePersonalModule.h"
#include "Inventory/InventoryCell.h"

#include "PersonalModulesHolder.generated.h"

UINTERFACE(BlueprintType, Meta = (CannotImplementInterfaceInBlueprint))
class UPersonalModulesHolder : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IPersonalModulesHolder
{
	GENERATED_BODY()

public:
	IPersonalModulesHolder() = default;

	virtual void addPersonalModule(TObjectPtr<UBasePersonalModule> module);

	UFUNCTION(Category = Modules, BlueprintCallable)
	virtual const TArray<UInventoryCell*>& getPersonalEquippedModules() const = 0;

	UFUNCTION(Category = Modules, BlueprintCallable)
	virtual const TArray<UInventoryCell*>& getPersonalUnequippedModules() const = 0;

	virtual const TArray<TObjectPtr<UInventoryCell>>& getActivePersonalModules() const = 0;
};
