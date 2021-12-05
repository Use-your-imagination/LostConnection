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
	void unloadAsset();

	template<typename T>
	TSharedPtr<FStreamableHandle>& getHandle();

	template<typename T>
	bool latentLoadAsset(UObject* worldContext, const FLatentActionInfo& info, FStreamableDelegate delegate = FStreamableDelegate());

	template<typename T>
	bool isAssetAlreadyLoaded();

private:
	static void startLatent(UObject* worldContext, const FLatentActionInfo& info, const TSharedPtr<FStreamableHandle>& handle);

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

public:
	UFUNCTION(Category = AssetLoading, BlueprintCallable, Meta = (Latent, LatentInfo = info, HidePin = worldContext, DefaultToSelf = worldContext))
	UPARAM(DisplayName = IsAlreadyLoaded) bool loadRuinedCityAct(UObject* worldContext, FLatentActionInfo info);

	UFUNCTION(Category = AssetLoading, BlueprintCallable)
	void unloadRuinedCityAct();
};

template<typename T>
TSharedPtr<FStreamableHandle>& ULostConnectionAssetManager::loadAsset(FStreamableDelegate delegate)
{
	return handles.Add(T::StaticClass()->GetFName(), LoadPrimaryAsset(T::getPrimaryAssetId(), {}, delegate));
}

template<typename T>
void ULostConnectionAssetManager::unloadAsset()
{
	if (!this->isAssetAlreadyLoaded<T>())
	{
		return;
	}

	UnloadPrimaryAsset(T::getPrimaryAssetId());

	this->getHandle<T>().Reset();

	handles.Remove(T::StaticClass()->GetFName());
}

template<typename T>
TSharedPtr<FStreamableHandle>& ULostConnectionAssetManager::getHandle()
{
	return handles[T::StaticClass()->GetFName()];
}

template<typename T>
bool ULostConnectionAssetManager::latentLoadAsset(UObject* worldContext, const FLatentActionInfo& info, FStreamableDelegate delegate)
{
	if (this->isAssetAlreadyLoaded<T>())
	{
		return true;
	}

	TSharedPtr<FStreamableHandle>& asset = this->loadAsset<T>();

	this->startLatent(worldContext, info, asset);

	return false;
}

template<typename T>
bool ULostConnectionAssetManager::isAssetAlreadyLoaded()
{
	return handles.Contains(T::StaticClass()->GetFName());
}
