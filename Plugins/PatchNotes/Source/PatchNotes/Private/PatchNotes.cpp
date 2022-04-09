// Copyright (c) 2022 Arkadiy Zakharov

#include "PatchNotes.h"

#include "LevelEditor.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/FileHelper.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"
#include "Brushes/SlateImageBrush.h"
#include "SlateFwd.h"
#include "Widgets/Layout/SWrapBox.h"
#include "Misc/MessageDialog.h"
#include "DesktopPlatformModule.h"
#include "IDesktopPlatform.h"
#include "Misc/App.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Async/Async.h"

#include "PatchNotesStyle.h"
#include "PatchNotesCommands.h"
#include "Utility.h"
#include "HTMLGenerator.h"
#include "Constants.h"

#include "Dialogs/CreateConfigurationDialog.h"
#include "Dialogs/CreateCategoryDialog.h"
#include "Dialogs/ChangeCategoriesOrderDialog.h"

#include "Dialogs/Edit/EditConfigurationDialog.h"
#include "Dialogs/Edit/EditCategoryDialog.h"
#include "Dialogs/Edit/EditElementDialog.h"
#include "Dialogs/Edit/EditNotesDialog.h"

#include "Dialogs/Delete/DeleteConfigurationDialog.h"
#include "Dialogs/Delete/DeleteCategoryDialog.h"
#include "Dialogs/Delete/DeleteElementDialog.h"
#include "Dialogs/Delete/DeleteNotesDialog.h"

DEFINE_LOG_CATEGORY(LogPatchNotes);

static const FName patchNotesTabName(TEXT("PatchNotes"));

#define LOCTEXT_NAMESPACE "FPatchNotesModule"

void FPatchNotesModule::registerMenus()
{
	FToolMenuOwnerScoped ownerScoped(this);

	{
		UToolMenu* toolbar = UToolMenus::Get()->ExtendMenu(TEXT("LevelEditor.LevelEditorToolBar.PlayToolBar"));

		{
			FToolMenuSection& section = toolbar->FindOrAddSection(TEXT("PatchNotes"));

			{
				FToolMenuEntry& entry = section.AddEntry(FToolMenuEntry::InitToolBarButton(FPatchNotesCommands::Get().openPluginWindow));

				entry.SetCommandList(pluginCommands);
			}
		}
	}
}

