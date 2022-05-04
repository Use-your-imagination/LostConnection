// Copyright (c) 2022 Semyon Gritsenko

#pragma once

#include "CoreMinimal.h"

#include "Framework/Commands/UICommandList.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Notifications/SProgressBar.h"

#include "ToolchainDataAsset.h"

#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogAutomationToolchain, Display, All);

class FAutomationToolchainModule : public IModuleInterface
{
private:
	TSharedPtr<FUICommandList> pluginCommands;
	FString pathToSettingsFile;
	bool isRunning;

	UToolchainDataAsset* dataAsset;

	TSharedPtr<SButton> executeActionsButton;
	TSharedPtr<SProgressBar> toolchainExecutionProgressBar;

private:
	void registerMenus();

	TSharedRef<SDockTab> onSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs);

	void initSettings();

	void executeToolchain();

public:
	void pluginButtonClicked();

	const FString& getPathToSettingsFile() const;

	virtual void StartupModule() override;

	virtual void ShutdownModule() override;
};
