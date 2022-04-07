// Copyright (c) 2022 Arkadiy Zakharov

#pragma once

#include "CoreMinimal.h"

#include "Animation/AnimSequence.h"

#include "Settings/AnimSequenceSettingsParser.h"
#include "Settings/FilesGenerationSettingsParser.h"
#include "Settings/FramesSettingsParser.h"
#include "Settings/OutPathSettingsParser.h"

#include "AnimSequenceAssetAction.h"

class FAnimationCutterAction : public FAnimSequenceAssetAction
{
private:
	static bool getErrors(const TArray<BaseSettingsParser*>& parsers);

	TSharedPtr<FJsonObject> readSettingsFile();

private:
	void cutAnimationsProcess(TArray<TWeakObjectPtr<UAnimSequence>> animSequences);

	void cutAnimations(TSharedPtr<FJsonObject> settings, TArray<TWeakObjectPtr<UAnimSequence>> animSequences);

	void createNewAnimSequence(const TWeakObjectPtr<UAnimSequence>& sourceSequence, int32 startCutFrameIndex, const FramesSettingsParser& framesSettings, const AnimSequenceSettingsParser& animSequenceSettings, const OutPathSettingsParser& outPathSettings, FilesGenerationSettingsParser& filesGenerationSettings);

public:
	void GetActions(const TArray<UObject*>& InObjects, struct FToolMenuSection& Section) override;
};
