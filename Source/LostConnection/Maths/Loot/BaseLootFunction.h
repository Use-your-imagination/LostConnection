// Copyright (c) 2022 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/NoExportTypes.h"

#include "BaseLootFunction.generated.h"

UCLASS(BlueprintType, Blueprintable)
class LOSTCONNECTION_API UBaseLootFunction : public UObject
{
	GENERATED_BODY()
	
public:
	UBaseLootFunction() = default;

	UFUNCTION(Category = "Maths|Loot", BlueprintNativeEvent)
	float calculateLootChance(int32 lootPoints) const;

	UFUNCTION(Category = "Maths|Loot", BlueprintNativeEvent)
	void getRange(int32& soft, int32& hard) const;

	UFUNCTION(Category = "UI|Loot", BlueprintNativeEvent)
	FText getLootName() const;

	virtual ~UBaseLootFunction() = default;
};