TSharedRef<SWidget> FPatchNotesModule::makeMenu()
{
	FMenuBarBuilder menuBuilder(nullptr);

	menuBuilder.AddPullDownMenu
	(
		FText::FromName(TEXT("Create")),
		FText::FromName(TEXT("Create new configuration or add category to current configuration")),
		FNewMenuDelegate::CreateLambda
		(
			[this](FMenuBuilder& menuBuilder)
			{
				menuBuilder.BeginSection(TEXT("Create"), FText::FromName(TEXT("Create")));

				menuBuilder.AddMenuEntry
				(
					FText::FromName(TEXT("Create configuration")),
					FText::FromName(TEXT("Create new project configuration")),
					FSlateIcon(),
					FUIAction
					(
						FExecuteAction::CreateLambda([this]() { CreateConfigurationDialog(*this).execute(); }),
						FCanExecuteAction()
					)
				);

				menuBuilder.AddMenuEntry
				(
					FText::FromName(TEXT("Create category")),
					FText::FromName(TEXT("Add category to current configuration")),
					FSlateIcon(),
					FUIAction
					(
						FExecuteAction::CreateLambda([this]() { CreateCategoryDialog(*this).execute(); }),
						FCanExecuteAction()
					)
				);

				menuBuilder.EndSection();
			}
		)
	);

	menuBuilder.AddMenuEntry
	(
		FText::FromName(TEXT("Preview")),
		FText::FromName(TEXT("Generate temporary .html preview file")),
		FSlateIcon(),
		FUIAction
		(
			FExecuteAction::CreateLambda
			(
				[this]()
				{
					IDesktopPlatform* platform = FDesktopPlatformModule::Get();

					if (!platform)
					{
						FMessageDialog::Open(EAppMsgType::Type::Ok, FText::FromName(TEXT("FDesktopPlatformModule::Get() returns NULL")));

						return;
					}

					const FString& currentConfiguration = configurations->getCurrentSelectionString();
					FString fullPath = platform->GetUserTempPath() / currentConfiguration + TEXT(".html");
					FString pathToConfigurationFile = pathToConfigurations / currentConfiguration + TEXT(".json");
					FString stylesFilePath = platform->GetUserTempPath() / Constants::stylesFileName;

					if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*pathToConfigurationFile))
					{
						FMessageDialog::Open(EAppMsgType::Type::Ok, FText::FromName(TEXT("Configuration file doesn't exist")));

						return;
					}

					Async(EAsyncExecution::ThreadPool, [this, stylesFilePath, platform, fullPath, pathToConfigurationFile]()
						{
							Utility::runOnGameThread([this]() { generationProgressBar->SetVisibility(EVisibility::Visible); });

							Utility::generateStyles(platform->GetUserTempPath());

							Utility::runOnGameThread([this]() { generationProgressBar->SetPercent(5.0f); });

							HTMLGenerator::generatePatchNotesHTML(fullPath, pathToConfigurationFile, pathToSettingsFile, generationProgressBar);

							UKismetSystemLibrary::LaunchURL(FString::Printf(TEXT("file://%s"), *fullPath));

							Utility::runOnGameThread([this]() { generationProgressBar->SetPercent(100.0f); });

							this->resetProgressBar();
						});

					temporaryGeneratedFiles.AddUnique(stylesFilePath);

					temporaryGeneratedFiles.AddUnique(fullPath);
				}
			),
			FCanExecuteAction()
		)
	);

	menuBuilder.AddMenuEntry
	(
		FText::FromName(TEXT("Generate notes")),
		FText::FromName(TEXT("Generate .html file and update index.html")),
		FSlateIcon(),
		FUIAction
		(
			FExecuteAction::CreateLambda
			(
				[this]()
				{
					TSharedPtr<FJsonObject> settings = Utility::getJSON(pathToSettingsFile);
					IPlatformFile& platformFile = FPlatformFileManager::Get().GetPlatformFile();
					FString outPath = Utility::getGeneratedFilesPath(settings);
					const FString& currentConfiguration = configurations->getCurrentSelectionString();
					FString htmlNotes = outPath / currentConfiguration + TEXT(".html");
					FString stylesPath = outPath / Constants::stylesFileName;

					if (!platformFile.FileExists(*outPath))
					{
						platformFile.CreateDirectoryTree(*outPath);
					}

					Async(EAsyncExecution::ThreadPool, [this, &platformFile, htmlNotes, currentConfiguration, settings, stylesPath, outPath]()
						{
							FString indexPath = outPath / TEXT("index.html");

							Utility::runOnGameThread([this]() { generationProgressBar->SetVisibility(EVisibility::Visible); });
							
							if (!platformFile.FileExists(*stylesPath))
							{
								Utility::generateStyles(outPath);
							}

							Utility::runOnGameThread([this]() { generationProgressBar->SetPercent(5.0f); });

							HTMLGenerator::generatePatchNotesHTML(htmlNotes, pathToConfigurations / currentConfiguration + TEXT(".json"), settings, generationProgressBar);

							if (!platformFile.FileExists(*indexPath))
							{
								HTMLGenerator::generateIndexHTML(outPath, currentConfiguration, settings);
							}
							else
							{
								HTMLGenerator::updateIndexHTML(outPath, currentConfiguration);
							}

							Utility::runOnGameThread([this]() { generationProgressBar->SetPercent(97.5f); });

							if (settings->GetBoolField(TEXT("openAfterUpdate")))
							{
								UKismetSystemLibrary::LaunchURL(FString::Printf(TEXT("file://%s"), *indexPath));
							}

							Utility::runOnGameThread([this]() { generationProgressBar->SetPercent(100.0f); });

							this->resetProgressBar();
						});
				}
			),
			FCanExecuteAction()
		)
	);

	menuBuilder.AddMenuEntry
	(
		FText::FromName(TEXT("Change categories order")),
		FText::GetEmpty(),
		FSlateIcon(),
		FUIAction
		(
			FExecuteAction::CreateLambda([this]() { ChangeCategoriesOrderDialog(*this).execute(); }),
			FCanExecuteAction()
		)
	);

	this->makeEditPullDownMenu(menuBuilder);

	this->makeDeletePullDownMenu(menuBuilder);

	TSharedRef<SWidget> menuBarWidget = menuBuilder.MakeWidget();

	menuBarWidget->SetVisibility(EVisibility::Visible);

	return menuBarWidget;
}

