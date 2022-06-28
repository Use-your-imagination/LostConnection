// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "BaseBot.h"
#include "Interfaces/AI/SupportBot.h"

#include "BaseSupportBot.generated.h"

UCLASS(Abstract)
class LOSTCONNECTION_API ABaseSupportBot : 
	public ABaseBot,
	public ISupportBot
{
	GENERATED_BODY()
	
public:
	ABaseSupportBot() = default;

	virtual ~ABaseSupportBot() = default;
};
