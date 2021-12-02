// Copyright (c) 2021 Use-your-imagination

#include "LostConnectionAssetManager.h"

#include "NiagaraFunctionLibrary.h"

#include "Statuses/BaseStatus.h"

ULostConnectionAssetManager& ULostConnectionAssetManager::get()
{
	return StaticCast<ULostConnectionAssetManager&>(UAssetManager::Get());
}

void ULostConnectionAssetManager::loadStatuses()
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
}

void ULostConnectionAssetManager::loadWeapons()
{
	FStreamableDelegate delegate;

	delegate.BindLambda([this]()
		{
			if (!statuses.IsValid())
			{
				GEngine->AddOnScreenDebugMessage(-1, 120.0f, FColor::Purple, L"Can't load weapons");

				return;
			}

			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, L"Weapons loaded");
		});

	weapons = LoadPrimaryAsset(UWeaponsDataAsset::getPrimaryAssetId(), {}, delegate);
}

void ULostConnectionAssetManager::loadDronesPreview()
{
	FStreamableDelegate delegate;

	delegate.BindLambda([this]()
		{
			if (!statuses.IsValid())
			{
				GEngine->AddOnScreenDebugMessage(-1, 120.0f, FColor::Purple, L"Can't load drones preview");

				return;
			}

			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, L"Drones preview loaded");
		});

	dronesPreview = LoadPrimaryAsset(UDronesPreviewDataAsset::getPrimaryAssetId(), {}, delegate);
}

const UClass* ULostConnectionAssetManager::operator [] (typeOfDamage damageType) const
{
	return (*GetPrimaryAssetObject<UStatusesDataAsset>(UStatusesDataAsset::getPrimaryAssetId()))[damageType];
}
