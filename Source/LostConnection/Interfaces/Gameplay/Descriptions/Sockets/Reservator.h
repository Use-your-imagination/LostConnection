// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "SocketItem.h"

#include "Reservator.generated.h"

UINTERFACE(MinimalAPI)
class UReservator : public USocketItem
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IReservator : public ISocketItem
{
	GENERATED_BODY()

public:
	IReservator() = default;

	virtual void reserve(class ABaseCharacter* target) = 0;

	virtual void restoreReserved(class ABaseCharacter* target) = 0;
};
