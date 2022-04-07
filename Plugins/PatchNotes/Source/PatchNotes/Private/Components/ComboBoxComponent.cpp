// Copyright (c) 2022 Arkadiy Zakharov

#include "Components/ComboBoxComponent.h"

ComboBoxComponent::ComboBoxComponent(const TFunction<void()>& onOpening) :
	onSelectionChanged([](TSharedPtr<FString>) {})
{
	comboBox = SNew(SComboBox<TSharedPtr<FString>>)
		.OptionsSource(&this->values)
		.OnGenerateWidget_Lambda([](TSharedPtr<FString> value) { return SNew(STextBlock).Text(FText::FromString(*value)).MinDesiredWidth(200.0f); })
		.OnComboBoxOpening_Lambda(onOpening)
		.OnSelectionChanged_Lambda
		(
			[this](TSharedPtr<FString> item, ESelectInfo::Type info)
			{
				if (!item.IsValid())
				{
					return;
				}

				currentSelection->SetText(FText::FromString(*item));

				onSelectionChanged(item);
			}
		)
		[
			SAssignNew(currentSelection, STextBlock).MinDesiredWidth(200.0f)
		];
}

void ComboBoxComponent::selectElement(int32 index)
{
	comboBox->SetSelectedItem(values[index]);
}

void ComboBoxComponent::setOnSelectionChanged(const TFunction<void(TSharedPtr<FString>)>& onSelectionChanged)
{
	this->onSelectionChanged = onSelectionChanged;
}

TSharedRef<SComboBox<TSharedPtr<FString>>> ComboBoxComponent::getComboBox()
{
	return comboBox.ToSharedRef();
}

TArray<TSharedPtr<FString>>& ComboBoxComponent::getValues()
{
	return values;
}

const FString& ComboBoxComponent::getCurrentSelectionString() const
{
	return currentSelection->GetText().ToString();
}
