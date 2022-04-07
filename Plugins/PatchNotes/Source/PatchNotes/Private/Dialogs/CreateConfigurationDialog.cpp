// Copyright (c) 2022 Arkadiy Zakharov

#include "Dialogs/CreateConfigurationDialog.h"

#include "PatchNotes.h"
#include "Interfaces/IPluginManager.h"
#include "Utility.h"

void CreateConfigurationDialog::collectData(const FPatchNotesModule& module, Validation& validation)
{
	validation.checkConfiguration();

	VALIDATION_CHECK();

	configuration = Utility::getConfigurationName(module.getConfigurations()->getCurrentSelectionString());
	pathToConfigurations = &module.getPathToConfigurations();
	pathToTemplate = &module.getPathToTemplate();
	settings = Utility::getJSON(module.getPathToSettingsFile());
}

TSharedPtr<SCustomDialog> CreateConfigurationDialog::createDialog()
{
	return SNew(SCustomDialog)
		.Title(FText::FromName(TEXT("Create configuration")))
		.DialogContent
		(
			SNew(SVerticalBox) 
			+ SVerticalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Center).VAlign(EVerticalAlignment::VAlign_Top).AutoHeight()
			[
				SNew(STextBlock).Text(FText::FromString(configuration)).MinDesiredWidth(200.0f)
			]
			+ SVerticalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Center).VAlign(EVerticalAlignment::VAlign_Top).AutoHeight()
			[
				SAssignNew(version, SEditableTextBox).HintText(FText::FromName(TEXT("Version"))).MinDesiredWidth(200.0f)
			]
			)
		.Buttons
		(
			{
				SCustomDialog::FButton
				(
					FText::FromName(TEXT("Create")),
					FSimpleDelegate::CreateLambda
					(
						[this]()
						{
							IPlatformFile& platformFile = FPlatformFileManager::Get().GetPlatformFile();
							FString pathToNewConfiguration = (*pathToConfigurations) / FString::Printf(TEXT("%s_%s.json"), *configuration, *version->GetText().ToString());
							bool isTemplateExists = platformFile.FileExists(**pathToTemplate);

							if (platformFile.FileExists(*pathToNewConfiguration))
							{
								FMessageDialog::Open(EAppMsgType::Type::Ok, FText::FromName(TEXT("Configuration already exists")));

								return;
							}

							TSharedPtr<FJsonObject> configurationData = MakeShareable(new FJsonObject());

							configurationData->SetStringField(TEXT("projectName"), settings->GetStringField(TEXT("projectName")));

							configurationData->SetStringField(TEXT("projectVersion"), version->GetText().ToString());

							if (!pathToTemplate->IsEmpty() && isTemplateExists)
							{
								TSharedPtr<FJsonObject> templateData = Utility::getJSON(*pathToTemplate);

								for (const auto& value : templateData->Values)
								{
									const TSharedPtr<FJsonObject>* category = nullptr;

									if (value.Value->TryGetObject(category))
									{
										configurationData->SetObjectField(value.Key, *category);
									}
								}
							}
							else if (!isTemplateExists)
							{
								UE_LOG(LogPatchNotes, Error, TEXT("Template file '%s' doesn't exist"), **pathToTemplate);
							}

							Utility::modifyConfigurationFile(pathToNewConfiguration, configurationData);
						}
					)
				)
			}
		);
}

CreateConfigurationDialog::CreateConfigurationDialog(const FPatchNotesModule& module) :
	BaseDialog(module)
{

}
