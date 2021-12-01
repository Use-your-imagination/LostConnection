// Copyright (c) 2021 Use-your-imagination

#include "LostConnectionAssetManager.h"

#include "NiagaraFunctionLibrary.h"

#include "Statuses/BaseStatus.h"

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

			const auto& values = Cast<UStatusesDataAsset>(statuses->GetLoadedAsset())->getAilments();

		});

	statuses = LoadPrimaryAsset(UStatusesDataAsset::getPrimaryAssetId(), {}, delegate);
}
