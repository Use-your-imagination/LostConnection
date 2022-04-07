// Copyright (c) 2022 Arkadiy Zakharov

#pragma once

#include "CoreMinimal.h"

#include "BaseDialog.h"

class PATCHNOTES_API CreateCategoryDialog : public BaseDialog
{
private:
	FString configuration;
	FString pathToConfiguration;
	TSharedPtr<SEditableTextBox> category;
	TSharedPtr<FJsonObject> settings;
	TFunction<void()> updateCategories;

private:
	void collectData(const class FPatchNotesModule& module, Validation& validation) override;

	TSharedPtr<SCustomDialog> createDialog() override;

public:
	CreateCategoryDialog(const class FPatchNotesModule& module);
	
	~CreateCategoryDialog() = default;
};
