// Copyright (c) 2022 Arkadiy Zakharov

#pragma once

#include "CoreMinimal.h"

#include "Dialogs/BaseDialog.h"

class PATCHNOTES_API DeleteConfigurationDialog : public BaseDialog
{
private:
	const FString* configuration;
	FString pathToConfiguration;
	TFunction<void()> updateConfigurations;

private:
	void collectData(const class FPatchNotesModule& module, Validation& validation) override;

	TSharedPtr<SCustomDialog> createDialog() override;

public:
	DeleteConfigurationDialog(const class FPatchNotesModule& module);

	~DeleteConfigurationDialog() = default;
};
