// Copyright (c) 2022 Arkadiy Zakharov

#include "Dialogs/Delete/DeleteConfigurationDialog.h"

#include "PatchNotes.h"

void DeleteConfigurationDialog::collectData(const FPatchNotesModule& module, Validation& validation)
{
	validation.checkConfiguration();

	VALIDATION_CHECK();

	configuration = &module.getConfigurations()->getCurrentSelectionString();
	pathToConfiguration = module.getPathToConfigurations() / (*configuration) + TEXT(".json");
	updateConfigurations = [&module]() { const_cast<FPatchNotesModule&>(module).updateConfigurations(); };
}

TSharedPtr<SCustomDialog> DeleteConfigurationDialog::createDialog()
{
	return SNew(SCustomDialog)
		.Title(FText::FromName(TEXT("Delete configuration")))
		.DialogContent
		(
			SNew(STextBlock).Text(FText::FromString(FString::Printf(TEXT("Delete %s?"), **configuration)))
		)
		.Buttons
		(
			{
				SCustomDialog::FButton
				(
					FText::FromName(TEXT("Yes")),
					FSimpleDelegate::CreateLambda
					(
						[this]()
						{
							FPlatformFileManager::Get().GetPlatformFile().DeleteFile(*pathToConfiguration);

							updateConfigurations();
						}
					)
				),
				SCustomDialog::FButton(FText::FromName(TEXT("No")))
			}
	);
}

DeleteConfigurationDialog::DeleteConfigurationDialog(const FPatchNotesModule& module) :
	BaseDialog(module)
{
}
