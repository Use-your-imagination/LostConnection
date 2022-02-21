// Copyright (c) 2022 Arkadiy Zakharov

#include "Settings/OutPathSettingsParser.h"

void OutPathSettingsParser::parse(const TSharedPtr<FJsonObject>& settings)
{
	TSharedPtr<FJsonValue> isRelativeSetting = settings->TryGetField("isRelative");

	if (isRelativeSetting.IsValid())
	{
		isRelative = isRelativeSetting->AsBool();
	}

	if (!settings->TryGetStringField("outPath", outPath))
	{
		errors.Add("Missing outPath field");
	}

	if (!(outPath.EndsWith("/") || outPath.EndsWith("\\")))
	{
		outPath += '/';
	}
}

OutPathSettingsParser::OutPathSettingsParser(const TSharedPtr<FJsonObject>& settings) :
	isRelative(false)
{
	this->parse(settings);
}

FString OutPathSettingsParser::getRealOutPath(const UAnimSequence* animSequence, const FString& fileName) const
{
	return this->getReferenceOutPath(animSequence, fileName).Replace(TEXT("/Game/"), *FPaths::ProjectContentDir()) + FPackageName::GetAssetPackageExtension();
}

FString OutPathSettingsParser::getReferenceOutPath(const UAnimSequence* animSequence, const FString& fileName) const
{
	if (isRelative)
	{
		FString result = animSequence->GetPathName();
		int32 index = 0;

		result.FindLastChar('/', index);

		result.RemoveAt(index + 1, result.Len(), false);

		result += outPath + fileName;

		return result;
	}
	else
	{
		return "/Game/" + outPath + fileName;
	}
}
