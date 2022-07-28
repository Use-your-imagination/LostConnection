// Copyright (c) 2022 Use Your Imagination

#include "BaseModule.h"

#include "Utility/Utility.h"

float UBaseModule::getMultiplier() const
{
	switch (quality)
	{
	case EModuleQuality::broken:
		return 0.5f;

	case EModuleQuality::bronze:
		return 1.0f;

	case EModuleQuality::silver:
		return 2.0f;

	case EModuleQuality::gold:
		return 4.0f;

	case EModuleQuality::platinum:
		return 8.0f;
	}

	return 0.0f;
}

void UBaseModule::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UBaseModule, quality);

	DOREPLIFETIME(UBaseModule, isModuleEquipped);
}

const FText& UBaseModule::getItemDescription() const
{
	return moduleDescription;
}

bool& UBaseModule::getIsEquipped()
{
	return isModuleEquipped;
}

bool UBaseModule::applyCondition(const TObjectPtr<AActor>& caller) const
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
