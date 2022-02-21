// Copyright (c) 2022 Arkadiy Zakharov

#pragma once

#include "CoreMinimal.h"

#include "Animation/AnimSequence.h"

#include "BaseSettingsParser.h"

class AnimSequenceSettingsParser : public BaseSettingsParser
{
private:
	EAdditiveAnimationType animationType;
	EAdditiveBasePoseType basePoseType;
	EAnimInterpolationType interpolationType;

private:
	void parse(const TSharedPtr<FJsonObject>& settings) override;

public:
	AnimSequenceSettingsParser(const TSharedPtr<FJsonObject>& settings);

	void initAnimSequence(UAnimSequence* animSequence) const;

	~AnimSequenceSettingsParser() = default;
};
