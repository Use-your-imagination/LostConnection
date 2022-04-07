// Copyright (c) 2022 Arkadiy Zakharov

#pragma once

#include "CoreMinimal.h"

#include "Widgets/Text/SMultiLineEditableText.h"

#include "Dialogs/BaseDialog.h"
#include "Components/ComboBoxComponent.h"

class PATCHNOTES_API EditNotesDialog : public BaseDialog
{
private:
	const FString* configuration;
	const FString* category;
	FString pathToConfiguration;

	TUniquePtr<ComboBoxComponent> elements;
	TSharedPtr<SMultiLineEditableText> notes;

private:
	void initElements();

	void updateNotes(const TSharedPtr<FString>& item);

	void collectData(const class FPatchNotesModule& module, Validation& validation) override;

	TSharedPtr<SCustomDialog> createDialog() override;

public:
	EditNotesDialog(const class FPatchNotesModule& module);

	~EditNotesDialog() = default;
};
