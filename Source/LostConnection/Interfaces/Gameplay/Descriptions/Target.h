// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"
#include "UObject/WeakInterfacePtr.h"

#include "EnvironmentTarget.h"

#include "Target.generated.h"

UINTERFACE(BlueprintType, MinimalAPI)
class UTarget : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API ITarget
{
	GENERATED_BODY()

private:
	TWeakObjectPtr<class ABaseCharacter> objectTarget;
	FVector positionTarget;
	TWeakInterfacePtr<IEnvironmentTarget> environmentTarget;

public:
	ITarget() = default;

	virtual void setObjectTarget(class ABaseCharacter* objectTarget);

	virtual void setPositionTarget(const FVector& positionTarget);

	virtual void setEnvironmentTarget(const TScriptInterface<IEnvironmentTarget>& environmentTarget);

	virtual TWeakObjectPtr<class ABaseCharacter>& getObjectTarget();

	virtual const FVector& getPositionTarget() const;

	virtual TWeakInterfacePtr<IEnvironmentTarget>& getEnvironmentTarget();
};
