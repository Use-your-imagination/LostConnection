// Copyright (c) 2022 Semyon Gritsenko

#include "AutomationToolchainStyle.h"

#include "Styling/SlateStyleRegistry.h"
#include "Framework/Application/SlateApplication.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"

TSharedPtr<FSlateStyleSet> FAutomationToolchainStyle::styleInstance = nullptr;

TSharedRef< FSlateStyleSet > FAutomationToolchainStyle::create()
{
	TSharedRef<FSlateStyleSet> style = MakeShareable(new FSlateStyleSet("AutomationToolchainStyle"));

	style->SetContentRoot(IPluginManager::Get().FindPlugin("AutomationToolchain")->GetBaseDir() / TEXT("Resources"));

	style->Set
	(
		"AutomationToolchain.OpenPluginWindow",
		new FSlateImageBrush(style->RootToContentDir("ButtonIcon40", TEXT(".png")), FVector2D(40.0f, 40.0f))
	);

	style->Set
	(
		"AutomationToolchain.TabIcon",
		new FSlateImageBrush(style->RootToContentDir("TabIcon16", TEXT(".png")), FVector2D(16.0f, 16.0f))
	);

	return style;
}

void FAutomationToolchainStyle::initialize()
{
	if (!styleInstance.IsValid())
	{
		styleInstance = create();

		FSlateStyleRegistry::RegisterSlateStyle(*styleInstance);
	}
}

void FAutomationToolchainStyle::shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*styleInstance);

	ensure(styleInstance.IsUnique());

	styleInstance.Reset();
}

void FAutomationToolchainStyle::reloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FAutomationToolchainStyle::get()
{
	return *styleInstance;
}

FName FAutomationToolchainStyle::getStyleSetName()
{
	static FName styleSetName("AutomationToolchainStyle");

	return styleSetName;
}
