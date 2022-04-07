// Copyright (c) 2022 Arkadiy Zakharov

#pragma once

#include "CoreMinimal.h"

#include "Dialogs/BaseDialog.h"
#include "Components/ComboBoxComponent.h"

class PATCHNOTES_API DeleteElementDialog : public BaseDialog
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
	DeleteElementDialog(const class FPatchNotesModule& module);

	~DeleteElementDialog() = default;
};
