// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "BotType.h"

#include "MeleeBot.generated.h"

UINTERFACE()
class UMeleeBot : public UBotType
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IMeleeBot : public IBotType
{
	GENERATED_BODY()

public:
	IMeleeBot() = default;

	EBotType getBotType() const override;
};
