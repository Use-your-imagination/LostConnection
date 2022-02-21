// Copyright (c) 2022 Arkadiy Zakharov

#include "AnimationCutter.h"

#include "AnimationCutterAction.h"

#define LOCTEXT_NAMESPACE "FAnimationCutterModule"

void FAnimationCutterModule::StartupModule()
{
	IAssetTools& assetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	assetTools.RegisterAssetTypeActions(MakeShareable(new FAnimationCutterAction()));
}

void FAnimationCutterModule::ShutdownModule()
{
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAnimationCutterModule, AnimationCutter)
