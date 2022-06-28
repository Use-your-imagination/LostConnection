// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "BotType.h"

#include "AssassinBot.generated.h"

UINTERFACE()
class UAssassinBot : public UBotType
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IAssassinBot : public IBotType
{
	GENERATED_BODY()

public:
	IAssassinBot() = default;

	EBotType getBotType() const override;
};
