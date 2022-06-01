// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "Modules/Base/PersonalModules/BasePersonalModule.h"

#include "PersonalModulesHolder.generated.h"

UINTERFACE(BlueprintType)
class UPersonalModulesHolder : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IPersonalModulesHolder
{
	GENERATED_BODY()

public:
	IPersonalModulesHolder() = default;

	virtual void addPersonalModule(TObjectPtr<UBasePersonalModule> module) = 0;

	virtual TArray<UBasePersonalModule*> getPersonalEquippedModules() const = 0;

	virtual TArray<UBasePersonalModule*> getPersonalUnequippedModules() const = 0;
};