void FPatchNotesModule::makeEditPullDownMenu(FMenuBarBuilder& menuBuilder)
{
	menuBuilder.AddPullDownMenu
	(
		FText::FromName(TEXT("Edit")),
		FText::FromName(TEXT("Edit configurations, categories, elements, notes")),
		FNewMenuDelegate::CreateLambda
		(
			[this](FMenuBuilder& menuBuilder)
			{
				menuBuilder.BeginSection(TEXT("Edit"), FText::FromName(TEXT("Edit")));

				menuBuilder.AddMenuEntry
				(
					FText::FromName(TEXT("Edit configuration")),
					FText::FromName(TEXT("Edit configuration version")),
					FSlateIcon(),
					FUIAction
					(
						FExecuteAction::CreateLambda([this]() { EditConfigurationDialog(*this).execute(); }),
						FCanExecuteAction()
					)
				);

				menuBuilder.AddMenuEntry
				(
					FText::FromName(TEXT("Edit category")),
					FText::GetEmpty(),
					FSlateIcon(),
					FUIAction
					(
						FExecuteAction::CreateLambda([this]() {EditCategoryDialog(*this).execute(); }),
						FCanExecuteAction()
					)
				);

				menuBuilder.AddMenuEntry
				(
					FText::FromName(TEXT("Edit element")),
					FText::GetEmpty(),
					FSlateIcon(),
					FUIAction
					(
						FExecuteAction::CreateLambda([this]() {EditElementDialog(*this).execute(); }),
						FCanExecuteAction()
					)
				);

				menuBuilder.AddMenuEntry
				(
					FText::FromName(TEXT("Edit notes")),
					FText::GetEmpty(),
					FSlateIcon(),
					FUIAction
					(
						FExecuteAction::CreateLambda([this]() {EditNotesDialog(*this).execute(); }),
						FCanExecuteAction()
					)
				);

				menuBuilder.EndSection();
			}
		)
	);
}

void FPatchNotesModule::makeDeletePullDownMenu(FMenuBarBuilder& menuBuilder)
{
	menuBuilder.AddPullDownMenu
	(
		FText::FromName(TEXT("Delete")),
		FText::FromName(TEXT("Delete configurations, categories, elements, notes")),
		FNewMenuDelegate::CreateLambda
		(
			[this](FMenuBuilder& menuBuilder)
			{
				menuBuilder.BeginSection(TEXT("Delete"), FText::FromName(TEXT("Delete")));

				menuBuilder.AddMenuEntry
				(
					FText::FromName(TEXT("Delete configuration")),
					FText::GetEmpty(),
					FSlateIcon(),
					FUIAction
					(
						FExecuteAction::CreateLambda([this]() { DeleteConfigurationDialog(*this).execute(); }),
						FCanExecuteAction()
					)
				);

				menuBuilder.AddMenuEntry
				(
					FText::FromName(TEXT("Delete category")),
					FText::GetEmpty(),
					FSlateIcon(),
					FUIAction
					(
						FExecuteAction::CreateLambda([this]() { DeleteCategoryDialog(*this).execute(); }),
						FCanExecuteAction()
					)
				);

				menuBuilder.AddMenuEntry
				(
					FText::FromName(TEXT("Delete element")),
					FText::GetEmpty(),
					FSlateIcon(),
					FUIAction
					(
						FExecuteAction::CreateLambda([this]() { DeleteElementDialog(*this).execute(); }),
						FCanExecuteAction()
					)
				);

				menuBuilder.AddMenuEntry
				(
					FText::FromName(TEXT("Delete notes")),
					FText::GetEmpty(),
					FSlateIcon(),
					FUIAction
					(
						FExecuteAction::CreateLambda([this]() { DeleteNotesDialog(*this).execute(); }),
						FCanExecuteAction()
					)
				);

				menuBuilder.EndSection();
			}
		)
	);
}

