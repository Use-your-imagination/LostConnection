// Copyright (c) 2021 Use-your-imagination

#include "LostConnectionAssetManager.h"

#include "NiagaraFunctionLibrary.h"
#include "Engine/LevelStreamingDynamic.h"

#include "Utility/LoadAssetsDelayAction.h"
#include "Statuses/BaseStatus.h"
#include "Weapons/BaseWeapon.h"

void ULostConnectionAssetManager::startLatent(UObject* worldContext, const FLatentActionInfo& info, const TSharedPtr<FStreamableHandle>& handle)
{
	UWorld* world = GEngine->GetWorldFromContextObject(worldContext, EGetWorldErrorMode::ReturnNull);

	if (world)
	{
		FLatentActionManager& manager = world->GetLatentActionManager();

		if (!manager.FindExistingAction<FLoadAssetsDelayAction>(info.CallbackTarget, info.UUID))
		{
			manager.AddNewAction(info.CallbackTarget, info.UUID, new FLoadAssetsDelayAction(handle, info));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, L"Can't get world");
	}
}

bool ULostConnectionAssetManager::loadStatuses(UObject* worldContext, FLatentActionInfo info)
{
	return this->latentLoadAsset<UStatusesDataAsset>(worldContext, info);
}

bool ULostConnectionAssetManager::loadWeapons(UObject* worldContext, FLatentActionInfo info)
{
	return this->latentLoadAsset<UWeaponsDataAsset>(worldContext, info);
}

bool ULostConnectionAssetManager::loadDronesPreview(UObject* worldContext, FLatentActionInfo info)
{
	return this->latentLoadAsset<UDronesPreviewDataAsset>(worldContext, info);
}

void ULostConnectionAssetManager::unloadDronesPreview()
{
	this->unloadAsset<UDronesPreviewDataAsset>();
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

	return (current / allAssets) * 100.0f;
}

const UClass* ULostConnectionAssetManager::operator [] (typeOfDamage damageType) const
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

TArray<const FDronePreview*> ULostConnectionAssetManager::getDronesPreview() const
{
	UDronesPreviewDataAsset& asset = *GetPrimaryAssetObject<UDronesPreviewDataAsset>(UDronesPreviewDataAsset::getPrimaryAssetId());

	return asset.getDronesPreview();
}

bool ULostConnectionAssetManager::loadRuinedCityAct(UObject* worldContext, FLatentActionInfo info)
{
	return this->latentLoadAct<URuinedCityActDataAsset>(worldContext, info);
}

void ULostConnectionAssetManager::unloadRuinedCityAct()
{
	this->unloadAct<URuinedCityActDataAsset>();
}
