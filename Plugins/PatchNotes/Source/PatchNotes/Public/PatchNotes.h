// Copyright (c) 2022 Arkadiy Zakharov

#pragma once

#include "CoreMinimal.h"

#include "Modules/ModuleManager.h"
#include "Framework/Commands/UICommandList.h"
#include "Widgets/Docking/SDockTab.h"
#include "Framework/Docking/TabManager.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "Widgets/Text/SMultiLineEditableText.h"
#include "Widgets/Notifications/SProgressBar.h"

#include "Components/ComboBoxComponent.h"

DECLARE_LOG_CATEGORY_EXTERN(LogPatchNotes, Display, All);

class FPatchNotesModule : public IModuleInterface
{
private:
	TSharedPtr<FUICommandList> pluginCommands;
	FString pathToSettingsFile;
	FString pathToConfigurations;
	FString pathToTemplate;
	TArray<FString> temporaryGeneratedFiles;
	FLinearColor generationProgressBarColor;

	TUniquePtr<ComboBoxComponent> configurations;
	TUniquePtr<ComboBoxComponent> categories;
	TSharedPtr<SEditableTextBox> element;
	TSharedPtr<SMultiLineEditableText> notes;
	TSharedPtr<SProgressBar> generationProgressBar;

private:
	void registerMenus();

	TSharedRef<SWidget> makeMenu();

	void makeEditPullDownMenu(FMenuBarBuilder& menuBuilder);

	void makeDeletePullDownMenu(FMenuBarBuilder& menuBuilder);

	TSharedRef<SDockTab> onSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs);

	void initDefaults(IPlatformFile& platformFile, const FString& pluginFolder);

	void init();

	void addNote();

	bool collectData(FString& configuration, FString& category, FString& elementValue, TArray<FString>& notesValues);

	void resetProgressBar(float waitSeconds = 1.0f);

public:
	void pluginButtonClicked();

	void updateConfigurations();

	void updateCategories();

	const FString& getPathToConfigurations() const;

	const FString& getPathToSettingsFile() const;

	const FString& getPathToTemplate() const;

	const TUniquePtr<ComboBoxComponent>& getConfigurations() const;

	const TUniquePtr<ComboBoxComponent>& getCategories() const;

	const TSharedPtr<SEditableTextBox>& getElement() const;

	const TSharedPtr<SMultiLineEditableText>& getNotes() const;

	void StartupModule() override;

	void ShutdownModule() override;
};
