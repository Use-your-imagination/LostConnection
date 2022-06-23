// Copyright (c) 2022 Use Your Imagination

#include "VideoSettingsWidget.h"

void UVideoSettingsWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	videoSettingName->SetText(settingName);

	for (const FText& option : options)
	{
		videoSettingValue->AddOption(option.ToString());
	}

	videoSettingName->SetToolTipText(settingNameToolTip);

	videoSettingValue->SetToolTipText(optionsToolTip);
}

TObjectPtr<UComboBoxString> UVideoSettingsWidget::getVideoSettingValue() const
{
	return videoSettingValue;
}
