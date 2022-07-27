// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Network/NetworkObject.h"
#include "Interfaces/Inventory/Inventoriable.h"
#include "Utility/Enums.h"

#include "BaseModule.generated.h"

#pragma warning(disable: 4458)

UCLASS(Abstract, BlueprintType, Blueprintable)
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
	TObjectPtr<UTexture2D> moduleIconTexture;

	UPROPERTY(Category = Stats, BlueprintReadOnly, Replicated)
	EModuleQuality quality;

protected:
	float getMultiplier() const;

protected:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual const FText& getItemDescription() const final override;

public:
	UBaseModule() = default;

	virtual bool applyCondition(TObjectPtr<AActor> caller) const;

	void setQuality(EModuleQuality quality);

	EModuleQuality getQuality() const;

	virtual const FText& getItemName() const final override;

	virtual const UTexture2D* getCellIcon() const final override;

	virtual const FLinearColor& getBorderColor() const final override;

	virtual ~UBaseModule() = default;
};
