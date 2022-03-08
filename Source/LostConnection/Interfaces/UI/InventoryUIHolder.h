// Copyright (c) 2022 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "UI/InventoryWidget.h"

#include "InventoryUIHolder.generated.h"

UINTERFACE(BlueprintType)
class UInventoryUIHolder : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IInventoryUIHolder
{
	GENERATED_BODY()

public:
	IInventoryUIHolder() = default;

	UFUNCTION(Category = Inventory, BlueprintNativeEvent, BlueprintCallable)
	void showInventory(APlayerController* playerController);

	UFUNCTION(Category = Inventory, BlueprintNativeEvent, BlueprintCallable)
	void hideInventory(APlayerController* playerController);

	UFUNCTION(Category = Inventory, BlueprintNativeEvent, BlueprintCallable)
	UInventoryWidget* getInventoryWidget() const;

	virtual void hideInventory_Implementation(APlayerController* playerController);

	virtual void showInventory_Implementation(APlayerController* playerController);
};
