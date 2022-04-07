// Copyright (c) 2022 Arkadiy Zakharov

#pragma once

#include "CoreMinimal.h"

#include "Widgets/Views/SListView.h"
#include "Brushes/SlateImageBrush.h"

class PATCHNOTES_API ChangeOrderListViewComponent
{
private:
	TArray<TSharedPtr<FString>> values;
	TSharedPtr<SListView<TSharedPtr<FString>>> listView;
	TUniquePtr<FSlateImageBrush> downImage;
	TUniquePtr<FSlateImageBrush> upImage;

public:
	ChangeOrderListViewComponent();
	
	TArray<TSharedPtr<FString>>& getValues();

	TSharedPtr<SListView<TSharedPtr<FString>>>& getListView();

	~ChangeOrderListViewComponent() = default;
};
