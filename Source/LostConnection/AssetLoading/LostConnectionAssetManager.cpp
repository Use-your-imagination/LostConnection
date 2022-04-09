// Copyright (c) 2021 Use-your-imagination

#include "LostConnectionAssetManager.h"

#include "NiagaraFunctionLibrary.h"
#include "Engine/LevelStreamingDynamic.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Utility/LoadAssetsDelayAction.h"
#include "Statuses/BaseStatus.h"
#include "Weapons/BaseWeapon.h"
#include "Utility/Utility.h"

void ULostConnectionAssetManager::startLatent(UObject* worldContext, const FLatentActionInfo& info, const TSharedPtr<FStreamableHandle>& handle)
{
	FLatentActionManager& manager = GEngine->GetWorldFromContextObject(worldContext, EGetWorldErrorMode::Assert)->GetLatentActionManager();

	if (!manager.FindExistingAction<FLoadAssetsDelayAction>(info.CallbackTarget, info.UUID))
	{
		manager.AddNewAction(info.CallbackTarget, info.UUID, new FLoadAssetsDelayAction(handle, info));
	}
}

TSharedPtr<FStreamableHandle>& ULostConnectionAssetManager::loadAsset(const TSubclassOf<UPrimaryDataAsset>& dataAsset, FStreamableDelegate delegate)
{
	return handles.Add(dataAsset.Get()->GetFName(), LoadPrimaryAsset(assets[dataAsset], {}, delegate));
}

bool ULostConnectionAssetManager::latentLoadAsset(const TSubclassOf<UPrimaryDataAsset>& dataAsset, UObject* worldContext, const FLatentActionInfo& info, FStreamableDelegate delegate)
{
	if (this->isAssetAlreadyLoaded(dataAsset))
	{
		return true;
	}

	TSharedPtr<FStreamableHandle>& asset = this->loadAsset(dataAsset);

	this->startLatent(worldContext, info, asset);

	return false;
}

bool ULostConnectionAssetManager::latentLoadAct(const TSubclassOf<UBaseActDataAsset>& dataAsset, UObject* worldContext, const FLatentActionInfo& info, FStreamableDelegate delegate)
{
	if (this->isAssetAlreadyLoaded(dataAsset))
	{
		return true;
	}

	TSharedPtr<FStreamableHandle>& asset = this->loadAsset(dataAsset);

	currentActId = assets[dataAsset];

	this->startLatent(worldContext, info, asset);

	return false;
}

void ULostConnectionAssetManager::unloadAsset(const TSubclassOf<UPrimaryDataAsset>& dataAsset)
{
	if (!this->isAssetAlreadyLoaded(dataAsset))
	{
		return;
	}

	UnloadPrimaryAsset(assets[dataAsset]);

	this->getHandle(dataAsset).Reset();

	handles.Remove(dataAsset.Get()->GetFName());
}

bool ULostConnectionAssetManager::isAssetAlreadyLoaded(const TSubclassOf<UPrimaryDataAsset>& dataAsset) const
{
	return handles.Contains(dataAsset.Get()->GetFName());
}

TSharedPtr<FStreamableHandle>& ULostConnectionAssetManager::getHandle(const TSubclassOf<UPrimaryDataAsset>& dataAsset)
{
	return handles[dataAsset.Get()->GetFName()];
}

bool ULostConnectionAssetManager::loadStatuses(UObject* worldContext, FLatentActionInfo info)
{
	return this->latentLoadAsset(UStatusesDataAsset::StaticClass(), worldContext, info);
}

bool ULostConnectionAssetManager::loadWeapons(UObject* worldContext, FLatentActionInfo info)
{
	return this->latentLoadAsset(UWeaponsDataAsset::StaticClass(), worldContext, info);
}

bool ULostConnectionAssetManager::loadDronesPreview(UObject* worldContext, FLatentActionInfo info)
{
	return this->latentLoadAsset(UDronesPreviewDataAsset::StaticClass(), worldContext, info);
}

bool ULostConnectionAssetManager::loadUI(UObject* worldContext, FLatentActionInfo info)
{
	return this->latentLoadAsset(UUIDataAsset::StaticClass(), worldContext, info);
}

bool ULostConnectionAssetManager::loadDefaults(UObject* worldContext, FLatentActionInfo info)
{
	return this->latentLoadAsset(UDefaultsDataAsset::StaticClass(), worldContext, info);
}

bool ULostConnectionAssetManager::loadLoot(UObject* worldContext, FLatentActionInfo info)
{
	return this->latentLoadAsset(ULootDataAsset::StaticClass(), worldContext, info);
}

bool ULostConnectionAssetManager::loadDrone(TSubclassOf<UBaseDroneDataAsset> droneAsset, UObject* worldContext, FLatentActionInfo info)
{
	return this->latentLoadAsset(droneAsset, worldContext, info);
}

bool ULostConnectionAssetManager::loadAct(TSubclassOf<UBaseActDataAsset> actAsset, UObject* worldContext, FLatentActionInfo info)
{
	return this->latentLoadAct(actAsset, worldContext, info);
}

