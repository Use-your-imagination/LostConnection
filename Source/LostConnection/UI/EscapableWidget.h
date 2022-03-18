// Copyright (c) 2022 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "EscapableWidget.generated.h"

UCLASS()
class LOSTCONNECTION_API UEscapableWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual ~UEscapableWidget() = default;
};
