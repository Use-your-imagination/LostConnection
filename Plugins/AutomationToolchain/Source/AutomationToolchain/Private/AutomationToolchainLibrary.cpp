// Copyright (c) 2022 Semyon Gritsenko

#include "AutomationToolchainLibrary.h"

#include "Interfaces/IPluginManager.h"
#include "Async/Async.h"
#include "Misc/FileHelper.h"
#include "Modules/ModuleManager.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/NetworkVersion.h"
#include "Runtime/Launch/Resources/Version.h"

#include "AutomationToolchain.h"

FString UAutomationToolchainLibrary::buildPath(const FString& pathToFolder, const FString& fileName, const FString& extension)
{
	return FString::Printf(TEXT("%s.%s"), *(pathToFolder / fileName), *extension);
}

void UAutomationToolchainLibrary::runOnMainThreadFunction(TUniqueFunction<void()>&& function)
{
	AsyncTask(ENamedThreads::Type::GameThread, MoveTemp(function));
}

TSharedPtr<FJsonObject> UAutomationToolchainLibrary::getSettings()
{
	FString data;
	TSharedPtr<FJsonObject> settings;
	const FString& pathToSettingsFile = StaticCast<FAutomationToolchainModule*>(FModuleManager::Get().GetModule("AutomationToolchain"))->getPathToSettingsFile();

	if (!UAutomationToolchainLibrary::getPlatformFile().FileExists(*pathToSettingsFile))
	{
		UE_LOG(LogAutomationToolchain, Warning, TEXT("Can't find settings file"));

		return nullptr;
	}

	FFileHelper::LoadFileToString(data, *pathToSettingsFile);

	FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(data), settings);

	return settings;
}

IPlatformFile& UAutomationToolchainLibrary::getPlatformFile()
{
	return FPlatformFileManager::Get().GetPlatformFile();
}

bool UAutomationToolchainLibrary::executeProcess(const FString& url, const FString& parameters, int32& code, FString& outStd, FString& errStd, const FString& optionalWorkingDirectory)
{
	return FPlatformProcess::ExecProcess
	(
		*url,
		*parameters,
		&code,
		&outStd,
		&errStd,
		optionalWorkingDirectory.IsEmpty() ? nullptr : *optionalWorkingDirectory
#if ENGINE_MAJOR_VERSION == 5
		,true
#endif
	);
}

bool UAutomationToolchainLibrary::executeShellCommand(const FString& command, const FString& parameters, int32& code, FString& outStd, FString& errStd, const FString& optionalWorkingDirectory)
{
	FString shellName;

#if PLATFORM_WINDOWS
	shellName = "cmd";
#elif PLATFORM_MAC
	UE_LOG(LogAutomationToolchain, Warning, TEXT("Doesn't support macOS"));

	return false;
#elif PLATFORM_LINUX
	UE_LOG(LogAutomationToolchain, Warning, TEXT("Doesn't support Linux"));

	return false;
#endif // PLATFORM_WINDOWS

	return UAutomationToolchainLibrary::executeProcess(shellName, FString::Printf(TEXT("/C %s %s"), *command, *parameters), code, outStd, errStd, optionalWorkingDirectory);
}

bool UAutomationToolchainLibrary::executePowerShellCommand(const FString& command, const FString& parameters, int32& code, FString& outStd, FString& errStd, const FString& optionalWorkingDirectory)
{
#if PLATFORM_MAC
	UE_LOG(LogAutomationToolchain, Warning, TEXT("Doesn't support macOS"));

	return false;
#elif PLATFORM_LINUX
	UE_LOG(LogAutomationToolchain, Warning, TEXT("Doesn't support Linux"));

	return false;
#endif // PLATFORM_MAC

	return UAutomationToolchainLibrary::executeProcess("cmd", FString::Printf(TEXT("/C PowerShell -command %s %s"), *command, *parameters), code, outStd, errStd, optionalWorkingDirectory);
}

void UAutomationToolchainLibrary::runOnMainThread(const FMainThreadFunction& delegate)
{
	UAutomationToolchainLibrary::runOnMainThreadFunction([delegate]() { delegate.Execute(); });
}

