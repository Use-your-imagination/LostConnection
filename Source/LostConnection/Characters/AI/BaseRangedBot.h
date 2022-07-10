// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "BaseBot.h"
#include "Interfaces/AI/RangedBot.h"

#include "BaseRangedBot.generated.h"

UCLASS(Abstract)
class LOSTCONNECTION_API ABaseRangedBot :
	public ABaseBot,
	public IRangedBot
{
	GENERATED_BODY()
	
public:
	ABaseRangedBot();

	virtual ~ABaseRangedBot() = default;
};