TSharedRef<SDockTab> FPatchNotesModule::onSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	this->init();

	return SNew(SDockTab).TabRole(ETabRole::NomadTab)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot().AutoHeight()
			[
				this->makeMenu()
			]
			+ SVerticalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Center).VAlign(EVerticalAlignment::VAlign_Top).AutoHeight()
			[
				configurations->getComboBox()
			]
			+ SVerticalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Center).VAlign(EVerticalAlignment::VAlign_Top).AutoHeight()
			[
				categories->getComboBox()
			]
			+ SVerticalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Center).VAlign(EVerticalAlignment::VAlign_Top).AutoHeight()
			[
				SAssignNew(element, SEditableTextBox).MinDesiredWidth(214.0f).HintText(FText::FromString(TEXT("Element")))
			]
			+ SVerticalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Fill).VAlign(EVerticalAlignment::VAlign_Fill)
			[
				SNew(SBorder).BorderBackgroundColor(FLinearColor::White)
				[
					SAssignNew(notes, SMultiLineEditableText).HintText(FText::FromName(TEXT("Notes")))
				]
			]
			+ SVerticalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Fill).VAlign(EVerticalAlignment::VAlign_Fill).AutoHeight()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Left).AutoWidth()
				[
					SNew(SBox).WidthOverride(150.0f)
					[
						SNew(SButton)
						.OnClicked_Lambda
						(
							[this]()
							{
								this->addNote();

								return FReply::Handled();
							}
						)
						[
							SNew(STextBlock).Text(FText::FromString(TEXT("Add"))).Justification(ETextJustify::Center)
						]
					]
				]
				+ SHorizontalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Fill)
				[
					SAssignNew(generationProgressBar, SProgressBar)
					.BarFillType(EProgressBarFillType::Type::LeftToRight)
					.FillColorAndOpacity(FSlateColor(generationProgressBarColor))
					.Visibility(EVisibility::Hidden)
				]
			]
		];
}

void FPatchNotesModule::initDefaults(IPlatformFile& platformFile, const FString& pluginFolder)
{
	auto initStyles = [this]()
	{
		TSharedPtr<FJsonObject> settings = Utility::getJSON(pathToSettingsFile);
		const TArray<TSharedPtr<FJsonValue>>& rgbaColorsValues = settings->GetArrayField(TEXT("patchNotesBackgroundColor"));
		const TArray<TSharedPtr<FJsonValue>>& generationProgressBarColorValues = settings->GetArrayField(TEXT("generationProgressBarColor"));
		TSharedPtr<FJsonValue> pathToBackgroundImage = settings->TryGetField("pathToBackgroundImage");
		TArray<float> rgbaColors;

		for (const auto& color : rgbaColorsValues)
		{
			rgbaColors.Add(StaticCast<float>(color->AsNumber()));
		}

		Constants::initBackgroundColors(rgbaColors);

		if (pathToBackgroundImage.IsValid() && !pathToBackgroundImage->IsNull())
		{
			Constants::initBackgroundImage(pathToBackgroundImage->AsString());
		}
		else
		{
			Constants::initBackgroundImage(Constants::getDefaultBackgroundImage());
		}

		generationProgressBarColor = FLinearColor
		(
			StaticCast<float>(generationProgressBarColorValues[0]->AsNumber()),
			StaticCast<float>(generationProgressBarColorValues[1]->AsNumber()),
			StaticCast<float>(generationProgressBarColorValues[2]->AsNumber()),
			StaticCast<float>(generationProgressBarColorValues[3]->AsNumber())
		);
	};

	if (platformFile.FileExists(*pathToSettingsFile))
	{
		initStyles();

		Utility::getJSON(pathToSettingsFile)->TryGetStringField(TEXT("pathToTemplate"), pathToTemplate);

		return;
	}

	TSharedPtr<FJsonObject> object = MakeShareable(new FJsonObject());
	FString defaultSettings;

	object->SetStringField(TEXT("generatedFilesPath"), pluginFolder / TEXT("GeneratedFiles"));

	object->SetBoolField(TEXT("openAfterUpdate"), true);

	object->SetBoolField(TEXT("isRelativeGeneratedFilesPath"), false);

	object->SetStringField(TEXT("projectName"), FApp::GetProjectName());

	object->SetField(TEXT("pathToBackgroundImage"), MakeShared<FJsonValueNull>());

	object->SetField(TEXT("pathToProjectLogo"), MakeShared<FJsonValueNull>());

	object->SetField(TEXT("pathToTemplate"), MakeShared<FJsonValueNull>());

	object->SetArrayField
	(
		TEXT("patchNotesBackgroundColor"),
		{
			MakeShared<FJsonValueNumber>(0.0f),
			MakeShared<FJsonValueNumber>(0.0f),
			MakeShared<FJsonValueNumber>(0.0f),
			MakeShared<FJsonValueNumber>(0.17f),
		}
	);

	object->SetArrayField
	(
		TEXT("generationProgressBarColor"),
		{
			MakeShared<FJsonValueNumber>(0.0f),
			MakeShared<FJsonValueNumber>(1.0f),
			MakeShared<FJsonValueNumber>(0.0f),
			MakeShared<FJsonValueNumber>(1.0f),
		}
	);

	FJsonSerializer::Serialize(object.ToSharedRef(), TJsonWriterFactory<>::Create(&defaultSettings));

	FFileHelper::SaveStringToFile(defaultSettings, *pathToSettingsFile, FFileHelper::EEncodingOptions::ForceUTF8);

	initStyles();
}

