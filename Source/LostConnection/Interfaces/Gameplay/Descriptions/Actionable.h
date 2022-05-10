// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "Actionable.generated.h"

UINTERFACE(BlueprintType, Meta = (CannotImplementInterfaceInBlueprint))
class UActionable : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IActionable
{
	GENERATED_BODY()

protected:
	virtual void action(TObjectPtr<class ABaseDrone> player) = 0;

public:
	IActionable() = default;

	UFUNCTION()
	virtual void doAction(class ABaseDrone* player);

	UFUNCTION(Category = Actionable, BlueprintCallable)
	virtual bool isEnable() const;

	UFUNCTION(Category = Actionable, BlueprintCallable)
	virtual FText getActionMessage() const;
};
