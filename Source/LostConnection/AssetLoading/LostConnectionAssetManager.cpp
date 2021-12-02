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

			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, L"Loaded");
		});

	statuses = LoadPrimaryAsset(UStatusesDataAsset::getPrimaryAssetId(), {}, delegate);
}

const UClass* ULostConnectionAssetManager::operator [] (typeOfDamage damageType) const
{
	return (*GetPrimaryAssetObject<UStatusesDataAsset>(UStatusesDataAsset::getPrimaryAssetId()))[damageType];
}
