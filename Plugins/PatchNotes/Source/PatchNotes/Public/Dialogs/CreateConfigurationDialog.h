// Copyright (c) 2022 Arkadiy Zakharov

#pragma once

#include "CoreMinimal.h"

#include "BaseDialog.h"

class PATCHNOTES_API CreateConfigurationDialog : public BaseDialog
{
private:
	FString configuration;
	const FString* pathToConfigurations;
	const FString* pathToTemplate;

	TSharedPtr<SEditableTextBox> version;
	TSharedPtr<FJsonObject> settings;

private:
	void collectData(const class FPatchNotesModule& module, Validation& validation) override;

	TSharedPtr<SCustomDialog> createDialog() override;

public:
	CreateConfigurationDialog(const class FPatchNotesModule& module);

	~CreateConfigurationDialog() = default;
};
