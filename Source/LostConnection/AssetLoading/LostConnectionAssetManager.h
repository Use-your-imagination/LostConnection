// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Engine/AssetManager.h"

#include "Utility/AssetsCollection.h"

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

private:
	static void startLatent(UObject* worldContext, const FLatentActionInfo& info, const TSharedPtr<FStreamableHandle>& handle);

public:
	static ULostConnectionAssetManager& get();

public:
	ULostConnectionAssetManager() = default;

	UFUNCTION(Category = AssetLoading, BlueprintCallable, Meta = (Latent, LatentInfo = info, HidePin = worldContext, DefaultToSelf = worldContext))
	void loadStatuses(UObject* worldContext, FLatentActionInfo info);

	UFUNCTION(Category = AssetLoading, BlueprintCallable, Meta = (Latent, LatentInfo = info, HidePin = worldContext, DefaultToSelf = worldContext))
	void loadWeapons(UObject* worldContext, FLatentActionInfo info);

	UFUNCTION(Category = AssetLoading, BlueprintCallable, Meta = (Latent, LatentInfo = info, HidePin = worldContext, DefaultToSelf = worldContext))
	void loadDronesPreview(UObject* worldContext, FLatentActionInfo info);

	const UClass* operator [] (typeOfDamage damageType) const;

	UFUNCTION(BlueprintCallable)
	TSubclassOf<class UBaseWeapon> getWeaponClass(TSubclassOf<class UBaseWeapon> weapon) const;

	TArray<const FDronePreview*> getDronesPreview() const;

	~ULostConnectionAssetManager() = default;
};
