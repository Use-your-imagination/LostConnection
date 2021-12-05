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
	TMap<FName, TSharedPtr<FStreamableHandle>> handles;

private:
	template<typename T>
	TSharedPtr<FStreamableHandle>& loadAsset(FStreamableDelegate delegate = FStreamableDelegate());

	template<typename T>
	TSharedPtr<FStreamableHandle>& getHandle();

	template<typename T>
	void latentLoadAsset(UObject* worldContext, const FLatentActionInfo& info, FStreamableDelegate delegate = FStreamableDelegate());

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

	UFUNCTION(Category = AssetLoading, BlueprintCallable)
	void unloadDronesPreview();

	UFUNCTION(Category = AssetLoading, BlueprintCallable)
	TMap<FName, float> getLoadingState() const;

	const UClass* operator [] (typeOfDamage damageType) const;

	UFUNCTION(Category = AssetLoading, BlueprintCallable)
	TSubclassOf<class UBaseWeapon> getWeaponClass(TSubclassOf<class UBaseWeapon> weapon) const;

	UFUNCTION(Category = AssetLoading, BlueprintCallable)
	const TArray<TSubclassOf<class UBaseWeapon>>& getWeapons() const;

	TArray<const FDronePreview*> getDronesPreview() const;

	~ULostConnectionAssetManager() = default;
};

template<typename T>
TSharedPtr<FStreamableHandle>& ULostConnectionAssetManager::loadAsset(FStreamableDelegate delegate)
{
	return handles.Add(T::StaticClass()->GetFName(), LoadPrimaryAsset(T::getPrimaryAssetId(), {}, delegate));
}

template<typename T>
TSharedPtr<FStreamableHandle>& ULostConnectionAssetManager::getHandle()
{
	return handles[T::StaticClass()->GetFName()];
}

template<typename T>
void ULostConnectionAssetManager::latentLoadAsset(UObject* worldContext, const FLatentActionInfo& info, FStreamableDelegate delegate)
{
	TSharedPtr<FStreamableHandle>& asset = this->loadAsset<T>();

	this->startLatent(worldContext, info, asset);
}
