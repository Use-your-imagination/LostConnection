// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "BaseBot.h"
#include "Interfaces/AI/MeleeBot.h"

#include "BaseMeleeBot.generated.h"

UCLASS(Abstract)
class LOSTCONNECTION_API ABaseMeleeBot :
	public ABaseBot,
	public IMeleeBot
{
	GENERATED_BODY()
	
public:
	ABaseMeleeBot() = default;

	virtual ~ABaseMeleeBot() = default;
};
