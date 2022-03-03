// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Interfaces/UI/Playerholder.h"

#include "LostConnectionUI.generated.h"

#pragma warning(disable: 4458)

UCLASS(BlueprintType, Blueprintable)
class LOSTCONNECTION_API ULostConnectionUI :
	public UUserWidget,
	public IPlayerHolder
{
	GENERATED_BODY()
	
protected:
	class ABaseDrone* player;

public:
	ULostConnectionUI(const FObjectInitializer& objectInitializer);

	void init(class ABaseDrone* player);

	UFUNCTION(Category = Initialization, BlueprintNativeEvent)
	void UIConstruction();

	UFUNCTION(Category = EnergyShield, BlueprintNativeEvent)
	void onEnergyShieldUpdate();

	UFUNCTION()
	void setPlayer_Implementation(APawn* playerPawn) override;

	UFUNCTION()
	APawn* getPlayer_Implementation() const override;

	virtual ~ULostConnectionUI() = default;
};
