// Copyright (c) 2022 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "PlayerHolder.generated.h"

UINTERFACE(BlueprintType)
class UPlayerHolder : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IPlayerHolder
{
	GENERATED_BODY()

public:
	IPlayerHolder() = default;

	UFUNCTION(Category = Player, BlueprintNativeEvent, BlueprintCallable)
	void setPlayer(class APawn* playerPawn);

	UFUNCTION(Category = Player, BlueprintNativeEvent, BlueprintCallable)
	APawn* getPlayer() const;
};
