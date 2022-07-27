// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Kismet/BlueprintFunctionLibrary.h"

#include "Interfaces/Gameplay/Descriptions/Base/DamageInflictor.h"

#include "FormulaLibrary.generated.h"

UCLASS()
class LOSTCONNECTION_API UFormulaLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(Category = Maths, BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Standard Formula"))
	static float standardFormulaArguments(float base, float added, const TArray<float>& increaseCoefficients, const TArray<float>& moreCoefficients, float additional);

	UFUNCTION(Category = Maths, BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Standard Formula"))
	static float standardFormulaDamage(const FDamageStructure& damage);
};
