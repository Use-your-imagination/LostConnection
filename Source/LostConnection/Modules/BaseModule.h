// Copyright (c) 2022 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

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

	virtual const FText& getItemName() const final override;

	virtual const FText& getItemDescription() const final override;

	virtual const UTexture2D* getCellIcon() const final override;

	virtual const FColor& getBorderColor() const final override;

	virtual ~UBaseModule() = default;
};
