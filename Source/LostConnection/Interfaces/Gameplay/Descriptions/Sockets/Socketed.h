// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"
#include "UObject/WeakInterfacePtr.h"

#include "SocketItem.h"

#include "Socketed.generated.h"

UINTERFACE(BlueprintType, MinimalAPI)
class USocketed : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API ISocketed
{
	GENERATED_BODY()

public:
	ISocketed() = default;

	virtual void insert(const TScriptInterface<ISocketItem>& socketItem) = 0;

	virtual void extract() = 0;

	virtual ISocketItem* getSocketItem() const = 0;
};
