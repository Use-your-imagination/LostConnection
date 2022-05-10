// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "HealthBarWidget.generated.h"

UCLASS(Blueprintable)
class LOSTCONNECTION_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(Category = Image, BlueprintNativeEvent)
	UImage* getImage();

	UFUNCTION(Category = Text, BlueprintNativeEvent)
	UTextBlock* getText();

	virtual ~UHealthBarWidget() = default;
};
