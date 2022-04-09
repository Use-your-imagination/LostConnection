// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"
#include "Animation/AnimMontage.h"
#include "Internationalization/StringTable.h"

#include "DronesPreviewDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FDronePreview
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = Components, EditDefaultsOnly, BlueprintReadOnly)
	USkeletalMesh* mesh;

	UPROPERTY(Category = Animations, EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UAnimInstance> animationBlueprint;

	UPROPERTY(Category = Information, EditDefaultsOnly, BlueprintReadOnly)
	UStringTable* droneInformation;

	FDronePreview();
};

UCLASS(BlueprintType)
class LOSTCONNECTION_API UDronesPreviewDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Category = SN4K3, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	FDronePreview SN4K3PreviewData;

public:
	static FPrimaryAssetId getPrimaryAssetId();

public:
	UDronesPreviewDataAsset() = default;

	TArray<const FDronePreview*> getDronesPreview() const;

	FPrimaryAssetId GetPrimaryAssetId() const override;

	~UDronesPreviewDataAsset() = default;
};
