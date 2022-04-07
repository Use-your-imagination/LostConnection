// Copyright (c) 2022 Arkadiy Zakharov

#include "Components/ChangeOrderListViewComponent.h"

#include "Interfaces/IPluginManager.h"

ChangeOrderListViewComponent::ChangeOrderListViewComponent()
{
	FString pathToResources = IPluginManager::Get().FindPlugin(TEXT("PatchNotes"))->GetBaseDir() / TEXT("Resources");

	downImage = TUniquePtr<FSlateImageBrush>(new FSlateImageBrush(*(pathToResources / TEXT("ArrowDown16.png")), FVector2D(16.0f, 16.0f)));
	upImage = TUniquePtr<FSlateImageBrush>(new FSlateImageBrush(*(pathToResources / TEXT("ArrowUp16.png")), FVector2D(16.0f, 16.0f)));

	SAssignNew(listView, SListView<TSharedPtr<FString>>)
		.ListItemsSource(&values)
		.OnGenerateRow
		(
			SListView<TSharedPtr<FString>>::FOnGenerateRow::CreateLambda
			(
				[this](TSharedPtr<FString> item, const TSharedRef<STableViewBase>& table) ->TSharedRef<ITableRow>
				{
					if (!item.IsValid())
					{
						return SNew(STableRow<TSharedPtr<FString>>, table)
							[
								SNew(STextBlock).Text(FText::FromName(TEXT("Fail to get category")))
							];
					}

					return SNew(STableRow<TSharedPtr<FString>>, table)
						[
							SNew(SHorizontalBox)
							+ SHorizontalBox::Slot().AutoWidth()
							[
								SNew(STextBlock).Text(FText::FromString(*item)).MinDesiredWidth(200.0f)
							]
							+ SHorizontalBox::Slot().AutoWidth()
							[
								SNew(SButton)
								.ButtonColorAndOpacity(FLinearColor::Transparent)
								.OnClicked_Lambda
								(
									[this, item]()
									{
										int32 index = values.IndexOfByKey(item);

										if (index == values.Num() - 1)
										{
											return FReply::Handled();
										}

										values.Swap(index, index + 1);

										listView->RequestListRefresh();

										return FReply::Handled();
									}
								)
								[
									SNew(SImage).Image(downImage.Get())
								]
							]
							+ SHorizontalBox::Slot().AutoWidth()
							[
								SNew(SButton)
								.ButtonColorAndOpacity(FLinearColor::Transparent)
								.OnClicked_Lambda
								(
									[this, item]()
									{
										int32 index = values.IndexOfByKey(item);

										if (!index)
										{
											return FReply::Handled();
										}

										values.Swap(index, index - 1);

										listView->RequestListRefresh();

										return FReply::Handled();
									}
								)
								[
									SNew(SImage).Image(upImage.Get())
								]
							]
						];
				}
			)
		);
}

TArray<TSharedPtr<FString>>& ChangeOrderListViewComponent::getValues()
{
	return values;
}

TSharedPtr<SListView<TSharedPtr<FString>>>& ChangeOrderListViewComponent::getListView()
{
	return listView;
}
