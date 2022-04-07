// Copyright (c) 2022 Arkadiy Zakharov

#pragma once

#include "CoreMinimal.h"

class PATCHNOTES_API Constants
{
private:
	Constants() = default;

	~Constants() = default;

private:
	static FString styles;

	static FString defaultFavicon;

	static FString defaultBackgroundImage;

public:
	static const FString stylesFileName;

public:
	static void initBackgroundColors(const TArray<float>& rgbaColor);

	static void initBackgroundImage(const FString& backgroundImage);

	static void initDefaults();

	static const FString& getStyles();
	
	static const FString& getDefaultFavicon();

	static const FString& getDefaultBackgroundImage();
};
