// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "BotType.h"

#include "CasterBot.generated.h"

UINTERFACE()
class UCasterBot : public UBotType
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API ICasterBot : public IBotType
{
	GENERATED_BODY()

public:
	ICasterBot() = default;

	EBotType getBotType() const override;
};
