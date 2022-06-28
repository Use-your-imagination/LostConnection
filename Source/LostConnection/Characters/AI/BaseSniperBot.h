// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "BaseBot.h"
#include "Interfaces/AI/SniperBot.h"

#include "BaseSniperBot.generated.h"

UCLASS(Abstract)
class LOSTCONNECTION_API ABaseSniperBot :
	public ABaseBot,
	public ISniperBot
{
	GENERATED_BODY()
	
public:
	ABaseSniperBot() = default;

	virtual ~ABaseSniperBot() = default;
};
