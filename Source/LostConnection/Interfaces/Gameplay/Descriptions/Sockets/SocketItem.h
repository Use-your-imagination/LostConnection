// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "SocketItem.generated.h"

UINTERFACE(BlueprintType)
class USocketItem : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API ISocketItem
{
	GENERATED_BODY()

public:
	ISocketItem() = default;

	virtual void useSocketItem(class ABaseCharacter* target) = 0;
};
