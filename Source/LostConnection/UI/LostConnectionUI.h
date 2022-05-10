// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "Interfaces/UI/Playerholder.h"
#include "Interfaces/UI/InventoryUIHolder.h"

#include "LostConnectionUI.generated.h"

#pragma warning(disable: 4458)

UCLASS(BlueprintType, Blueprintable)
class LOSTCONNECTION_API ULostConnectionUI :
	public UUserWidget,
	public IPlayerHolder,
	public IInventoryUIHolder
{
	GENERATED_BODY()
	
protected:
	class ABaseDrone* player;

	UPROPERTY()
	UInventoryWidget* inventoryWidget;

public:
	void init(class ABaseDrone* player);

	UFUNCTION(Category = Initialization, BlueprintNativeEvent)
	void UIConstruction();

	UFUNCTION(Category = EnergyShield, BlueprintNativeEvent)
	void onEnergyShieldUpdate();

	void setPlayer_Implementation(APawn* playerPawn) override;

	APawn* getPlayer_Implementation() const override;

	UInventoryWidget* getInventoryWidget_Implementation() const override;

	virtual ~ULostConnectionUI() = default;
};
