// Copyright (c) 2022 Use Your Imagination

#include "LostConnectionStyle.h"

#include "Styling/SlateStyleRegistry.h"

TSharedRef<FSlateStyleSet> FLostConnectionStyle::create()
{
	FSlateStyleSet& coreStyleSet = const_cast<FSlateStyleSet&>(static_cast<const FSlateStyleSet&>(FCoreStyle::Get()));
	TSharedRef<FSlateStyleSet> style = MakeShareable(new FSlateStyleSet(FLostConnectionStyle::getStyleSetName()));
	FSlateImageBrush* randomziedSelectorIcon = nullptr;

	style->SetContentRoot(FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir() / "Assets" / "Editor"));

	randomziedSelectorIcon = new FSlateImageBrush(style->RootToContentDir(*(FString("AI") / "RandomizedSelector"), TEXT(".png")), FVector2D(24.0));

	style->Set
	(
		"LostConnectionStyle.Editor.AI.RandomizedSelector.Icon",
		randomziedSelectorIcon
	);

	coreStyleSet.Set
	(
		"LostConnectionStyle.Editor.AI.RandomizedSelector.Icon",
		randomziedSelectorIcon
	);

	return style;
}

const FSlateStyleSet& FLostConnectionStyle::get()
{
	static TSharedPtr<FSlateStyleSet> instance;

	if (!instance.IsValid())
	{
		instance = FLostConnectionStyle::create();

		FSlateStyleRegistry::RegisterSlateStyle(*instance);
	}

	return *instance;
}

FName FLostConnectionStyle::getStyleSetName()
{
	return FName("LostConnectionStyle");
}
