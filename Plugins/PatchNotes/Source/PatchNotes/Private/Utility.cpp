// Copyright (c) 2022 Arkadiy Zakharov

#include "Utility.h"

#include "Serialization/JsonSerializer.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/FileHelper.h"
#include "Async/Async.h"

#include "Constants.h"

void Utility::modifyConfigurationFile(const FString& pathToConfigurationFile, const TSharedPtr<FJsonObject>& object)
{
	FString result;

	FJsonSerializer::Serialize(object.ToSharedRef(), TJsonWriterFactory<>::Create(&result));

	FFileHelper::SaveStringToFile(result, *pathToConfigurationFile, FFileHelper::EEncodingOptions::ForceUTF8);
}

void Utility::updateConfigurationFileWithNotes(const FString& pathToConfigurationFile, const FString& category, const FString& element, const TArray<FString>& notes)
{
	IPlatformFile& platformFile = FPlatformFileManager::Get().GetPlatformFile();
	TSharedPtr<FJsonObject> configurationObject = Utility::getJSON(pathToConfigurationFile);
	TSharedPtr<FJsonObject> categoryObject;
	TSharedPtr<FJsonObject> elementObject = MakeShareable(new FJsonObject());
	FString jsonString;
	TArray<TSharedPtr<FJsonValue>> notesArray;

	notesArray.Reserve(notes.Num());

	for (const FString& note : notes)
	{
		notesArray.Add(MakeShareable(new FJsonValueString(note)));
	}

	categoryObject = configurationObject->GetObjectField(category);

	elementObject->SetStringField(TEXT("type"), TEXT("item"));

	elementObject->SetArrayField(TEXT("notes"), notesArray);

	categoryObject->SetObjectField(element, elementObject);

	Utility::modifyConfigurationFile(pathToConfigurationFile, configurationObject);
}

void Utility::generateStyles(const FString& outPath)
{
	FFileHelper::SaveStringToFile(Constants::getStyles(), *(outPath / Constants::stylesFileName), FFileHelper::EEncodingOptions::ForceUTF8);
}

TSharedPtr<FJsonObject> Utility::getJSON(const FString& pathToJSON)
{
	TSharedPtr<FJsonObject> result;
	FString jsonString;

	FFileHelper::LoadFileToString(jsonString, *pathToJSON);

	FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(jsonString), result);

	return result;
}

FString Utility::getConfigurationName(const FString& configurationWithVersion)
{
	FString result = configurationWithVersion;
	int32 versionPosition;

	result.FindLastChar(TEXT('_'), versionPosition);

	result.RemoveAt(versionPosition, result.Len());

	return result;
}

void Utility::runOnGameThread(const TFunction<void()>& function)
{
	AsyncTask(ENamedThreads::Type::GameThread, function);
}
