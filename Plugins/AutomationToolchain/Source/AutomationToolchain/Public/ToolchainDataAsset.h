// Copyright (c) 2022 Semyon Gritsenko

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"

#include "ToolchainAction.h"

#include "ToolchainDataAsset.generated.h"

/**
 * Contains list of actions to execute
 */
UCLASS(BlueprintType, Blueprintable)
class AUTOMATIONTOOLCHAIN_API UToolchainDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Category = Toolchain, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TArray<TSubclassOf<UToolchainAction>> actions;

public:
	UToolchainDataAsset() = default;

	const TArray<TSubclassOf<UToolchainAction>>& getActions() const;

	virtual ~UToolchainDataAsset() = default;
};
