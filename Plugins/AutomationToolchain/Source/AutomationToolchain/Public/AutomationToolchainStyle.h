// Copyright (c) 2022 Semyon Gritsenko

#pragma once

#include "CoreMinimal.h"

#include "Styling/SlateStyle.h"

class FAutomationToolchainStyle
{
private:
	static TSharedPtr<FSlateStyleSet> styleInstance;

private:
	static TSharedRef<FSlateStyleSet> create();

public:
	static void initialize();

	static void shutdown();

	static void reloadTextures();

	static const ISlateStyle& get();

	static FName getStyleSetName();
};