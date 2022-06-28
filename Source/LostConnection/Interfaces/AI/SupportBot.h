// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "BotType.h"

#include "SupportBot.generated.h"

UINTERFACE()
class USupportBot : public UBotType
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API ISupportBot : public IBotType
{
	GENERATED_BODY()

public:
	ISupportBot() = default;

	EBotType getBotType() const override;
};
