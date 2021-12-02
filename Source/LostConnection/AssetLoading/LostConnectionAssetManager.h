// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Engine/AssetManager.h"

#include "AssetsCollection.h"

#include "LostConnectionAssetManager.generated.h"

UCLASS(BlueprintType)
class LOSTCONNECTION_API ULostConnectionAssetManager : public UAssetManager
{
	GENERATED_BODY()

private:
	AssetsCollection& assets = AssetsCollection::get();

private:
	TSharedPtr<FStreamableHandle> statuses;
	TSharedPtr<FStreamableHandle> weapons;
	TSharedPtr<FStreamableHandle> dronesPreview;

public:
	static ULostConnectionAssetManager& get();

public:
	ULostConnectionAssetManager() = default;

	UFUNCTION(BlueprintCallable)
	void loadStatuses();

	UFUNCTION(BlueprintCallable)
	void loadWeapons();

	UFUNCTION(BlueprintCallable)
	void loadDronesPreview();

	const UClass* operator [] (typeOfDamage damageType) const;

	UFUNCTION(BlueprintCallable)
	const UClass* getWeaponClass(const TSubclassOf<class UBaseWeapon>& weapon) const;

	TArray<const FDronePreview*> getDronesPreview() const;

	~ULostConnectionAssetManager() = default;
};
