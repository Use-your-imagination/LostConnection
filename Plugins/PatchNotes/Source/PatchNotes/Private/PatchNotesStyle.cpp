// Copyright (c) 2022 Arkadiy Zakharov

#include "PatchNotesStyle.h"

#include "Styling/SlateStyleRegistry.h"
#include "Framework/Application/SlateApplication.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Brushes/SlateImageBrush.h"

TSharedPtr<FSlateStyleSet> FPatchNotesStyle::styleInstance = nullptr;

TSharedRef<FSlateStyleSet> FPatchNotesStyle::create()
{
	TSharedRef<FSlateStyleSet> style = MakeShareable(new FSlateStyleSet(FPatchNotesStyle::getStyleSetName()));

	style->SetContentRoot(IPluginManager::Get().FindPlugin(TEXT("PatchNotes"))->GetBaseDir() / TEXT("Resources"));

	style->Set
	(
		TEXT("PatchNotes.OpenPluginWindow"),
		new FSlateImageBrush(style->RootToContentDir(TEXT("ButtonIcon40"), TEXT(".png")), FVector2D(40.0f, 40.0f))
	);

	style->Set
	(
		TEXT("PatchNotes.TabIcon"),
		new FSlateImageBrush(style->RootToContentDir(TEXT("TabIcon16"), TEXT(".png")), FVector2D(16.0f, 16.0f))
	);

	style->Set
	(
		TEXT("PatchNotes.ArrowDown"),
		new FSlateImageBrush(style->RootToContentDir(TEXT("ArrowDown16"), TEXT(".png")), FVector2D(16.0f, 16.0f))
	);

	style->Set
	(
		TEXT("PatchNotes.ArrowUp"),
		new FSlateImageBrush(style->RootToContentDir(TEXT("ArrowUp16"), TEXT(".png")), FVector2D(16.0f, 16.0f))
	);

	return style;
}

void FPatchNotesStyle::initialize()
{
	if (!styleInstance.IsValid())
	{
		styleInstance = create();

		FSlateStyleRegistry::RegisterSlateStyle(*styleInstance);
	}
}

void FPatchNotesStyle::shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*styleInstance);

	ensure(styleInstance.IsUnique());

	styleInstance.Reset();
}

void FPatchNotesStyle::reloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FPatchNotesStyle::get()
{
	return *styleInstance;
}

FName FPatchNotesStyle::getStyleSetName()
{
	static FName StyleSetName(TEXT("PatchNotesStyle"));

	return StyleSetName;
}
