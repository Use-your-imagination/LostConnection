// Copyright (c) 2022 Semyon Gritsenko

#include "AutomationToolchain.h"

#include "AutomationToolchainCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include "Misc/FileHelper.h"
#include "Interfaces/IPluginManager.h"
#include "Serialization/JsonSerializer.h"
#include "PropertyCustomizationHelpers.h"
#include "Async/Async.h"

#include "AutomationToolchainStyle.h"
#include "ToolchainDataAsset.h"
#include "AutomationToolchainLibrary.h"

DEFINE_LOG_CATEGORY(LogAutomationToolchain);

static const FName automationToolchainTabName("AutomationToolchain");

#define LOCTEXT_NAMESPACE "FAutomationToolchainModule"

TSharedRef<SDockTab> FAutomationToolchainModule::onSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.HAlign(EHorizontalAlignment::HAlign_Center)
			.VAlign(EVerticalAlignment::VAlign_Top)
			.AutoHeight()
			[
				SNew(STextBlock).Text(FText::FromString("Select toolchain data asset"))
			]
			+ SVerticalBox::Slot()
			.HAlign(EHorizontalAlignment::HAlign_Center)
			.VAlign(EVerticalAlignment::VAlign_Top)
			.AutoHeight()
			[
				SNew(SObjectPropertyEntryBox)
				.AllowedClass(UToolchainDataAsset::StaticClass())
				.AllowClear(true)
				.ObjectPath_Lambda([this]() { return IsValid(dataAsset) ? dataAsset->GetPathName() : ""; })
				.OnObjectChanged_Lambda([this](const FAssetData& asset) { dataAsset = Cast<UToolchainDataAsset>(asset.GetAsset()); })
			]
			+ SVerticalBox::Slot()
			.HAlign(EHorizontalAlignment::HAlign_Center)
			.VAlign(EVerticalAlignment::VAlign_Top)
			.AutoHeight()
			[
				SAssignNew(executeActionsButton, SButton)
				.Text(FText::FromString("Execute toolchain"))
				.OnClicked_Lambda
				(
					[this]()
					{
						if (!IsValid(dataAsset))
						{
							FMessageDialog::Open(EAppMsgType::Type::Ok, FText::FromString("Can't execute empty toolchain"));

							return FReply::Handled();
						}

						executeActionsButton->SetEnabled(false);

						toolchainExecutionProgressBar->SetPercent(0.0f);

						isRunning = true;

						Async(EAsyncExecution::Thread, [this]()
							{
								this->executeToolchain();
							});

						return FReply::Handled();
					}
				)
			]
			+ SVerticalBox::Slot()
			.HAlign(EHorizontalAlignment::HAlign_Fill)
			.VAlign(EVerticalAlignment::VAlign_Bottom)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.HAlign(EHorizontalAlignment::HAlign_Fill)
				[
					SAssignNew(toolchainExecutionProgressBar, SProgressBar).Percent(0.0f)
				]
				+ SHorizontalBox::Slot()
				.HAlign(EHorizontalAlignment::HAlign_Right)
				.AutoWidth()
				[
					SNew(SButton)
					.Text(FText::FromString("Cancel"))
					.OnClicked_Lambda
					(
						[this]()
						{
							isRunning = false;

							return FReply::Handled();
						}
					)
				]
			]
		];
}

void FAutomationToolchainModule::initSettings()
{
	TSharedPtr<FJsonObject> object = MakeShareable(new FJsonObject());
	FString defaultSettings;

	object->SetStringField("pathToStagedBuildsFolder", FPaths::ConvertRelativePathToFull(FPaths::ProjectSavedDir()) / TEXT("StagedBuilds"));

	object->SetBoolField("isRelativePathToStagedBuilds", false);

	FJsonSerializer::Serialize(object.ToSharedRef(), TJsonWriterFactory<>::Create(&defaultSettings));

	FFileHelper::SaveStringToFile(defaultSettings, *pathToSettingsFile, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
}

void FAutomationToolchainModule::executeToolchain()
{
	int32 actionsToProcess = dataAsset->getActions().Num();
	int32 processedActions = 0;

	for (TSubclassOf<UToolchainAction> actionClass : dataAsset->getActions())
	{
		if (!isRunning)
		{
			break;
		}

		UToolchainAction* action = NewObject<UToolchainAction>(GetTransientPackage(), actionClass);

		action->initialization();

		action->execute();

		if (!action->getContinueToolchain())
		{
			break;
		}

		processedActions++;

		UAutomationToolchainLibrary::runOnMainThreadFunction([this, actionsToProcess, processedActions]()
			{
				toolchainExecutionProgressBar->SetPercent(StaticCast<float>(processedActions) / StaticCast<float>(actionsToProcess) * 100.0f);
			});
	}

	FPlatformProcess::Sleep(1.0f);

	UAutomationToolchainLibrary::runOnMainThreadFunction([this]()
		{
			executeActionsButton->SetEnabled(true);

			toolchainExecutionProgressBar->SetPercent(0.0f);
		});
}

void FAutomationToolchainModule::registerMenus()
{
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* toolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");

		{
			FToolMenuSection& section = toolbarMenu->FindOrAddSection("AutomationToolchain");

			{
				FToolMenuEntry& entry = section.AddEntry(FToolMenuEntry::InitToolBarButton(FAutomationToolchainCommands::Get().openPluginWindow));

				entry.SetCommandList(pluginCommands);
			}
		}
	}
}

void FAutomationToolchainModule::pluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(automationToolchainTabName);
}

const FString& FAutomationToolchainModule::getPathToSettingsFile() const
{
	return pathToSettingsFile;
}

void FAutomationToolchainModule::StartupModule()
{
	IPlatformFile& platformFile = UAutomationToolchainLibrary::getPlatformFile();
	FString pluginFolder = UAutomationToolchainLibrary::getAutomationToolchainPluginFolderFullPath();
	FSlateIcon icon(FAutomationToolchainStyle::getStyleSetName(), "AutomationToolchain.TabIcon");
	FString settingsFolder = pluginFolder / TEXT("Settings");

	pathToSettingsFile = settingsFolder / TEXT("automation_toolchain_settings.json");

	isRunning = false;

	if (!platformFile.DirectoryExists(*settingsFolder))
	{
		platformFile.CreateDirectory(*settingsFolder);
	}

	if (!platformFile.FileExists(*pathToSettingsFile))
	{
		this->initSettings();
	}

	FAutomationToolchainStyle::initialize();

	FAutomationToolchainStyle::reloadTextures();

	FAutomationToolchainCommands::Register();
	
	pluginCommands = MakeShareable(new FUICommandList);

	pluginCommands->MapAction
	(
		FAutomationToolchainCommands::Get().openPluginWindow,
		FExecuteAction::CreateRaw(this, &FAutomationToolchainModule::pluginButtonClicked),
		FCanExecuteAction()
	);

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FAutomationToolchainModule::registerMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(automationToolchainTabName, FOnSpawnTab::CreateRaw(this, &FAutomationToolchainModule::onSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FAutomationToolchainTabTitle", "Automation Toolchain"))
		.SetMenuType(ETabSpawnerMenuType::Hidden)
		.SetIcon(icon);
}

void FAutomationToolchainModule::ShutdownModule()
{
	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FAutomationToolchainStyle::shutdown();

	FAutomationToolchainCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(automationToolchainTabName);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAutomationToolchainModule, AutomationToolchain)
