// Copyright (c) 2022 Arkadiy Zakharov

#pragma once

#include "CoreMinimal.h"

#include "Dialogs/BaseDialog.h"
#include "Components/ComboBoxComponent.h"

class PATCHNOTES_API DeleteNotesDialog : public BaseDialog
{
private:
	const FString* configuration;
	const FString* category;
	FString pathToConfiguration;

	TUniquePtr<ComboBoxComponent> elements;

private:
	void initElements();

	void collectData(const class FPatchNotesModule& module, Validation& validation) override;

	TSharedPtr<SCustomDialog> createDialog() override;

public:
	DeleteNotesDialog(const class FPatchNotesModule& module);

	~DeleteNotesDialog() = default;
};
