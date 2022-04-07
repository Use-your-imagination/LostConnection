// Copyright (c) 2022 Arkadiy Zakharov

#pragma once

#include "CoreMinimal.h"

#include "Widgets/Notifications/SProgressBar.h"

class PATCHNOTES_API HTMLGenerator
{
private:
	HTMLGenerator() = default;

	~HTMLGenerator() = default;

private:
	FString html;

private:
	void addPageInformation(const FString& projectName, const FString& version, const TSharedPtr<FJsonObject>& settings);

	void addProjectNameAndVersion(const FString& projectName, const FString& version, const TSharedPtr<FJsonObject>& settings);

	void addCategory(const FString& category);

	void addItem(const FString& item, const TArray<FString>& notes);

	void addCategoryEnd();

	void addFooterInformation(const FString& information = "");

	const FString& getHTML() const;

private:
	static FString generatePatchLink(const FString& configurationName);

	static FString generateEmptyPatchLink();

	static FString getLineTerminators(int32 count);

	static FString makeTableRows(const TArray<FString>& data, int32 index, int32 columns);

public:
	static void generatePatchNotesHTML(const FString& fullOutPath, const FString& pathToConfigurationFile, const FString& pathToSettingsFile, TSharedPtr<SProgressBar>& progressBar);

	static void generatePatchNotesHTML(const FString& fullOutPath, const FString& pathToConfigurationFile, const TSharedPtr<FJsonObject>& settings, TSharedPtr<SProgressBar>& progressBar);

	static void generateIndexHTML(const FString& outPath, const FString& configurationName, const TSharedPtr<FJsonObject>& settings);

	static void updateIndexHTML(const FString& outPath, const FString& configurationName);
};
