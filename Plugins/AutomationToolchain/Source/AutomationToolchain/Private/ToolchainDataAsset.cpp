// Copyright (c) 2022 Semyon Gritsenko

#include "ToolchainDataAsset.h"

const TArray<TSubclassOf<UToolchainAction>>& UToolchainDataAsset::getActions() const
{
	return actions;
}
