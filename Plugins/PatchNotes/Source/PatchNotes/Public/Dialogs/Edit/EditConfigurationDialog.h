// Copyright (c) 2022 Arkadiy Zakharov

#pragma once

#include "CoreMinimal.h"

#include "Dialogs/BaseDialog.h"

class PATCHNOTES_API EditConfigurationDialog : public BaseDialog
{
private:
	FString currentVersion;
	FString pathToConfiguration;
	FString configurationName;
	const FString* pathToConfigurations;
	TFunction<void()> updateConfigurations;

	TSharedPtr<SEditableTextBox> newVersion;

private:
	void collectData(const class FPatchNotesModule& module, Validation& validation) override;

	TSharedPtr<SCustomDialog> createDialog() override;

public:
	EditConfigurationDialog(const class FPatchNotesModule& module);

	~EditConfigurationDialog() = default;
};
