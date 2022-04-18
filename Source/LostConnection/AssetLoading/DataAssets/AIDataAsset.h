// Copyright (c) 2022 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"

#include "AIDataAsset.generated.h"

UCLASS(BlueprintType)
class LOSTCONNECTION_API UAIDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Category = "Constants|Blackboard", EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	FName selfActorKey;

	UPROPERTY(Category = "Constants|Blackboard", EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	FName targetKey;

	UPROPERTY(Category = "Constants|Blackboard", EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	FName movementPointKey;

public:
	static FPrimaryAssetId getPrimaryAssetId();

public:
	UAIDataAsset() = default;

	const FName& getTargetKey() const;

	FPrimaryAssetId GetPrimaryAssetId() const override;

	virtual ~UAIDataAsset() = default;
};
