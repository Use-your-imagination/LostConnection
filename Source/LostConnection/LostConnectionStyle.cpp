// Copyright (c) 2022 Use Your Imagination

#include "LostConnectionStyle.h"

#include "Styling/SlateStyleRegistry.h"

#include "Utility/Utility.h"

TSharedRef<FSlateStyleSet> FLostConnectionStyle::create()
{
	TSharedRef<FSlateStyleSet> style = MakeShareable(new FSlateStyleSet(FLostConnectionStyle::getStyleSetName()));
	FSlateImageBrush* imageBrush = nullptr;

	style->SetContentRoot(FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir() / "Assets" / "Editor"));

	imageBrush = new FSlateImageBrush(style->RootToContentDir(*(FString("AI") / "RandomizedSelector"), TEXT(".png")), FVector2D(24.0));

	style->Set
	(
		"LostConnectionStyle.Editor.AI.RandomizedSelector.Icon",
		imageBrush
	);

	const_cast<FSlateStyleSet&>(static_cast<const FSlateStyleSet&>(FCoreStyle::Get())).Set
	(
		"LostConnectionStyle.Editor.AI.RandomizedSelector.Icon",
		imageBrush
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
