// Copyright (c) 2022 Use Your Imagination

#include "VideoSettingsWidget.h"

void UVideoSettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	videoSettingName->SetText(settingName);

	for (const FString& option : options)
	{
		videoSettingValue->AddOption(option);
	}
}

TObjectPtr<UComboBoxString> UVideoSettingsWidget::getVideoSettingValue() const
{
	return videoSettingValue;
}
