// Copyright (c) 2022 Arkadiy Zakharov

#pragma once

#include "CoreMinimal.h"

#include "Animation/AnimSequence.h"

#include "BaseSettingsParser.h"

class OutPathSettingsParser : public BaseSettingsParser
{
private:
	bool isRelative;
	FString outPath;

private:
	void parse(const TSharedPtr<FJsonObject>& settings) override;

public:
	OutPathSettingsParser(const TSharedPtr<FJsonObject>& settings);

	FString getRealOutPath(const UAnimSequence* animSequence, const FString& fileName) const;

	FString getReferenceOutPath(const UAnimSequence* animSequence, const FString& fileName) const;

	~OutPathSettingsParser() = default;
};
