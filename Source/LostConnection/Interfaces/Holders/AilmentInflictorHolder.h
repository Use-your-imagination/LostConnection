// Copyright (c) 2022 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "Holders/Utility/AilmentInflictorUtility.h"

#include "AilmentInflictorHolder.generated.h"

UINTERFACE(BlueprintType, Meta = (CannotImplementInterfaceInBlueprint))
class UAilmentInflictorHolder : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IAilmentInflictorHolder
{
	GENERATED_BODY()

public:
	IAilmentInflictorHolder() = default;

	UFUNCTION(Category = "Utility|AilmentInflictor", BlueprintCallable)
	virtual UAilmentInflictorUtility* getAilmentInflictorUtility() const = 0;
};
