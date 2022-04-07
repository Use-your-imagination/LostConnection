// Copyright (c) 2022 Arkadiy Zakharov

#pragma once

#include "CoreMinimal.h"

#include "Styling/SlateStyle.h"

class FPatchNotesStyle
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
