// Copyright (c) 2022 Arkadiy Zakharov

#pragma once

#include "CoreMinimal.h"

#include "BaseSettingsParser.h"

#pragma warning(disable: 4458)

class FilesGenerationSettingsParser : public BaseSettingsParser
{
private:
	enum class generationType
	{
		prefixes,
		postfixes,
		standard
	};

private:
	generationType type;
	TArray<FString> values;
	int32 nextIndex;

private:
	void parse(const TSharedPtr<FJsonObject>& settings) override;

	FString generateFileName(const FString& fileName) const;

public:
	FilesGenerationSettingsParser(const TSharedPtr<FJsonObject>& settings);

	FString getFileName(const FString& fileName);

	void reset();

	~FilesGenerationSettingsParser() = default;
};
