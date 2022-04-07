// Copyright (c) 2022 Arkadiy Zakharov

#pragma once

#include "CoreMinimal.h"

#include "Widgets/Input/SComboBox.h"
#include "Misc/DateTime.h"

#pragma warning(disable: 4458)

class PATCHNOTES_API ComboBoxComponent
{
private:
	TSharedPtr<SComboBox<TSharedPtr<FString>>> comboBox;
	TArray<TSharedPtr<FString>> values;
	TSharedPtr<STextBlock> currentSelection;
	TFunction<void(TSharedPtr<FString>)> onSelectionChanged;

public:
	ComboBoxComponent(const TFunction<void()>& onOpening = []() {});

	void selectElement(int32 index);

	void setOnSelectionChanged(const TFunction<void(TSharedPtr<FString>)>& onSelectionChanged);

	TSharedRef<SComboBox<TSharedPtr<FString>>> getComboBox();

	TArray<TSharedPtr<FString>>& getValues();

	const FString& getCurrentSelectionString() const;

	~ComboBoxComponent() = default;
};
