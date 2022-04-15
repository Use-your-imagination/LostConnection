// Copyright (c) 2022 Arkadiy Zakharov

#pragma once

#include "CoreMinimal.h"

#include "BaseDialog.h"

class PATCHNOTES_API CreateConfigurationDialog : public BaseDialog
{
private:
	FString projectName;
	const FString* pathToConfigurations;
	const FString* pathToTemplate;
	TFunction<void()> updateConfigurations;

	TSharedPtr<SEditableTextBox> version;
	TSharedPtr<FJsonObject> settings;

private:
	void collectData(const class FPatchNotesModule& module, Validation& validation) override;

	TSharedPtr<SCustomDialog> createDialog() override;

public:
	CreateConfigurationDialog(const class FPatchNotesModule& module);

	~CreateConfigurationDialog() = default;
};