FString UAutomationToolchainLibrary::createFolder(const FString& pathToNewFolder)
{
	if (UAutomationToolchainLibrary::getPlatformFile().CreateDirectory(*pathToNewFolder))
	{
		return FPaths::ConvertRelativePathToFull(pathToNewFolder);
	}

	return "";
}

FString UAutomationToolchainLibrary::createFolderTree(const FString& pathToLastFolder)
{
	if (UAutomationToolchainLibrary::getPlatformFile().CreateDirectoryTree(*pathToLastFolder))
	{
		return FPaths::ConvertRelativePathToFull(pathToLastFolder);
	}

	return "";
}

bool UAutomationToolchainLibrary::createFile(const FString& pathToFolder, const FString& fileName, const FString& extension, const FString& data)
{
	return FFileHelper::SaveStringToFile(data, *UAutomationToolchainLibrary::buildPath(pathToFolder, fileName, extension), FFileHelper::EEncodingOptions::ForceUTF8);
}

bool UAutomationToolchainLibrary::createFileFromArray(const FString& pathToFolder, const FString& fileName, const FString& extension, const TArray<FString>& data)
{
	return FFileHelper::SaveStringArrayToFile(data, *UAutomationToolchainLibrary::buildPath(pathToFolder, fileName, extension), FFileHelper::EEncodingOptions::ForceUTF8);
}

bool UAutomationToolchainLibrary::createBinaryFileFromArray(const FString& pathToFolder, const FString& fileName, const FString& extension, const TArray<uint8>& data)
{
	return FFileHelper::SaveArrayToFile(data, *UAutomationToolchainLibrary::buildPath(pathToFolder, fileName, extension));
}

bool UAutomationToolchainLibrary::readFile(const FString& pathToFile, FString& data)
{
	return FFileHelper::LoadFileToString(data, *pathToFile);
}

bool UAutomationToolchainLibrary::readFileInArray(const FString& pathToFile, TArray<FString>& data)
{
	return FFileHelper::LoadFileToStringArray(data, *pathToFile);
}

bool UAutomationToolchainLibrary::readBinaryFileInArray(const FString& pathToFile, TArray<uint8>& data)
{
	return FFileHelper::LoadFileToArray(data, *pathToFile);
}

bool UAutomationToolchainLibrary::appendFile(const FString& pathToFile, const FString& appendData)
{
	FString data;

	if (FFileHelper::LoadFileToString(data, *pathToFile))
	{
		data += appendData;

		return FFileHelper::SaveStringToFile(data, *pathToFile, FFileHelper::EEncodingOptions::ForceUTF8);
	}

	return false;
}

bool UAutomationToolchainLibrary::appendFileFromArray(const FString& pathToFile, const TArray<FString>& appendData)
{
	TArray<FString> data;

	if (FFileHelper::LoadFileToStringArray(data, *pathToFile))
	{
		data.Append(appendData);

		return FFileHelper::SaveStringArrayToFile(data, *pathToFile, FFileHelper::EEncodingOptions::ForceUTF8);
	}

	return false;
}

bool UAutomationToolchainLibrary::appendBinaryFileFromArray(const FString& pathToFile, const TArray<uint8>& appendData)
{
	TArray<uint8> data;

	if (FFileHelper::LoadFileToArray(data, *pathToFile))
	{
		data.Append(appendData);

		return FFileHelper::SaveArrayToFile(data, *pathToFile);
	}

	return false;
}

bool UAutomationToolchainLibrary::deleteFile(const FString& pathToFile)
{
	return UAutomationToolchainLibrary::getPlatformFile().DeleteFile(*pathToFile);
}

TArray<bool> UAutomationToolchainLibrary::deleteFiles(const TArray<FString>& pathToFiles)
{
	TArray<bool> result;

	result.Reserve(pathToFiles.Num());

	for (const FString& pathToFile : pathToFiles)
	{
		result.Add(UAutomationToolchainLibrary::deleteFile(pathToFile));
	}

	return result;
}

bool UAutomationToolchainLibrary::rename(const FString& newName, const FString& oldName, const FString& path)
{
	return UAutomationToolchainLibrary::getPlatformFile().MoveFile(*(path / newName), *(path / oldName));
}

