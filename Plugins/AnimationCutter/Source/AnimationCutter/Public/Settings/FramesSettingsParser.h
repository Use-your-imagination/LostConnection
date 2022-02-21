// Copyright (c) 2022 Arkadiy Zakharov

#pragma once

#include "CoreMinimal.h"

#include "BaseSettingsParser.h"

class FramesSettingsParser : public BaseSettingsParser
{
private:
	int32 step;
	int32 framesToCut;

private:
	void parse(const TSharedPtr<FJsonObject>& settings) override;

public:
	FramesSettingsParser(const TSharedPtr<FJsonObject>& settings);

	int32 getStep() const;

	int32 getFramesToCut() const;

	~FramesSettingsParser() = default;
};
