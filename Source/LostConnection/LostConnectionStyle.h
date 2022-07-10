// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Styling/SlateStyle.h"

class FLostConnectionStyle
{
private:
	static TSharedRef<FSlateStyleSet> create();

public:
	static const FSlateStyleSet& get();

	static FName getStyleSetName();
};
