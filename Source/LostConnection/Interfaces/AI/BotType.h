// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "Utility/Enums.h"

#include "BotType.generated.h"

UINTERFACE(BlueprintType, Meta = (CannotImplementInterfaceInBlueprint))
class UBotType : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IBotType
{
	GENERATED_BODY()

public:
	IBotType() = default;

	UFUNCTION(Category = Bots, BlueprintCallable)
	virtual EBotType getBotType() const = 0;
};
