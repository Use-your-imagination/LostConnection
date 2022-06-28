// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "BotType.h"

#include "RangedBot.generated.h"

UINTERFACE()
class URangedBot : public UBotType
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IRangedBot : public IBotType
{
	GENERATED_BODY()

public:
	IRangedBot() = default;

	EBotType getBotType() const override;
};
