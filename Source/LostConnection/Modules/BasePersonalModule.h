// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "BaseModule.h"

#include "BasePersonalModule.generated.h"

UCLASS()
class LOSTCONNECTION_API UBasePersonalModule : public UBaseModule
{
	GENERATED_BODY()
	
public:
	UBasePersonalModule() = default;

	virtual ~UBasePersonalModule() = default;
};
