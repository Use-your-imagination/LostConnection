// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"

#include "DefaultsDataAsset.generated.h"

UCLASS(BlueprintType)
class LOSTCONNECTION_API UDefaultsDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = Placeholders, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ADeathPlaceholder> deathPlaceholder;

public:
	static FPrimaryAssetId getPrimaryAssetId();

public:
	UDefaultsDataAsset() = default;

	const TSubclassOf<class ADeathPlaceholder>& getDeathPlaceholder() const;

	FPrimaryAssetId GetPrimaryAssetId() const override;

	virtual ~UDefaultsDataAsset() = default;
};
