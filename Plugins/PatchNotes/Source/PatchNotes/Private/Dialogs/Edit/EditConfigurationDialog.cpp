// Copyright (c) 2022 Arkadiy Zakharov

#include "Dialogs/Edit/EditConfigurationDialog.h"

#include "PatchNotes.h"
#include "Utility.h"

void EditConfigurationDialog::collectData(const FPatchNotesModule& module, Validation& validation)
{
	validation.checkConfigurationExist();

	validation.checkConfiguration();

	VALIDATION_CHECK();

	const FString& configuration = module.getConfigurations()->getCurrentSelectionString();

	int32 versionPosition;

	configuration.FindLastChar(TEXT('_'), versionPosition);

	currentVersion = configuration.Mid(versionPosition + 1);
	pathToConfiguration = FString::Printf(TEXT("%s.json"), *(module.getPathToConfigurations() / configuration));
	configurationName = Utility::getConfigurationName(configuration);
	pathToConfigurations = &module.getPathToConfigurations();
	updateConfigurations = [&module]() { const_cast<FPatchNotesModule&>(module).updateConfigurations(); };
}

TSharedPtr<SCustomDialog> EditConfigurationDialog::createDialog()
{
	return SNew(SCustomDialog)
		.Title(FText::FromName(TEXT("Edit configuration")))
		.DialogContent
		(
			SNew(SVerticalBox)
			+ SVerticalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Center).VAlign(EVerticalAlignment::VAlign_Center).AutoHeight()
			[
				SNew(STextBlock).Text(FText::FromString(FString::Printf(TEXT("Current version to change: %s"), *currentVersion))).MinDesiredWidth(200.0f)
			]
			+ SVerticalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Center).VAlign(EVerticalAlignment::VAlign_Center).AutoHeight()
			[
				SAssignNew(newVersion, SEditableTextBox).HintText(FText::FromName(TEXT("New version"))).MinDesiredWidth(200.0f)
			]
		)
		.Buttons
		(
			{
				SCustomDialog::FButton
				(
					FText::FromName(TEXT("Edit")),
					FSimpleDelegate::CreateLambda
					(
						[this]()
						{
							const FString& newVersionName = newVersion->GetText().ToString();

							if (newVersionName.IsEmpty())
							{
								FMessageDialog::Open(EAppMsgType::Type::Ok, FText::FromName(TEXT("New version can't be empty")));

								return;
							}

							TSharedPtr<FJsonObject> configurationData = Utility::getJSON(pathToConfiguration);
							IPlatformFile& platformFile = FPlatformFileManager::Get().GetPlatformFile();
							FString newConfiguration = FString::Printf(TEXT("%s_%s.json"), *((*pathToConfigurations) / configurationName), *newVersionName);

							configurationData->SetStringField(TEXT("projectVersion"), newVersionName);

							if (platformFile.FileExists(*newConfiguration))
							{
								FMessageDialog::Open(EAppMsgType::Type::Ok, FText::FromName(TEXT("Configuration with this version already exists")));

								return;
							}

							Utility::modifyConfigurationFile(newConfiguration, configurationData);

							platformFile.DeleteFile(*pathToConfiguration);

							updateConfigurations();
						}
					)
				)
			}
		);
}

EditConfigurationDialog::EditConfigurationDialog(const FPatchNotesModule& module) :
	BaseDialog(module)
{

}
