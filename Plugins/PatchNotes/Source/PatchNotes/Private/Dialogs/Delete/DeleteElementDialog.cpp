// Copyright (c) 2022 Arkadiy Zakharov

#include "Dialogs/Delete/DeleteElementDialog.h"

#include "PatchNotes.h"
#include "Utility.h"

void DeleteElementDialog::initElements()
{
	elements = MakeUnique<ComboBoxComponent>();

	TSharedPtr<FJsonObject> configurationData = Utility::getJSON(pathToConfiguration);
	TArray<TSharedPtr<FString>>& values = elements->getValues();
	const TSharedPtr<FJsonObject>& categoryData = configurationData->GetObjectField(*category);

	for (const auto& elementData : categoryData->Values)
	{
		const TSharedPtr<FJsonObject>* elementObject = nullptr;

		if (elementData.Value->TryGetObject(elementObject))
		{
			values.Add(MakeShareable(new FString(elementData.Key)));
		}
	}

	elements->getComboBox()->RefreshOptions();

	if (values.Num())
	{
		elements->selectElement(0);
	}
}

void DeleteElementDialog::collectData(const FPatchNotesModule& module, Validation& validation)
{
	validation.checkConfigurationExist();

	validation.checkConfiguration();

	validation.checkCategory();

	VALIDATION_CHECK();

	configuration = &module.getConfigurations()->getCurrentSelectionString();
	category = &module.getCategories()->getCurrentSelectionString();
	pathToConfiguration = module.getPathToConfigurations() / (*configuration) + TEXT(".json");

	this->initElements();
}

TSharedPtr<SCustomDialog> DeleteElementDialog::createDialog()
{
	return SNew(SCustomDialog)
		.Title(FText::FromName(TEXT("Delete element")))
		.DialogContent
		(
			SNew(SVerticalBox)
			+ SVerticalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Center).VAlign(EVerticalAlignment::VAlign_Center).AutoHeight()
			[
				SNew(STextBlock).Text(FText::FromString(*configuration)).MinDesiredWidth(214.0f)
			]
			+ SVerticalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Center).VAlign(EVerticalAlignment::VAlign_Center).AutoHeight()
			[
				SNew(STextBlock).Text(FText::FromString(*category)).MinDesiredWidth(214.0f)
			]
			+ SVerticalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Center).VAlign(EVerticalAlignment::VAlign_Center).AutoHeight()
			[
				elements->getComboBox()
			]
		)
		.Buttons
		(
			{
				SCustomDialog::FButton
				(
					FText::FromName(TEXT("Delete")),
					FSimpleDelegate::CreateLambda
					(
						[this]()
						{
							const FString& element = elements->getCurrentSelectionString();

							if (element.IsEmpty())
							{
								FMessageDialog::Open(EAppMsgType::Type::Ok, FText::FromName(TEXT("Element can't be empty")));

								return;
							}

							TSharedPtr<FJsonObject> configurationData = Utility::getJSON(pathToConfiguration);

							configurationData->GetObjectField(*category)->Values.Remove(element);

							Utility::modifyConfigurationFile(pathToConfiguration, configurationData);
						}
					)
				)
			}
		);
}

DeleteElementDialog::DeleteElementDialog(const FPatchNotesModule& module) :
	BaseDialog(module)
{

}
