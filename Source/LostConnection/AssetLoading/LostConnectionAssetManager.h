// Copyright (c) 2021 Use Your Imagination

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
	TMap<FName, TSharedPtr<FStreamableHandle>> handles;
	FPrimaryAssetId currentActId;

private:
	static void startLatent(UObject* worldContext, const FLatentActionInfo& info, const TSharedPtr<FStreamableHandle>& handle);

private:
	template<typename AssetT>
	const AssetT& getDataAsset() const;

	TSharedPtr<FStreamableHandle>& loadAsset(const TSubclassOf<UPrimaryDataAsset>& dataAsset, FStreamableDelegate delegate = FStreamableDelegate());

	bool latentLoadAsset(const TSubclassOf<UPrimaryDataAsset>& dataAsset, UObject* worldContext, const FLatentActionInfo& info, FStreamableDelegate delegate = FStreamableDelegate());

	bool latentLoadAct(const TSubclassOf<UBaseActDataAsset>& dataAsset, UObject* worldContext, const FLatentActionInfo& info, FStreamableDelegate delegate = FStreamableDelegate());

	void unloadAsset(const TSubclassOf<UPrimaryDataAsset>& dataAsset);

	bool isAssetAlreadyLoaded(const TSubclassOf<UPrimaryDataAsset>& dataAsset) const;

	TSharedPtr<FStreamableHandle>& getHandle(const TSubclassOf<UPrimaryDataAsset>& dataAsset);

public:
	static ULostConnectionAssetManager& get();

public:
	ULostConnectionAssetManager() = default;

	UFUNCTION(Category = AssetLoading, BlueprintCallable, Meta = (Latent, LatentInfo = info, HidePin = worldContext, DefaultToSelf = worldContext))
	UPARAM(DisplayName = IsAlreadyLoaded) bool loadStatuses(UObject* worldContext, FLatentActionInfo info);

	UFUNCTION(Category = AssetLoading, BlueprintCallable, Meta = (Latent, LatentInfo = info, HidePin = worldContext, DefaultToSelf = worldContext))
	UPARAM(DisplayName = IsAlreadyLoaded) bool loadWeapons(UObject* worldContext, FLatentActionInfo info);

	UFUNCTION(Category = AssetLoading, BlueprintCallable, Meta = (Latent, LatentInfo = info, HidePin = worldContext, DefaultToSelf = worldContext))
	UPARAM(DisplayName = IsAlreadyLoaded) bool loadDronesPreview(UObject* worldContext, FLatentActionInfo info);

	UFUNCTION(Category = AssetLoading, BlueprintCallable, Meta = (Latent, LatentInfo = info, HidePin = worldContext, DefaultToSelf = worldContext))
	UPARAM(DisplayName = IsAlreadyLoaded) bool loadUI(UObject* worldContext, FLatentActionInfo info);

	UFUNCTION(Category = AssetLoading, BlueprintCallable, Meta = (Latent, LatentInfo = info, HidePin = worldContext, DefaultToSelf = worldContext))
	UPARAM(DisplayName = IsAlreadyLoaded) bool loadDefaults(UObject* worldContext, FLatentActionInfo info);

	UFUNCTION(Category = AssetLoading, BlueprintCallable, Meta = (Latent, LatentInfo = info, HidePin = worldContext, DefaultToSelf = worldContext))
	UPARAM(DisplayName = IsAlreadyLoaded) bool loadLoot(UObject* worldContext, FLatentActionInfo info);

	UFUNCTION(Category = AssetLoading, BlueprintCallable, Meta = (Latent, LatentInfo = info, HidePin = worldContext, DefaultToSelf = worldContext))
	UPARAM(DisplayName = IsAlreadyLoaded) bool loadAI(UObject* worldContext, FLatentActionInfo info);

	UFUNCTION(Category = AssetLoading, BlueprintCallable, Meta = (Latent, LatentInfo = info, HidePin = worldContext, DefaultToSelf = worldContext))
	UPARAM(DisplayName = IsAlreadyLoaded) bool loadDrone(TSubclassOf<UBaseDroneDataAsset> droneAsset, UObject* worldContext, FLatentActionInfo info);

	UFUNCTION(Category = AssetLoading, BlueprintCallable, Meta = (Latent, LatentInfo = info, HidePin = worldContext, DefaultToSelf = worldContext))
	UPARAM(DisplayName = IsAlreadyLoaded) bool loadAct(TSubclassOf<UBaseActDataAsset> actAsset, UObject* worldContext, FLatentActionInfo info);

	UFUNCTION(Category = AssetLoading, BlueprintCallable)
	void unloadDronesPreview();

	UFUNCTION(Category = AssetLoading, BlueprintCallable)
	void unloadDrone(TSubclassOf<UBaseDroneDataAsset> droneAsset);

	UFUNCTION(Category = AssetLoading, BlueprintCallable)
	void unloadAct(TSubclassOf<UBaseActDataAsset> actAsset);

	UFUNCTION(Category = AssetLoading, BlueprintCallable)
	TMap<FName, float> getLoadingState() const;

	UFUNCTION(Category = AssetLoading, BlueprintCallable)
	float getCurrentPercentLoading() const;

	UFUNCTION(Category = AssetLoading, BlueprintCallable)
	bool isAssetsLoadingInProgress() const;

	UFUNCTION(Category = AssetLoading, BlueprintCallable)
	bool isAssetsLoadingEnd() const;

	const TSubclassOf<class UBaseStatus>& operator [] (ETypeOfDamage damageType) const;

	UFUNCTION(Category = AssetLoading, BlueprintCallable)
	TSubclassOf<class UBaseWeapon> getWeaponClass(TSubclassOf<class UBaseWeapon> weapon) const;

	UFUNCTION(Category = AssetLoading, BlueprintCallable)
	const TArray<TSubclassOf<class UBaseWeapon>>& getWeapons() const;

	const UStatusesDataAsset& getStatuses() const;

	const UBaseActDataAsset& getCurrentAct() const;

	const UUIDataAsset& getUI() const;

	const UDefaultsDataAsset& getDefaults() const;

	const ULootDataAsset& getLoot() const;

	const UAIDataAsset& getAI() const;

	UFUNCTION(Category = "AssetLoading|Statuses", BlueprintCallable)
	const UStatusesDataAsset* getStatusesDataAsset() const;

	UFUNCTION(Category = "AssetLoading|Acts", BlueprintCallable)
	const UBaseActDataAsset* getCurrentActDataAsset() const;

	UFUNCTION(Category = "AssetLoading|UI", BlueprintCallable)
	const UUIDataAsset* getUIDataAsset() const;

	UFUNCTION(Category = "AssetLoading|Defaults", BlueprintCallable)
	const UDefaultsDataAsset* getDefaultsDataAsset() const;

	UFUNCTION(Category = "AssetLoading|Loot", BlueprintCallable)
	const ULootDataAsset* getLootDataAsset() const;

	UFUNCTION(Category = "AssetLoading|AI", BlueprintCallable)
	const UAIDataAsset* getAIDataAsset() const;

	UFUNCTION(Category = "AssetLoading|DronesPreview", BlueprintCallable)
	const UDronesPreviewDataAsset* getDronesPreview() const;

	TArray<const UBaseDroneDataAsset*> getDrones() const;

	FPrimaryAssetId GetPrimaryAssetIdForObject(UObject* object) const override;

	~ULostConnectionAssetManager() = default;
};

inline ULostConnectionAssetManager& ULostConnectionAssetManager::get()
{
	return StaticCast<ULostConnectionAssetManager&>(UAssetManager::Get());
}
