// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "BaseBot.h"
#include "Interfaces/AI/AssassinBot.h"

#include "BaseAssassinBot.generated.h"

UCLASS(Abstract)
class LOSTCONNECTION_API ABaseAssassinBot :
	public ABaseBot,
	public IAssassinBot
{
	GENERATED_BODY()
	
public:
	ABaseAssassinBot() = default;

	virtual ~ABaseAssassinBot() = default;
};
