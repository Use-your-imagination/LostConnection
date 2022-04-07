// Copyright (c) 2022 Arkadiy Zakharov

#pragma once

#include "CoreMinimal.h"

#include "BaseDialog.h"
#include "Components/ChangeOrderListViewComponent.h"

class PATCHNOTES_API ChangeCategoriesOrderDialog : public BaseDialog
{
private:
	const FString* configuration;
	FString pathToConfiguration;
	TFunction<void()> updateCategories;

	TUniquePtr<ChangeOrderListViewComponent> categories;

private:
	void initCategories();

	void collectData(const class FPatchNotesModule& module, Validation& validation) override;

	TSharedPtr<SCustomDialog> createDialog() override;

public:
	ChangeCategoriesOrderDialog(const class FPatchNotesModule& module);

	~ChangeCategoriesOrderDialog() = default;
};
