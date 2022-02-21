// Copyright (c) 2022 Arkadiy Zakharov

#include "Settings/FramesSettingsParser.h"

void FramesSettingsParser::parse(const TSharedPtr<FJsonObject>& settings)
{
	if (!settings->TryGetNumberField("step", step))
	{
		errors.Add("Missing step field");
	}

	if (!settings->TryGetNumberField("animationLength", framesToCut))
	{
		framesToCut = step;
	}

	framesToCut--;
}

FramesSettingsParser::FramesSettingsParser(const TSharedPtr<FJsonObject>& settings)
{
	this->parse(settings);
}

int32 FramesSettingsParser::getStep() const
{
	return step;
}

int32 FramesSettingsParser::getFramesToCut() const
{
	return framesToCut;
}
