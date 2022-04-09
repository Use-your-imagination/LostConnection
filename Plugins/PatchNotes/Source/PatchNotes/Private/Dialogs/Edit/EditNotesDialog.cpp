// Copyright (c) 2022 Arkadiy Zakharov

#include "Dialogs/Edit/EditNotesDialog.h"

#include "PatchNotes.h"
#include "Utility.h"

void EditNotesDialog::initElements()
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

	elements->setOnSelectionChanged([this](TSharedPtr<FString> item)
		{
			this->updateNotes(item);
		});

	elements->getComboBox()->RefreshOptions();

	if (values.Num())
	{
		elements->selectElement(0);
	}
}

void EditNotesDialog::updateNotes(const TSharedPtr<FString>& item)
{
	if (!item.IsValid())
	{
		notes->SetText(FText::GetEmpty());

		return;
	}

	TSharedPtr<FJsonObject> configurationData = Utility::getJSON(pathToConfiguration);
	TArray<FString> notesData;
	FString data;

	configurationData->GetObjectField(*category)->GetObjectField(*item)->TryGetStringArrayField(TEXT("notes"), notesData);

	for (const auto& note : notesData)
	{
		data.Append(note).Append(LINE_TERMINATOR);
	}

	notes->SetText(FText::FromString(data));
}

void EditNotesDialog::collectData(const FPatchNotesModule& module, Validation& validation)
{
	validation.checkConfigurationExist();

	validation.checkConfiguration();

	validation.checkCategory();

	VALIDATION_CHECK();

	configuration = &module.getConfigurations()->getCurrentSelectionString();
	category = &module.getCategories()->getCurrentSelectionString();
	pathToConfiguration = module.getPathToConfigurations() / *configuration + TEXT(".json");
	notes = SNew(SMultiLineEditableText).HintText(FText::FromName(TEXT("Notes")));

	this->initElements();
}

TSharedPtr<SCustomDialog> EditNotesDialog::createDialog()
{
	return SNew(SCustomDialog)
		.Title(FText::FromName(TEXT("Edit notes")))
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
			+ SVerticalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Fill).VAlign(EVerticalAlignment::VAlign_Fill).AutoHeight()
			[
				SNew(SBorder).BorderBackgroundColor(FLinearColor::White)
				[
					notes.ToSharedRef()
				]
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
							TArray<FString> notesData;
							notes->GetText().ToString().ParseIntoArray(notesData, LINE_TERMINATOR);

							TSharedPtr<FJsonObject> configurationData = Utility::getJSON(pathToConfiguration);
							TArray<TSharedPtr<FJsonValue>> newNotes;

							newNotes.Reserve(notesData.Num());

							for (const auto& note : notesData)
							{
								newNotes.Add(MakeShareable(new FJsonValueString(note)));
							}

							configurationData->GetObjectField(*category)->GetObjectField(elements->getCurrentSelectionString())->SetArrayField(TEXT("notes"), newNotes);

							Utility::modifyConfigurationFile(pathToConfiguration, configurationData);
						}
					)
				)
			}
		);
}

EditNotesDialog::EditNotesDialog(const FPatchNotesModule& module) :
	BaseDialog(module)
{

}
