// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "LostConnectionUI.generated.h"

#pragma warning(disable: 4458)

UCLASS(BlueprintType, Blueprintable)
class LOSTCONNECTION_API ULostConnectionUI : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(Category = Player, BlueprintReadOnly)
	class ABaseDrone* player;

public:
	ULostConnectionUI(const FObjectInitializer& objectInitializer);

	void init(class ABaseDrone* player);

	UFUNCTION(Category = Initialization, BlueprintNativeEvent)
	void UIConstruction();

	virtual ~ULostConnectionUI() = default;
};
