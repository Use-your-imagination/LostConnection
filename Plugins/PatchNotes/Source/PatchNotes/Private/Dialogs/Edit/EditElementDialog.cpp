// Copyright (c) 2022 Arkadiy Zakharov


#include "Dialogs/Edit/EditElementDialog.h"

#include "PatchNotes.h"
#include "Utility.h"

void EditElementDialog::initElements()
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

void EditElementDialog::collectData(const FPatchNotesModule& module, Validation& validation)
{
	validation.checkConfigurationExist();

	validation.checkConfiguration();

	validation.checkCategory();

	VALIDATION_CHECK();

	const FString& configuration = module.getConfigurations()->getCurrentSelectionString();

	this->configuration = &configuration;
	this->category = &module.getCategories()->getCurrentSelectionString();;
	pathToConfiguration = module.getPathToConfigurations() / configuration + TEXT(".json");

	this->initElements();
}

TSharedPtr<SCustomDialog> EditElementDialog::createDialog()
{
	return SNew(SCustomDialog)
		.Title(FText::FromName(TEXT("Edit element")))
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
			+ SVerticalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Center).VAlign(EVerticalAlignment::VAlign_Center).AutoHeight()
			[
				SAssignNew(newElement, SEditableTextBox).HintText(FText::FromName(TEXT("New element name"))).MinDesiredWidth(214.0f)
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
							const FString& newElementName = newElement->GetText().ToString();

							if (newElementName.IsEmpty())
							{
								FMessageDialog::Open(EAppMsgType::Type::Ok, FText::FromName(TEXT("New element name can't be empty")));

								return;
							}

							TSharedPtr<FJsonObject> configurationData = Utility::getJSON(pathToConfiguration);
							TSharedPtr<FJsonObject>& categoryData = const_cast<TSharedPtr<FJsonObject>&>(configurationData->GetObjectField(*category));
							TSharedPtr<FJsonValue> elementData;

							categoryData->Values.RemoveAndCopyValue(elements->getCurrentSelectionString(), elementData);

							categoryData->SetObjectField(newElementName, elementData->AsObject());

							Utility::modifyConfigurationFile(pathToConfiguration, configurationData);
						}
					)
				)
			}
		);
}

EditElementDialog::EditElementDialog(const FPatchNotesModule& module) :
	BaseDialog(module)
{

}
