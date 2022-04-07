// Copyright (c) 2022 Arkadiy Zakharov

#include "Dialogs/ChangeCategoriesOrderDialog.h"

#include "PatchNotes.h"
#include "Utility.h"

void ChangeCategoriesOrderDialog::initCategories()
{
	categories = MakeUnique<ChangeOrderListViewComponent>();

	TSharedPtr<FJsonObject> configurationData = Utility::getJSON(pathToConfiguration);
	TArray<TSharedPtr<FString>>& values = categories->getValues();

	for (const auto& value : configurationData->Values)
	{
		const TSharedPtr<FJsonObject>* category = nullptr;

		if (value.Value->TryGetObject(category))
		{
			values.Add(MakeShareable(new FString(value.Key)));
		}
	}
}

void ChangeCategoriesOrderDialog::collectData(const FPatchNotesModule& module, Validation& validation)
{
	validation.checkConfigurationExist();

	validation.checkConfiguration();

	VALIDATION_CHECK();

	configuration = &module.getConfigurations()->getCurrentSelectionString();
	pathToConfiguration = module.getPathToConfigurations() / (*configuration) + TEXT(".json");
	updateCategories = [&module]() { const_cast<FPatchNotesModule&>(module).updateCategories(); };

	this->initCategories();
}

TSharedPtr<SCustomDialog> ChangeCategoriesOrderDialog::createDialog()
{
	return SNew(SCustomDialog)
		.Title(FText::FromName("Change categories order"))
		.DialogContent
		(
			SNew(SVerticalBox)
			+ SVerticalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Center).VAlign(EVerticalAlignment::VAlign_Top).AutoHeight()
			[
				SNew(STextBlock).Text(FText::FromString(FString::Printf(TEXT("Change categories order in %s"), **configuration)))
			]
			+ SVerticalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Center).VAlign(EVerticalAlignment::VAlign_Top).AutoHeight()
			[
				categories->getListView().ToSharedRef()
			]
		)
		.Buttons
		(
			{
				SCustomDialog::FButton
				(
					FText::FromName(TEXT("Change")),
					FSimpleDelegate::CreateLambda
					(
						[this]()
						{
							TArray<TSharedPtr<FString>>& values = categories->getValues();
							TSharedPtr<FJsonObject> configurationData = Utility::getJSON(pathToConfiguration);
							TSharedPtr<FJsonObject> updatedData = MakeShareable(new FJsonObject());

							updatedData->SetStringField(TEXT("projectName"), configurationData->GetStringField(TEXT("projectName")));

							updatedData->SetStringField(TEXT("projectVersion"), configurationData->GetStringField(TEXT("projectVersion")));

							for (const TSharedPtr<FString>& value : values)
							{
								TSharedPtr<FJsonValue> category;

								configurationData->Values.RemoveAndCopyValue(*value, category);

								updatedData->SetObjectField(*value, category->AsObject());
							}

							Utility::modifyConfigurationFile(pathToConfiguration, updatedData);

							updateCategories();
						}
					)
				)
			}
		);
}

ChangeCategoriesOrderDialog::ChangeCategoriesOrderDialog(const FPatchNotesModule& module) :
	BaseDialog(module)
{

}
