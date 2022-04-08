// Copyright (c) 2022 Arkadiy Zakharov

#pragma once

#include "CoreMinimal.h"

#include "Dom/JsonObject.h"

class PATCHNOTES_API Utility
{
private:
	Utility() = default;

	~Utility() = default;

public:
	static void modifyConfigurationFile(const FString& pathToConfigurationFile, const TSharedPtr<FJsonObject>& object);

	static void updateConfigurationFileWithNotes(const FString& pathToConfigurationFile, const FString& category, const FString& element, const TArray<FString>& notes);

	static void generateStyles(const FString& outPath);

	static TSharedPtr<FJsonObject> getJSON(const FString& pathToJSON);

	static FString getConfigurationName(const FString& configurationWithVersion);

	static void runOnGameThread(const TFunction<void()>& function);

	static FString getGeneratedFilesPath(const TSharedPtr<FJsonObject>& settings);
};
