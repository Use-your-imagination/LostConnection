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

USTRUCT(BlueprintType)
struct LOSTCONNECTION_API FStatDescription
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = Description, BlueprintReadOnly)
	FText name;

	UPROPERTY(Category = Description, BlueprintReadOnly)
	float value;

	UPROPERTY(Category = Description, BlueprintReadOnly)
	FText nameTooltip;

	UPROPERTY(Category = Description, BlueprintReadOnly)
	FText valueTooltip;

	FStatDescription() = default;

	FStatDescription(const FText& name, float value, const FText& nameTooltip, const FText& valueTooltip);
};
