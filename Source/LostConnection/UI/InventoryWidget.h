// Copyright (c) 2022 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "Inventory/Inventory.h"

#include "InventoryWidget.generated.h"

UCLASS(Blueprintable)
class LOSTCONNECTION_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Category = Inventory, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	UInventory* inventory;

public:
	UInventoryWidget* init(class ALostConnectionPlayerState* playerState);

	UFUNCTION(Category = Events, BlueprintNativeEvent)
	void onShow();

	UFUNCTION(Category = Events, BlueprintNativeEvent)
	void onHide();

	virtual ~UInventoryWidget() = default;
};