void ULostConnectionAssetManager::unloadDronesPreview()
{
	this->unloadAsset(UDronesPreviewDataAsset::StaticClass());
}

void ULostConnectionAssetManager::unloadDrone(TSubclassOf<UBaseDroneDataAsset> droneAsset)
{
	this->unloadAsset(droneAsset);
}

void ULostConnectionAssetManager::unloadAct(TSubclassOf<UBaseActDataAsset> actAsset)
{
	if (!this->isAssetAlreadyLoaded(actAsset))
	{
		return;
	}

	UnloadPrimaryAsset(assets[actAsset]);

	this->getHandle(actAsset).Reset();

	handles.Remove(actAsset.Get()->GetFName());

	currentActId = FPrimaryAssetId();
}

TMap<FName, float> ULostConnectionAssetManager::getLoadingState() const
{
	TMap<FName, float> result;

	result.Reserve(handles.Num());

	for (const auto& i : handles)
	{
		result.Add(i.Key, i.Value->GetProgress());
	}

	return result;
}

float ULostConnectionAssetManager::getCurrentPercentLoading() const
{
	float allAssets = handles.Num();
	float current = 0.0f;

	for (const auto& i : handles)
	{
		current += i.Value->GetProgress();
	}

	return Utility::toPercent(current / allAssets);
}

bool ULostConnectionAssetManager::isAssetsLoadingEnd() const
{
	return Algo::AllOf(handles, [](const auto& data) { return data.Value->HasLoadCompleted(); });
}

const TSubclassOf<UBaseStatus>& ULostConnectionAssetManager::operator [] (ETypeOfDamage damageType) const
{
	UStatusesDataAsset& asset = *GetPrimaryAssetObject<UStatusesDataAsset>(UStatusesDataAsset::getPrimaryAssetId());

	return asset[damageType];
}

TSubclassOf<UBaseWeapon> ULostConnectionAssetManager::getWeaponClass(TSubclassOf<UBaseWeapon> weapon) const
{
	UWeaponsDataAsset& asset = *GetPrimaryAssetObject<UWeaponsDataAsset>(UWeaponsDataAsset::getPrimaryAssetId());

	return asset[weapon];
}

const TArray<TSubclassOf<UBaseWeapon>>& ULostConnectionAssetManager::getWeapons() const
{
	UWeaponsDataAsset& asset = *GetPrimaryAssetObject<UWeaponsDataAsset>(UWeaponsDataAsset::getPrimaryAssetId());

	return asset.getWeapons();
}

const UStatusesDataAsset& ULostConnectionAssetManager::getStatuses() const
{
	return *GetPrimaryAssetObject<UStatusesDataAsset>(assets[UStatusesDataAsset::StaticClass()]);
}

const UBaseActDataAsset& ULostConnectionAssetManager::getCurrentAct() const
{
	return *GetPrimaryAssetObject<UBaseActDataAsset>(currentActId);
}

const UUIDataAsset& ULostConnectionAssetManager::getUI() const
{
	return *GetPrimaryAssetObject<UUIDataAsset>(assets[UUIDataAsset::StaticClass()]);
}

const UDefaultsDataAsset& ULostConnectionAssetManager::getDefaults() const
{
	return *GetPrimaryAssetObject<UDefaultsDataAsset>(assets[UDefaultsDataAsset::StaticClass()]);
}

const ULootDataAsset& ULostConnectionAssetManager::getLoot() const
{
	return *GetPrimaryAssetObject<ULootDataAsset>(assets[ULootDataAsset::StaticClass()]);
}

const ULootDataAsset* ULostConnectionAssetManager::getLootDataAsset() const
{
	return &this->getLoot();
}

const UDronesPreviewDataAsset* ULostConnectionAssetManager::getDronesPreview() const
{
	return GetPrimaryAssetObject<UDronesPreviewDataAsset>(assets[UDronesPreviewDataAsset::StaticClass()]);
}

TArray<const UBaseDroneDataAsset*> ULostConnectionAssetManager::getDrones() const
{
	TArray<const UBaseDroneDataAsset*> drones;

	for (const auto& handle : handles)
	{
		if (handle.Value.IsValid() && handle.Value->HasLoadCompleted())
		{
			UBaseDroneDataAsset* asset = Cast<UBaseDroneDataAsset>(handle.Value->GetLoadedAsset());

			if (asset)
			{
				drones.Add(asset);
			}
		}
	}

	return drones;
}

FPrimaryAssetId ULostConnectionAssetManager::GetPrimaryAssetIdForObject(UObject* object) const
{
	FPrimaryAssetId result = Super::GetPrimaryAssetIdForPath(object);

	if (!result.IsValid())
	{
		TSubclassOf<UPrimaryDataAsset> tem(Cast<UClass>(object));

		if (tem)
		{
			result = assets[tem];
		}
	}

	return result;
}
