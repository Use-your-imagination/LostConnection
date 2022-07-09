// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "BehaviorTree/BTCompositeNode.h"

#include "BTComposite_RandomizedSelector.generated.h"

/**
 * Randomized Selector composite node.
 * Randomized Selector Nodes execute their children from left to right with chance, and will stop executing its children when one of their children succeeds.
 * If a Randomized Selector's child succeeds, the Randomized Selector succeeds. If all the Randomized Selector's children fail, the Randomized Selector fails.
 * Each node must have percent chance to execute
 * If current node not called, next node chance will summarize previous nodes chances
 * Summary chance must be 100%
 */
UCLASS()
class LOSTCONNECTION_API UBTComposite_RandomizedSelector : public UBTCompositeNode
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Category = Randomized, EditAnywhere)
	TArray<float> executionChances;

	UPROPERTY()
	mutable TArray<float> realExecutionChances;

private:
	int32 GetNextChildHandler(FBehaviorTreeSearchData& SearchData, int32 PrevChild, EBTNodeResult::Type LastResult) const override;

public:
	UBTComposite_RandomizedSelector();

#if WITH_EDITOR
	virtual FName GetNodeIconName() const override;
#endif
};
