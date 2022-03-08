// Copyright (c) 2022 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Engine/Texture2D.h"

#include "Network/NetworkObject.h"
#include "Interfaces/Inventory/Inventoriable.h"

#include "BaseModule.generated.h"

UCLASS(BlueprintType, Blueprintable)
class LOSTCONNECTION_API UBaseModule :
	public UNetworkObject,
	public IInventoriable
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = Description, EditDefaultsOnly, BlueprintReadOnly)
	FText moduleName;

	UPROPERTY(Category = Description, EditDefaultsOnly, BlueprintReadOnly)
	FText moduleDescription;

	UPROPERTY(Category = UI, EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* moduleIconTexture;

public:
	UBaseModule() = default;

	const FText& getItemName() const override;

	const FText& getItemDescription() const override;

	virtual ~UBaseModule() = default;
};
