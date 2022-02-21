// Copyright (c) 2022 Arkadiy Zakharov

#include "Settings/FilesGenerationSettingsParser.h"

void FilesGenerationSettingsParser::parse(const TSharedPtr<FJsonObject>& settings)
{
	FString settingsType;

	if (!settings->TryGetStringField("generationType", settingsType) || settingsType == "standard")
	{
		type = generationType::standard;
	}
	else if (settingsType == "prefixes")
	{
		if (!settings->TryGetStringArrayField("prefixes", values))
		{
			errors.Add("Can't find prefixes field");
		}

		type = generationType::prefixes;
	}
	else if (settingsType == "postfixes")
	{
		if (!settings->TryGetStringArrayField("postfixes", values))
		{
			errors.Add("Can't find postfixes field");
		}

		type = generationType::postfixes;
	}
	else
	{
		errors.Add("Wrong generationType");
	}

	if (!values.Num())
	{
		type = generationType::standard;
	}

	this->reset();
}

FString FilesGenerationSettingsParser::generateFileName(const FString& fileName) const
{
	switch (type)
	{
	case generationType::prefixes:
		return values[nextIndex] + fileName;

	case generationType::postfixes:
		return fileName + values[nextIndex];

	case generationType::standard:
		return fileName + FString::FromInt(nextIndex);

	default:
		return {};
	}
}

FilesGenerationSettingsParser::FilesGenerationSettingsParser(const TSharedPtr<FJsonObject>& settings)
{
	this->parse(settings);
}

FString FilesGenerationSettingsParser::getFileName(const FString& fileName)
{
	FString result;

	if (type == generationType::standard || (nextIndex < values.Num()))
	{
		result = this->generateFileName(fileName);
	}
	else
	{
		int32 tem = nextIndex;

		nextIndex = values.Num() - 1;

		result = this->generateFileName(fileName) + FString::FromInt(tem - values.Num());

		nextIndex = tem;
	}

	nextIndex++;

	return result;
}

void FilesGenerationSettingsParser::reset()
{
	nextIndex = 0;
}
