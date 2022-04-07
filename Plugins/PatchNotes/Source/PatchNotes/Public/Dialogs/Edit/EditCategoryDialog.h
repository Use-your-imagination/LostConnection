// Copyright (c) 2022 Arkadiy Zakharov

#pragma once

#include "CoreMinimal.h"

#include "Dialogs/BaseDialog.h"

class PATCHNOTES_API EditCategoryDialog : public BaseDialog
{
private:
	const FString* configuration;
	FString pathToConfiguration;
	const FString* category;
	TFunction<void()> updateCategories;

	TSharedPtr<SEditableTextBox> newCategory;

private:
	void collectData(const class FPatchNotesModule& module, Validation& validation) override;

	TSharedPtr<SCustomDialog> createDialog() override;

public:
	EditCategoryDialog(const class FPatchNotesModule& module);

	~EditCategoryDialog() = default;
};
