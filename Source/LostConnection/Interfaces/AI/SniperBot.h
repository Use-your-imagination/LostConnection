// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "BotType.h"

#include "SniperBot.generated.h"

UINTERFACE()
class USniperBot : public UBotType
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API ISniperBot : public IBotType
{
	GENERATED_BODY()

public:
	ISniperBot() = default;

	EBotType getBotType() const override;
};
