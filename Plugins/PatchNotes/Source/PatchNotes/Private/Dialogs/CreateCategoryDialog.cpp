// Copyright (c) 2022 Arkadiy Zakharov

#include "Dialogs/CreateCategoryDialog.h"

#include "PatchNotes.h"
#include "Utility.h"

void CreateCategoryDialog::collectData(const FPatchNotesModule& module, Validation& validation)
{
	validation.checkConfigurationExist();

	validation.checkConfiguration();

	VALIDATION_CHECK();

	configuration = &module.getConfigurations()->getCurrentSelectionString();
	pathToConfiguration = module.getPathToConfigurations() / *configuration + TEXT(".json");
	settings = Utility::getJSON(module.getPathToSettingsFile());
	updateCategories = [&module]() { const_cast<FPatchNotesModule&>(module).updateCategories(); };
}

TSharedPtr<SCustomDialog> CreateCategoryDialog::createDialog()
{
	return SNew(SCustomDialog)
		.Title(FText::FromName(TEXT("Add category")))
		.DialogContent
		(
			SNew(SVerticalBox) 
			+ SVerticalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Center).VAlign(EVerticalAlignment::VAlign_Top).AutoHeight()
			[
				SNew(STextBlock).Text(FText::FromString(*configuration)).MinDesiredWidth(200.0f)
			]
			+ SVerticalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Center).VAlign(EVerticalAlignment::VAlign_Top).AutoHeight()
			[
				SAssignNew(category, SEditableTextBox).HintText(FText::FromName(TEXT("Category"))).MinDesiredWidth(200.0f)
			]
		)
		.Buttons
		(
			{
				SCustomDialog::FButton
				(
					FText::FromName(TEXT("Create")),
					FSimpleDelegate::CreateLambda
					(
						[this]()
						{
							IPlatformFile& platformFile = FPlatformFileManager::Get().GetPlatformFile();
							const FString& categoryName = category->GetText().ToString();

							if (!platformFile.FileExists(*pathToConfiguration))
							{
								FMessageDialog::Open(EAppMsgType::Type::Ok, FText::FromName(TEXT("Configuration doesn't exist")));

								return;
							}

							TSharedPtr<FJsonObject> configurationData = Utility::getJSON(pathToConfiguration);

							if (configurationData->TryGetField(categoryName).IsValid())
							{
								FMessageDialog::Open(EAppMsgType::Type::Ok, FText::FromName(TEXT("Category already exists")));

								return;
							}

							TSharedPtr<FJsonObject> categoryData = MakeShareable(new FJsonObject());

							categoryData->SetStringField(TEXT("type"), TEXT("category"));

							configurationData->SetObjectField(categoryName, categoryData);

							Utility::modifyConfigurationFile(pathToConfiguration, configurationData);

							updateCategories();
						}
					)
				)
			}
		);
}

CreateCategoryDialog::CreateCategoryDialog(const FPatchNotesModule& module) :
	BaseDialog(module)
{

}
