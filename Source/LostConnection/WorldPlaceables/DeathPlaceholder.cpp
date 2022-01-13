// Copyright (c) 2021 Use-your-imagination

#include "DeathPlaceholder.h"

#include "Kismet/GameplayStatics.h"

#include "AssetLoading/LostConnectionAssetManager.h"
#include "Utility/Utility.h"

void ADeathPlaceholder::BeginPlay()
{
	Super::BeginPlay();

	Utility::executeOnOwningClient(this, [this]()
		{
			Utility::setCurrentUI(ULostConnectionAssetManager::get().getUI().getDefaultDeathUI(), this);
		});
}
