// Copyright (c) 2022 Arkadiy Zakharov

#include "AnimationCutterAction.h"

#include "ToolMenus.h"
#include "Misc/FileHelper.h"
#include "IDesktopPlatform.h"
#include "DesktopPlatformModule.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

#include "LogAnimationCutter.h"

bool FAnimationCutterAction::getErrors(const TArray<BaseSettingsParser*>& parsers)
{
	bool isError = false;
	
	for (const auto& parser : parsers)
	{
		TArray<FString> errors = parser->getErrors();

		if (!isError && errors.Num())
		{
			isError = true;
		}

		for (const auto& error : errors)
		{
			UE_LOG(LogAnimation, Error, TEXT("%s"), *error);
		}
	}

	return isError;
}

TSharedPtr<FJsonObject> FAnimationCutterAction::readSettingsFile()
{
	IDesktopPlatform* platform = FDesktopPlatformModule::Get();
	TArray<FString> files;
	TSharedPtr<FJsonObject> json;

	if (!platform)
	{
		UE_LOG(LogAnimationCutter, Error, TEXT("Can't get FDesktopPlatformModule"));

		return json;
	}

	bool isSuccess = platform->OpenFileDialog
	(
		nullptr,
		"Choose settings file",
		"",
		"",
		"Settings file|*.json",
		EFileDialogFlags::Type::None,
		files
	);

	if (isSuccess && files.Num())
	{
		FString file;

		if (!FFileHelper::LoadFileToString(file, *files[0]))
		{
			UE_LOG(LogAnimationCutter, Error, TEXT("Fail to read file"));

			return json;
		}

		TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(file);

		FJsonSerializer::Deserialize(reader, json);
	}
	else
	{
		UE_LOG(LogAnimationCutter, Error, TEXT("Wrong file"));
	}

	return json;
}

void FAnimationCutterAction::cutAnimationsProcess(TArray<TWeakObjectPtr<UAnimSequence>> animSequences)
{
	this->cutAnimations(FAnimationCutterAction::readSettingsFile(), animSequences);
}

void FAnimationCutterAction::cutAnimations(TSharedPtr<FJsonObject> settings, TArray<TWeakObjectPtr<UAnimSequence>> animSequences)
{
	if (!settings.IsValid())
	{
		UE_LOG(LogAnimationCutter, Error, TEXT("Wrong settings file"));

		return;
	}

	FramesSettingsParser framesSettings(settings);
	AnimSequenceSettingsParser animSequenceSettings(settings);
	OutPathSettingsParser outPathSettings(settings);
	FilesGenerationSettingsParser filesGenerationSettings(settings);

	if (FAnimationCutterAction::getErrors({ &framesSettings, &animSequenceSettings, &outPathSettings, &filesGenerationSettings }))
	{
		return;
	}

	for (const TWeakObjectPtr<UAnimSequence>& animSequence : animSequences)
	{
		int32 frames = animSequence->GetNumberOfFrames();

		for (int32 startCutFrameIndex = 0; startCutFrameIndex < frames; startCutFrameIndex += framesSettings.getStep())
		{
			this->createNewAnimSequence(animSequence, startCutFrameIndex, framesSettings, animSequenceSettings, outPathSettings, filesGenerationSettings);
		}

		filesGenerationSettings.reset();
	}
}

void FAnimationCutterAction::createNewAnimSequence(const TWeakObjectPtr<UAnimSequence>& sourceSequence, int32 startCutFrameIndex, const FramesSettingsParser& framesSettings, const AnimSequenceSettingsParser& animSequenceSettings, const OutPathSettingsParser& outPathSettings, FilesGenerationSettingsParser& filesGenerationSettings)
{
	FString fileName = filesGenerationSettings.getFileName(sourceSequence->GetName());
	UPackage* package = CreatePackage(*outPathSettings.getReferenceOutPath(sourceSequence.Get(), fileName));
	UAnimSequence* animSequence = DuplicateObject<UAnimSequence>(sourceSequence.Get(), package, *fileName);
	
	animSequenceSettings.initAnimSequence(animSequence);

	animSequence->RefPoseSeq = sourceSequence.Get();

	animSequence->CropRawAnimData(animSequence->GetTimeAtFrame(startCutFrameIndex), true);

	animSequence->CropRawAnimData(animSequence->GetTimeAtFrame(framesSettings.getFramesToCut()), false);

	FAssetRegistryModule::AssetCreated(animSequence);

	animSequence->MarkPackageDirty();

	UPackage::Save(package, animSequence, animSequence->GetFlags(), *outPathSettings.getRealOutPath(sourceSequence.Get(), fileName));
}

void FAnimationCutterAction::GetActions(const TArray<UObject*>& InObjects, FToolMenuSection& Section)
{
	FAnimSequenceAssetAction::GetActions(InObjects, Section);

	TArray<TWeakObjectPtr<UAnimSequence>> animSequences = GetTypedWeakObjectPtrs<UAnimSequence>(InObjects);

	Section.AddMenuEntry
	(
		"CutAnimations",
		FText::FromString("Cut animation sequence"),
		FText::FromString("Cut one animation sequence to few animation sequences"),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateSP(this, &FAnimationCutterAction::cutAnimationsProcess, animSequences), FCanExecuteAction())
	);
}
