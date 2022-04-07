// Copyright (c) 2022 Arkadiy Zakharov

#pragma once

#include "CoreMinimal.h"

#include "Dialogs/BaseDialog.h"
#include "Components/ComboBoxComponent.h"

class PATCHNOTES_API EditElementDialog : public BaseDialog
{
private:
	const FString* configuration;
	const FString* category;
	FString pathToConfiguration;

	TUniquePtr<ComboBoxComponent> elements;
	TSharedPtr<SEditableTextBox> newElement;

private:
	void initElements();

	void collectData(const class FPatchNotesModule& module, Validation& validation) override;

	TSharedPtr<SCustomDialog> createDialog() override;

public:
	EditElementDialog(const class FPatchNotesModule& module);

	~EditElementDialog() = default;
};
