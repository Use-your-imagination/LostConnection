// Copyright (c) 2022 Arkadiy Zakharov

#pragma once

#include "CoreMinimal.h"

#include "Dialogs/BaseDialog.h"

class PATCHNOTES_API DeleteCategoryDialog : public BaseDialog
{
private:
	const FString* configuration;
	const FString* category;
	FString pathToConfiguration;
	TFunction<void()> updateCategories;

private:
	void collectData(const class FPatchNotesModule& module, Validation& validation) override;

	TSharedPtr<SCustomDialog> createDialog() override;

public:
	DeleteCategoryDialog(const class FPatchNotesModule& module);

	~DeleteCategoryDialog() = default;
};
