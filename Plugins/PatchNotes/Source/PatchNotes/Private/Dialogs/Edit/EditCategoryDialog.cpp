// Copyright (c) 2022 Arkadiy Zakharov


#include "Dialogs/Edit/EditCategoryDialog.h"

#include "PatchNotes.h"
#include "Utility.h"

void EditCategoryDialog::collectData(const FPatchNotesModule& module, Validation& validation)
{
	validation.checkConfigurationExist();

	validation.checkConfiguration();

	validation.checkCategory();

	VALIDATION_CHECK();

	configuration = &module.getConfigurations()->getCurrentSelectionString();
	pathToConfiguration = FString::Printf(TEXT("%s.json"), *(module.getPathToConfigurations() / *configuration));
	category = &module.getCategories()->getCurrentSelectionString();
	updateCategories = [&module]() { const_cast<FPatchNotesModule&>(module).updateCategories(); };
}

TSharedPtr<SCustomDialog> EditCategoryDialog::createDialog()
{
	return SNew(SCustomDialog)
		.Title(FText::FromName(TEXT("Edit category")))
		.DialogContent
		(
			SNew(SVerticalBox)
			+ SVerticalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Center).VAlign(EVerticalAlignment::VAlign_Center).AutoHeight()
			[
				SNew(STextBlock).Text(FText::FromString(*configuration)).MinDesiredWidth(200.0f)
			]
			+ SVerticalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Center).VAlign(EVerticalAlignment::VAlign_Center).AutoHeight()
			[
				SNew(STextBlock).Text(FText::FromString(FString::Printf(TEXT("Current category to change: %s"), **category))).MinDesiredWidth(200.0f)
			]
			+ SVerticalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Center).VAlign(EVerticalAlignment::VAlign_Center).AutoHeight()
			[
				SAssignNew(newCategory, SEditableTextBox).HintText(FText::FromName(TEXT("New category name"))).MinDesiredWidth(200.0f)
			]
		)
		.Buttons
		(
			{
				SCustomDialog::FButton
				(
					FText::FromName("Edit"),
					FSimpleDelegate::CreateLambda
					(
						[this]()
						{
							const FString& newCategoryName = newCategory->GetText().ToString();

							if (newCategoryName.IsEmpty())
							{
								FMessageDialog::Open(EAppMsgType::Type::Ok, FText::FromName(TEXT("New category name can't be empty")));

								return;
							}

							TSharedPtr<FJsonObject> configurationData = Utility::getJSON(pathToConfiguration);
							TSharedPtr<FJsonValue> categoryData;

							if (configurationData->HasField(newCategoryName))
							{
								FMessageDialog::Open(EAppMsgType::Type::Ok, FText::FromName(TEXT("Category already exists")));

								return;
							}

							configurationData->Values.RemoveAndCopyValue(*category, categoryData);

							configurationData->SetObjectField(newCategoryName, categoryData->AsObject());

							Utility::modifyConfigurationFile(pathToConfiguration, configurationData);

							updateCategories();
						}
					)
				)
			}
		);
}

EditCategoryDialog::EditCategoryDialog(const FPatchNotesModule& module) :
	BaseDialog(module)
{

}