void FPatchNotesModule::init()
{
	configurations = MakeUnique<ComboBoxComponent>();
	categories = MakeUnique<ComboBoxComponent>();

	configurations->setOnSelectionChanged([this](TSharedPtr<FString> item)
		{
			this->updateCategories();
		});

	this->updateConfigurations();
}

void FPatchNotesModule::addNote()
{
	FString configuration;
	FString category;
	FString elementValue;
	TArray<FString> notesValues;
	FString pathToConfigurationFile;

	if (!this->collectData(configuration, category, elementValue, notesValues))
	{
		return;
	}

	pathToConfigurationFile = pathToConfigurations / configuration + TEXT(".json");

	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*pathToConfigurationFile))
	{
		FMessageDialog::Open(EAppMsgType::Type::Ok, FText::FromName(TEXT("Configuration file doesn't exist")));

		return;
	}

	Utility::updateConfigurationFileWithNotes(pathToConfigurationFile, category, elementValue, notesValues);

	FMessageDialog::Open(EAppMsgType::Type::Ok, FText::FromName(TEXT("Note added successfully")));

	notes->SetText(FText::GetEmpty());

	element->SetText(FText::GetEmpty());
}

bool FPatchNotesModule::collectData(FString& configuration, FString& category, FString& elementValue, TArray<FString>& notesValues)
{
	FString errors;
	FString data = notes->GetText().ToString();

	configuration = configurations->getCurrentSelectionString();
	category = categories->getCurrentSelectionString();
	elementValue = element->GetText().ToString();

	if (configuration.IsEmpty())
	{
		errors.Append(TEXT("Configuration can't be empty")).Append(LINE_TERMINATOR);
	}

	if (category.IsEmpty())
	{
		errors.Append(TEXT("Category can't be empty")).Append(LINE_TERMINATOR);
	}

	if (elementValue.IsEmpty())
	{
		errors.Append(TEXT("Element can't be empty")).Append(LINE_TERMINATOR);
	}

	if (data.IsEmpty())
	{
		errors.Append(TEXT("Notes can't be empty")).Append(LINE_TERMINATOR);
	}

	data.ParseIntoArray(notesValues, LINE_TERMINATOR);

	if (errors.Len())
	{
		FMessageDialog::Open(EAppMsgType::Type::Ok, FText::FromString(errors));

		return false;
	}

	return true;
}

void FPatchNotesModule::resetProgressBar(float waitSeconds)
{
	FPlatformProcess::Sleep(waitSeconds);

	Utility::runOnGameThread
	(
		[this]()
		{
			generationProgressBar->SetPercent(0.0f);

			generationProgressBar->SetVisibility(EVisibility::Hidden);
		}
	);
}

void FPatchNotesModule::pluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(patchNotesTabName);
}

void FPatchNotesModule::updateConfigurations()
{
	TArray<TSharedPtr<FString>>& values = configurations->getValues();
	TArray<TPair<FDateTime, FString>> configurationFiles;
	IPlatformFile& platformFile = FPlatformFileManager::Get().GetPlatformFile();

	platformFile.IterateDirectory(*pathToConfigurations, [&configurationFiles, &platformFile](const TCHAR* filePath, bool)
		{
			FString fileName = FPaths::GetCleanFilename(filePath);

			fileName.RemoveFromEnd(TEXT(".") + FPaths::GetExtension(filePath));

			configurationFiles.Emplace
			(
				platformFile.GetTimeStampLocal(filePath),
				MoveTemp(fileName)
			);

			return true;
		});

	Algo::Sort(configurationFiles, [](const TPair<FDateTime, FString>& first, const TPair<FDateTime, FString>& second) { return first.Key > second.Key; });

	values.Empty();

	values.Reserve(configurationFiles.Num());

	for (const auto& configurationFile : configurationFiles)
	{
		values.Add(MakeShareable(new FString(configurationFile.Value)));
	}

	configurations->getComboBox()->RefreshOptions();

	if (values.Num())
	{
		configurations->selectElement(0);
	}
}

