// Copyright (c) 2022 Arkadiy Zakharov

#include "Dialogs/Delete/DeleteCategoryDialog.h"

#include "PatchNotes.h"
#include "Utility.h"

void DeleteCategoryDialog::collectData(const FPatchNotesModule& module, Validation& validation)
{
	validation.checkConfigurationExist();

	validation.checkConfiguration();

	validation.checkCategory();

	VALIDATION_CHECK();

	configuration = &module.getConfigurations()->getCurrentSelectionString();
	category = &module.getCategories()->getCurrentSelectionString();
	pathToConfiguration = module.getPathToConfigurations() / (*configuration) + TEXT(".json");
	updateCategories = [&module]() { const_cast<FPatchNotesModule&>(module).updateCategories(); };
}

TSharedPtr<SCustomDialog> DeleteCategoryDialog::createDialog()
{
	return SNew(SCustomDialog)
		.Title(FText::FromName(TEXT("Delete category")))
		.DialogContent
		(
			SNew(STextBlock).Text(FText::FromString(FString::Printf(TEXT("Delete %s from %s?"), **category, **configuration)))
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
							TSharedPtr<FJsonObject> configurationData = Utility::getJSON(pathToConfiguration);

							configurationData->Values.Remove(*category);

							Utility::modifyConfigurationFile(pathToConfiguration, configurationData);

							updateCategories();
						}
					)
				),
				SCustomDialog::FButton(FText::FromName(TEXT("No")))
			}
		);
}

DeleteCategoryDialog::DeleteCategoryDialog(const FPatchNotesModule& module) :
	BaseDialog(module)
{

}