bool UAutomationToolchainLibrary::move(const FString& newPath, const FString& oldPath)
{
	return UAutomationToolchainLibrary::getPlatformFile().MoveFile(*newPath, *oldPath);
}

void UAutomationToolchainLibrary::findFiles(const FString& pathToFolder, const FString& extension, TArray<FString>& files)
{
	UAutomationToolchainLibrary::getPlatformFile().FindFiles(files, *pathToFolder, *extension);
}

void UAutomationToolchainLibrary::findFilesRecursively(const FString& pathToFolder, const FString& extension, TArray<FString>& files)
{
	UAutomationToolchainLibrary::getPlatformFile().FindFilesRecursively(files, *pathToFolder, *extension);
}

void UAutomationToolchainLibrary::iterateFiles(const FString& pathToFolder, const FIterateFolderFunction& delegate)
{
	IPlatformFile& platformFile = UAutomationToolchainLibrary::getPlatformFile();

	platformFile.IterateDirectory(*pathToFolder, [&platformFile, &delegate](const TCHAR* path, bool) -> bool
	{
		if (platformFile.GetStatData(path).bIsDirectory)
		{
			return false;
		}

		delegate.Execute(path, EPathType::file);

		return true;
	});
}

void UAutomationToolchainLibrary::iterateFilesRecursively(const FString& pathToFolder, const FIterateFolderFunction& delegate)
{
	IPlatformFile& platformFile = UAutomationToolchainLibrary::getPlatformFile();

	platformFile.IterateDirectoryRecursively(*pathToFolder, [&platformFile, &delegate](const TCHAR* path, bool) -> bool
	{
		if (platformFile.GetStatData(path).bIsDirectory)
		{
			return false;
		}

		delegate.Execute(path, EPathType::file);

		return true;
	});
}

void UAutomationToolchainLibrary::iterateFolder(const FString& pathToFolder, const FIterateFolderFunction& delegate)
{
	IPlatformFile& platformFile = UAutomationToolchainLibrary::getPlatformFile();

	platformFile.IterateDirectory(*pathToFolder, [&platformFile, &delegate](const TCHAR* path, bool) -> bool
	{
		delegate.Execute(path, platformFile.GetStatData(path).bIsDirectory ? EPathType::folder : EPathType::file);

		return true;
	});
}

void UAutomationToolchainLibrary::iterateFolderRecursive(const FString& pathToFolder, const FIterateFolderFunction& delegate)
{
	IPlatformFile& platformFile = UAutomationToolchainLibrary::getPlatformFile();

	platformFile.IterateDirectoryRecursively(*pathToFolder, [&platformFile, &delegate](const TCHAR* path, bool) -> bool
	{
		delegate.Execute(path, platformFile.GetStatData(path).bIsDirectory ? EPathType::folder : EPathType::file);

		return true;
	});
}

FString UAutomationToolchainLibrary::getFullPath(const FString& path)
{
	return FPaths::ConvertRelativePathToFull(path);
}

FString UAutomationToolchainLibrary::getAutomationToolchainPluginFolderFullPath()
{
	return FPaths::ConvertRelativePathToFull(IPluginManager::Get().FindPlugin("AutomationToolchain")->GetBaseDir());
}

FString UAutomationToolchainLibrary::getProjectName()
{
	return FApp::GetProjectName();
}

const FString& UAutomationToolchainLibrary::getProjectVersion()
{
	return FNetworkVersion::GetProjectVersion();
}

FString UAutomationToolchainLibrary::appendPath(const FString& path, const FString& next)
{
	return path / next;
}

FString UAutomationToolchainLibrary::getPathToStagedBuildsFolder()
{
	TSharedPtr<FJsonObject> settings = UAutomationToolchainLibrary::getSettings();

	if (!settings)
	{
		return "";
	}

	return settings->GetStringField("pathToStagedBuildsFolder");
}

bool UAutomationToolchainLibrary::getIsRelativePathToStagedBuilds()
{
	TSharedPtr<FJsonObject> settings = UAutomationToolchainLibrary::getSettings();

	if (!settings)
	{
		return false;
	}

	return settings->GetBoolField("isRelativePathToStagedBuilds");
}
