// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "Modules/BasePersonalModule.h"

#include "PersonalModulesHolder.generated.h"

UINTERFACE(BlueprintType, MinimalAPI)
class UPersonalModulesHolder : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IPersonalModulesHolder
{
	GENERATED_BODY()

public:
	IPersonalModulesHolder() = default;

	virtual void addPersonalModule(UBasePersonalModule* module) = 0;

	virtual const TArray<UBasePersonalModule*>& getPersonalEquippedModules() const = 0;

	virtual const TArray<UBasePersonalModule*>& getPersonalUnequippedModules() const = 0;
};