void FPatchNotesModule::updateCategories()
{
	IPlatformFile& platformFile = FPlatformFileManager::Get().GetPlatformFile();
	TArray<TSharedPtr<FString>>& values = categories->getValues();
	FString configurationFilePath = pathToConfigurations / configurations->getCurrentSelectionString() + TEXT(".json");
	TSharedPtr<FJsonObject> object;
	FString jsonString;

	values.Empty();

	if (!platformFile.FileExists(*configurationFilePath))
	{
		return;
	}

	FFileHelper::LoadFileToString(jsonString, *configurationFilePath);

	if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(jsonString), object))
	{
		UE_LOG(LogTemp, Error, TEXT("Can't parse data, path to file: %s"), *configurationFilePath);

		return;
	}

	for (const auto& value : object->Values)
	{
		const TSharedPtr<FJsonObject>* tem = nullptr;

		if (value.Value->TryGetObject(tem))
		{
			values.Add(MakeShareable(new FString(value.Key)));
		}
	}

	categories->getComboBox()->RefreshOptions();

	if (values.Num())
	{
		categories->selectElement(0);
	}
}

const FString& FPatchNotesModule::getPathToConfigurations() const
{
	return pathToConfigurations;
}

const FString& FPatchNotesModule::getPathToSettingsFile() const
{
	return pathToSettingsFile;
}

const FString& FPatchNotesModule::getPathToTemplate() const
{
	return pathToTemplate;
}

const TUniquePtr<ComboBoxComponent>& FPatchNotesModule::getConfigurations() const
{
	return configurations;
}

const TUniquePtr<ComboBoxComponent>& FPatchNotesModule::getCategories() const
{
	return categories;
}

const TSharedPtr<SEditableTextBox>& FPatchNotesModule::getElement() const
{
	return element;
}

const TSharedPtr<SMultiLineEditableText>& FPatchNotesModule::getNotes() const
{
	return notes;
}

void FPatchNotesModule::StartupModule()
{
	FString pluginFolder = IPluginManager::Get().FindPlugin(TEXT("PatchNotes"))->GetBaseDir();
	FString settingsFolder = pluginFolder / TEXT("Settings");
	IPlatformFile& platformFile = FPlatformFileManager::Get().GetPlatformFile();
	FSlateIcon icon(FPatchNotesStyle::getStyleSetName(), TEXT("PatchNotes.TabIcon"));

	FPatchNotesStyle::initialize();

	FPatchNotesStyle::reloadTextures();

	FPatchNotesCommands::Register();

	pluginCommands = MakeShareable(new FUICommandList);

	pathToSettingsFile = settingsFolder / TEXT("generate_patch_notes_settings.json");

	pathToConfigurations = pluginFolder / TEXT("Configurations");

	pluginCommands->MapAction
	(
		FPatchNotesCommands::Get().openPluginWindow,
		FExecuteAction::CreateRaw(this, &FPatchNotesModule::pluginButtonClicked),
		FCanExecuteAction()
	);

	this->init();

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FPatchNotesModule::registerMenus));

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(patchNotesTabName, FOnSpawnTab::CreateRaw(this, &FPatchNotesModule::onSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FPatchNotesTabTitle", "Patch Notes"))
		.SetMenuType(ETabSpawnerMenuType::Type::Hidden)
		.SetIcon(icon);

	platformFile.CreateDirectory(*settingsFolder);

	platformFile.CreateDirectory(*pathToConfigurations);

	Constants::initDefaults();

	this->initDefaults(platformFile, pluginFolder);
}

void FPatchNotesModule::ShutdownModule()
{
	IPlatformFile& platformFile = FPlatformFileManager::Get().GetPlatformFile();

	for (const FString& temporaryFile : temporaryGeneratedFiles)
	{
		platformFile.DeleteFile(*temporaryFile);
	}

	temporaryGeneratedFiles.Empty();

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FPatchNotesStyle::shutdown();

	FPatchNotesCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(patchNotesTabName);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FPatchNotesModule, PatchNotes)
