// Copyright (c) 2022 Semyon Gritsenko

#pragma once

#include "CoreMinimal.h"

#include "Kismet/BlueprintFunctionLibrary.h"
#include "GenericPlatform/GenericPlatformFile.h"

#include "AutomationToolchainLibrary.generated.h"

UENUM(BlueprintType)
enum class EPathType : uint8
{
	folder UMETA(DisplayName = Folder),
	file UMETA(DisplayName = File)
};

DECLARE_DYNAMIC_DELEGATE(FMainThreadFunction);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FIterateFolderFunction, FString, path, EPathType, type);

UCLASS()
class AUTOMATIONTOOLCHAIN_API UAutomationToolchainLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

private:
	static FString buildPath(const FString& pathToFolder, const FString& fileName, const FString& extension);
	
public:
	static void runOnMainThreadFunction(TUniqueFunction<void()>&& function);

	static TSharedPtr<FJsonObject> getSettings();

	static IPlatformFile& getPlatformFile();

	/**
	* Executes process from Url with parameters
	*/
	UFUNCTION(Category = "AutomationToolchain|OS", BlueprintCallable, Meta = (DevelopmentOnly))
	static bool executeProcess(const FString& url, const FString& parameters, int32& code, FString& outStd, FString& errStd, const FString& optionalWorkingDirectory);

	/**
	* Executes Command with Parameters in OS shell
	* Doesn't support macOS
	* Doesn't support Linux
	*/
	UFUNCTION(Category = "AutomationToolchain|OS", BlueprintCallable, Meta = (DevelopmentOnly))
	static bool executeShellCommand(const FString& command, const FString& parameters, int32& code, FString& outStd, FString& errStd, const FString& optionalWorkingDirectory);

	/**
	* Executes Command with Parameters in PowerShell
	*/
	UFUNCTION(Category = "AutomationToolchain|OS", BlueprintCallable, Meta = (DevelopmentOnly))
	static bool executePowerShellCommand(const FString& command, const FString& parameters, int32& code, FString& outStd, FString& errStd, const FString& optionalWorkingDirectory);

	/**
	* All actions execute from separate thread
	* This function allows you to process functions in main thread
	*/
	UFUNCTION(Category = "AutomationToolchain|Threading", BlueprintCallable, Meta = (DevelopmentOnly))
	static void runOnMainThread(const FMainThreadFunction& delegate);

	/**
	* Create folder and return full path to folder
	* Return empty path if can't create folder
	*/
	UFUNCTION(Category = "AutomationToolchain|Files", BlueprintCallable, Meta = (DevelopmentOnly))
	static FString createFolder(const FString& pathToNewFolder);

	/**
	* Create folder and all parents folders and return full path to last folder
	* Return empty path if can't create folders
	*/
	UFUNCTION(Category = "AutomationToolchain|Files", BlueprintCallable, Meta = (DevelopmentOnly))
	static FString createFolderTree(const FString& pathToLastFolder);

	/**
	* Create file with UTF8 encoding
	*/
	UFUNCTION(Category = "AutomationToolchain|Files", BlueprintCallable, Meta = (DevelopmentOnly))
	static bool createFile(const FString& pathToFolder, const FString& fileName, const FString& extension, const FString& data);
	
	/**
	* Create file with UTF8 encoding
	*/
	UFUNCTION(Category = "AutomationToolchain|Files", BlueprintCallable, Meta = (DevelopmentOnly))
	static bool createFileFromArray(const FString& pathToFolder, const FString& fileName, const FString& extension, const TArray<FString>& data);

	/**
	* Create binary file
	*/
	UFUNCTION(Category = "AutomationToolchain|Files", BlueprintCallable, Meta = (DevelopmentOnly))
	static bool createBinaryFileFromArray(const FString& pathToFolder, const FString& fileName, const FString& extension, const TArray<uint8>& data);

	/**
	* Read text file
	*/
	UFUNCTION(Category = "AutomationToolchain|Files", BlueprintCallable, Meta = (DevelopmentOnly))
	static bool readFile(const FString& pathToFile, UPARAM(ref) FString& data);

	/**
	* Read text file
	*/
	UFUNCTION(Category = "AutomationToolchain|Files", BlueprintCallable, Meta = (DevelopmentOnly))
	static bool readFileInArray(const FString& pathToFile, UPARAM(ref) TArray<FString>& data);

	/**
	* Read binary file 
	* Two last bytes are uninitialized
	*/
	UFUNCTION(Category = "AutomationToolchain|Files", BlueprintCallable, Meta = (DevelopmentOnly))
	static bool readBinaryFileInArray(const FString& pathToFile, UPARAM(ref) TArray<uint8>& data);

	/**
	* Append data to end of file without new line with UTF8 encoding
	*/
	UFUNCTION(Category = "AutomationToolchain|Files", BlueprintCallable, Meta = (DevelopmentOnly))
	static bool appendFile(const FString& pathToFile, const FString& appendData);

	/**
	* Append data to end of file without new line with UTF8 encoding
	*/
	UFUNCTION(Category = "AutomationToolchain|Files", BlueprintCallable, Meta = (DevelopmentOnly))
	static bool appendFileFromArray(const FString& pathToFile, const TArray<FString>& appendData);

	/**
	* Append data to end of binary file
	*/
	UFUNCTION(Category = "AutomationToolchain|Files", BlueprintCallable, Meta = (DevelopmentOnly))
	static bool appendBinaryFileFromArray(const FString& pathToFile, const TArray<uint8>& appendData);

	/**
	* Delete file
	*/
	UFUNCTION(Category = "AutomationToolchain|Files", BlueprintCallable, Meta = (DevelopmentOnly))
	static bool deleteFile(const FString& pathToFile);

	/**
	* Delete files
	*/
	UFUNCTION(Category = "AutomationToolchain|Files", BlueprintCallable, Meta = (DevelopmentOnly))
	static TArray<bool> deleteFiles(const TArray<FString>& pathToFiles);

	/**
	* Rename file or folder
	*/
	UFUNCTION(Category = "AutomationToolchain|Files", BlueprintCallable, Meta = (DevelopmentOnly))
	static bool rename(const FString& newName, const FString& oldName, const FString& path);

	/**
	* Move file or folder
	* @param newPath Full path to file or folder with name and extension
	* @param oldPath Full path to file or folder with name and extension
	*/
	UFUNCTION(Category = "AutomationToolchain|Files", BlueprintCallable, Meta = (DevelopmentOnly))
	static bool move(const FString& newPath, const FString& oldPath);

	/**
	* Find files with given Extension
	*/
	UFUNCTION(Category = "AutomationToolchain|Files", BlueprintCallable, BlueprintPure, Meta = (DevelopmentOnly))
	static void findFiles(const FString& pathToFolder, const FString& extension, TArray<FString>& files);

	/**
	* Find files recursively with given Extension
	*/
	UFUNCTION(Category = "AutomationToolchain|Files", BlueprintCallable, BlueprintPure, Meta = (DevelopmentOnly))
	static void findFilesRecursively(const FString& pathToFolder, const FString& extension, TArray<FString>& files);

	/**
	* Iterate folder and call Delegate for each file
	*/
	UFUNCTION(Category = "AutomationToolchain|Files", BlueprintCallable, Meta = (DevelopmentOnly))
	static void iterateFiles(const FString& pathToFolder, const FIterateFolderFunction& delegate);

	/**
	* Iterate folder and each subfolder and call Delegate for each file
	*/
	UFUNCTION(Category = "AutomationToolchain|Files", BlueprintCallable, Meta = (DevelopmentOnly))
	static void iterateFilesRecursively(const FString& pathToFolder, const FIterateFolderFunction& delegate);

	/**
	* Iterate folder and call Delegate for each file or folder
	*/
	UFUNCTION(Category = "AutomationToolchain|Files", BlueprintCallable, Meta = (DevelopmentOnly))
	static void iterateFolder(const FString& pathToFolder, const FIterateFolderFunction& delegate);

	/**
	* Iterate folder and each subfolder and call Delegate for each file or folder
	*/
	UFUNCTION(Category = "AutomationToolchain|Files", BlueprintCallable, Meta = (DevelopmentOnly))
	static void iterateFolderRecursive(const FString& pathToFolder, const FIterateFolderFunction& delegate);

	/**
	* Convert relative path to full path
	*/
	UFUNCTION(Category = "AutomationToolchain|Files", BlueprintCallable, BlueprintPure, Meta = (DevelopmentOnly))
	static FString getFullPath(const FString& path);

	/**
	* Delete folder recursively
	*/
	UFUNCTION(Category = "AutomationToolchain|Folders", BlueprintCallable, Meta = (DevelopmentOnly))
	static bool deleteFolder(const FString& pathToFolder);

	/**
	* Delete folders recursively
	*/
	UFUNCTION(Category = "AutomationToolchain|Folders", BlueprintCallable, Meta = (DevelopmentOnly))
	static TArray<bool> deleteFolders(const TArray<FString>& pathToFolders);

	/**
	* Delete empty folder
	*/
	UFUNCTION(Category = "AutomationToolchain|Folders", BlueprintCallable, Meta = (DevelopmentOnly))
	static bool deleteEmptyFolder(const FString& pathToFolder);

	/**
	* Delete empty folders
	*/
	UFUNCTION(Category = "AutomationToolchain|Folders", BlueprintCallable, Meta = (DevelopmentOnly))
	static TArray<bool> deleteEmptyFolders(const TArray<FString>& pathToFolders);

	/**
	* Get path to plugin folder
	*/
	UFUNCTION(Category = "AutomationToolchain|Utility", BlueprintCallable, BlueprintPure, Meta = (DevelopmentOnly))
	static FString getAutomationToolchainPluginFolderFullPath();

	/**
	* Get project name
	*/
	UFUNCTION(Category = "AutomationToolchain|Utility", BlueprintCallable, BlueprintPure, Meta = (DevelopmentOnly))
	static FString getProjectName();

	/**
	* Get project version
	*/
	UFUNCTION(Category = "AutomationToolchain|Utility", BlueprintCallable, BlueprintPure, Meta = (DevelopmentOnly))
	static const FString& getProjectVersion();

	/**
	* Append path
	*/
	UFUNCTION(Category = "AutomationToolchain|Utility", BlueprintCallable, BlueprintPure, Meta = (DevelopmentOnly))
	static FString appendPath(const FString& path, const FString& next);

	/**
	* Get path to StagedBuilds folder from settings file
	*/
	UFUNCTION(Category = "AutomationToolchain|Settings", BlueprintCallable, BlueprintPure, Meta = (DevelopmentOnly))
	static FString getPathToStagedBuildsFolder();

	/**
	* Is path to StagedBuilds relative to project folder
	*/
	UFUNCTION(Category = "AutomationToolchain|Settings", BlueprintCallable, BlueprintPure, Meta = (DevelopmentOnly))
	static bool getIsRelativePathToStagedBuilds();
};
