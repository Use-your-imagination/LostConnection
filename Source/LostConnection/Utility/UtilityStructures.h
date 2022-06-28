// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "UtilityStructures.generated.h"

UENUM()
enum class EUtilityStructures
{
	NONE
};

DECLARE_DYNAMIC_DELEGATE(FStandardDelegate);

USTRUCT(BlueprintType)
struct LOSTCONNECTION_API FStandardDelegateHolder
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FStandardDelegate delegate;
};
