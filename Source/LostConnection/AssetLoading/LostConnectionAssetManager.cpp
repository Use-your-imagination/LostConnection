// Copyright (c) 2021 Use Your Imagination

#include "LostConnectionAssetManager.h"

#include "NiagaraFunctionLibrary.h"
#include "Engine/LevelStreamingDynamic.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Utility/LoadAssetsDelayAction.h"
#include "Statuses/BaseStatus.h"
#include "Weapons/BaseWeapon.h"
#include "Utility/Utility.h"

template<typename AssetT>
const AssetT& ULostConnectionAssetManager::getDataAsset() const
{
	return *GetPrimaryAssetObject<AssetT>(assets[AssetT::StaticClass()]);
}

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
	return handles.Add(dataAsset->GetFName(), LoadPrimaryAsset(assets[dataAsset], {}, delegate));
}

bool ULostConnectionAssetManager::latentLoadAsset(const TSubclassOf<UPrimaryDataAsset>& dataAsset, UObject* worldContext, const FLatentActionInfo& info, FStreamableDelegate delegate)
{
	if (this->isAssetAlreadyLoaded(dataAsset))
	{
		return true;
	}

	TSharedPtr<FStreamableHandle>& asset = this->loadAsset(dataAsset);

	ULostConnectionAssetManager::startLatent(worldContext, info, asset);

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

	ULostConnectionAssetManager::startLatent(worldContext, info, asset);

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

bool ULostConnectionAssetManager::loadAI(UObject* worldContext, FLatentActionInfo info)
{
	return this->latentLoadAsset(UAIDataAsset::StaticClass(), worldContext, info);
}

bool ULostConnectionAssetManager::loadDrone(TSubclassOf<UBaseDroneDataAsset> droneAsset, UObject* worldContext, FLatentActionInfo info)
{
	return this->latentLoadAsset(droneAsset, worldContext, info);
}

bool ULostConnectionAssetManager::loadAct(TSubclassOf<UBaseActDataAsset> actAsset, UObject* worldContext, FLatentActionInfo info)
{
	return this->latentLoadAct(actAsset, worldContext, info);
}

void ULostConnectionAssetManager::syncLoadAsset(TSubclassOf<UPrimaryDataAsset> dataAsset)
{
	const TSharedPtr<FStreamableHandle>* it = handles.Find(dataAsset.Get()->GetFName());

	if (it)
	{
		(*it)->WaitUntilComplete();
	}
	else
	{
		handles.Add(dataAsset->GetFName(), LoadPrimaryAsset(assets[dataAsset]))->WaitUntilComplete();
	}
}

void ULostConnectionAssetManager::syncLoadActAsset(TSubclassOf<UBaseActDataAsset> dataAsset)
{
	const TSharedPtr<FStreamableHandle>* it = handles.Find(dataAsset.Get()->GetFName());

	if (it)
	{
		(*it)->WaitUntilComplete();
	}
	else
	{
		currentActId = assets[dataAsset];

		handles.Add(dataAsset->GetFName(), LoadPrimaryAsset(assets[dataAsset]))->WaitUntilComplete();
	}
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

bool ULostConnectionAssetManager::isAssetsLoadingInProgress() const
{
	return Algo::AnyOf(handles, [](const auto& data) { return data.Value.IsValid() && !data.Value->HasLoadCompleted(); });
}

bool ULostConnectionAssetManager::isAssetsLoadingEnd() const
{
	return Algo::AllOf(handles, [](const auto& data) { return data.Value.IsValid() && data.Value->HasLoadCompleted(); });
}

bool ULostConnectionAssetManager::isAssetLoaded(TSubclassOf<UPrimaryDataAsset> dataAsset) const
{
	const TSharedPtr<FStreamableHandle>* it = handles.Find(dataAsset.Get()->GetFName());

	return it && (*it)->HasLoadCompleted();
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
	return GetPrimaryAssetObject<UWeaponsDataAsset>(UWeaponsDataAsset::getPrimaryAssetId())->getWeapons();
}

const UStatusesDataAsset& ULostConnectionAssetManager::getStatuses() const
{
	return this->getDataAsset<UStatusesDataAsset>();
}

const UBaseActDataAsset& ULostConnectionAssetManager::getCurrentAct() const
{
	return *GetPrimaryAssetObject<UBaseActDataAsset>(currentActId);
}

const UUIDataAsset& ULostConnectionAssetManager::getUI() const
{
	return this->getDataAsset<UUIDataAsset>();
}

const UDefaultsDataAsset& ULostConnectionAssetManager::getDefaults() const
{
	return this->getDataAsset<UDefaultsDataAsset>();
}

const ULootDataAsset& ULostConnectionAssetManager::getLoot() const
{
	return this->getDataAsset<ULootDataAsset>();
}

const UAIDataAsset& ULostConnectionAssetManager::getAI() const
{
	return this->getDataAsset<UAIDataAsset>();
}

const UStatusesDataAsset* ULostConnectionAssetManager::getStatusesDataAsset() const
{
	return &this->getStatuses();
}

const UBaseActDataAsset* ULostConnectionAssetManager::getCurrentActDataAsset() const
{
	return &this->getCurrentAct();
}

const UUIDataAsset* ULostConnectionAssetManager::getUIDataAsset() const
{
	return &this->getUI();
}

const UDefaultsDataAsset* ULostConnectionAssetManager::getDefaultsDataAsset() const
{
	return &this->getDefaults();
}

const ULootDataAsset* ULostConnectionAssetManager::getLootDataAsset() const
{
	return &this->getLoot();
}

const UAIDataAsset* ULostConnectionAssetManager::getAIDataAsset() const
{
	return &this->getAI();
}

const UDronesPreviewDataAsset* ULostConnectionAssetManager::getDronesPreview() const
{
	return &this->getDataAsset<UDronesPreviewDataAsset>();
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
