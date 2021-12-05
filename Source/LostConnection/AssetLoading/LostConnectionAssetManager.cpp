// Copyright (c) 2021 Use-your-imagination

#include "LostConnectionAssetManager.h"

#include "NiagaraFunctionLibrary.h"
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

ULostConnectionAssetManager& ULostConnectionAssetManager::get()
{
	return StaticCast<ULostConnectionAssetManager&>(UAssetManager::Get());
}

void ULostConnectionAssetManager::loadStatuses(UObject* worldContext, FLatentActionInfo info)
{
	this->latentLoadAsset<UStatusesDataAsset>(worldContext, info);
}

void ULostConnectionAssetManager::loadWeapons(UObject* worldContext, FLatentActionInfo info)
{
	this->latentLoadAsset<UWeaponsDataAsset>(worldContext, info);
}

void ULostConnectionAssetManager::loadDronesPreview(UObject* worldContext, FLatentActionInfo info)
{
	this->latentLoadAsset<UDronesPreviewDataAsset>(worldContext, info);
}

void ULostConnectionAssetManager::unloadDronesPreview()
{
	UnloadPrimaryAsset(UDronesPreviewDataAsset::getPrimaryAssetId());

	this->getHandle<UDronesPreviewDataAsset>().Reset();

	handles.Remove(UDronesPreviewDataAsset::StaticClass()->GetFName());
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

TArray<const FDronePreview*> ULostConnectionAssetManager::getDronesPreview() const
{
	UDronesPreviewDataAsset& asset = *GetPrimaryAssetObject<UDronesPreviewDataAsset>(UDronesPreviewDataAsset::getPrimaryAssetId());

	return asset.getDronesPreview();
}
