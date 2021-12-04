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
	FStreamableDelegate delegate;

	delegate.BindLambda([this]()
		{
			if (!statuses.IsValid())
			{
				GEngine->AddOnScreenDebugMessage(-1, 120.0f, FColor::Purple, L"Can't load statuses");

				return;
			}

			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, L"Statuses loaded");
		});

	statuses = LoadPrimaryAsset(UStatusesDataAsset::getPrimaryAssetId(), {}, delegate);

	this->startLatent(worldContext, info, statuses);
}

void ULostConnectionAssetManager::loadWeapons(UObject* worldContext, FLatentActionInfo info)
{
	FStreamableDelegate delegate;

	delegate.BindLambda([this]()
		{
			if (!weapons.IsValid())
			{
				GEngine->AddOnScreenDebugMessage(-1, 120.0f, FColor::Purple, L"Can't load weapons");

				return;
			}

			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, L"Weapons loaded");
		});

	weapons = LoadPrimaryAsset(UWeaponsDataAsset::getPrimaryAssetId(), {}, delegate);

	this->startLatent(worldContext, info, weapons);
}

void ULostConnectionAssetManager::loadDronesPreview(UObject* worldContext, FLatentActionInfo info)
{
	FStreamableDelegate delegate;

	delegate.BindLambda([this]()
		{
			if (!dronesPreview.IsValid())
			{
				GEngine->AddOnScreenDebugMessage(-1, 120.0f, FColor::Purple, L"Can't load drones preview");

				return;
			}

			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, L"Drones preview loaded");
		});

	dronesPreview = LoadPrimaryAsset(UDronesPreviewDataAsset::getPrimaryAssetId(), {}, delegate);

	this->startLatent(worldContext, info, dronesPreview);
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

TArray<const FDronePreview*> ULostConnectionAssetManager::getDronesPreview() const
{
	UDronesPreviewDataAsset& asset = *GetPrimaryAssetObject<UDronesPreviewDataAsset>(UDronesPreviewDataAsset::getPrimaryAssetId());

	return asset.getDronesPreview();
}
