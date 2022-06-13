// Copyright (c) 2022 Use Your Imagination

#include "BaseModule.h"

#include "Utility/Utility.h"

int32 UBaseModule::getMultiplier() const
{
	switch (quality)
	{
	case EModuleQuality::broken:
	case EModuleQuality::bronze:
		return 1;

	case EModuleQuality::silver:
		return 2;

	case EModuleQuality::gold:
		return 4;

	case EModuleQuality::platinum:
		return 8;
	}

	return 0;
}

void UBaseModule::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UBaseModule, quality);
}

const FText& UBaseModule::getItemDescription() const
{
	return moduleDescription;
}

bool UBaseModule::applyCondition(TObjectPtr<AActor> caller) const
{
	return true;
}

void UBaseModule::setQuality(EModuleQuality quality)
{
	this->quality = quality;
}

EModuleQuality UBaseModule::getQuality() const
{
	return quality;
}

const FText& UBaseModule::getItemName() const
{
	return moduleName;
}

const UTexture2D* UBaseModule::getCellIcon() const
{
	return moduleIconTexture;
}

const FLinearColor& UBaseModule::getBorderColor() const
{
	return ULostConnectionAssetManager::get().getDefaults()[quality];
}
