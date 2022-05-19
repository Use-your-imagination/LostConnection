// Copyright (c) 2022 Semyon Gritsenko

#pragma once

#include "CoreMinimal.h"

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Dom/JsonObject.h"

#include "AutomationToolchainLibrary.h"

#include "JsonLibrary.generated.h"

USTRUCT(BlueprintType)
struct AUTOMATIONTOOLCHAIN_API FJsonDataObject
{
	GENERATED_BODY()

public:
	TSharedPtr<FJsonObject> data;

public:
	FJsonDataObject() = default;

	FJsonDataObject(const TSharedPtr<FJsonObject>& jsonObject);

	~FJsonDataObject() = default;
};

UCLASS()
class AUTOMATIONTOOLCHAIN_API UJsonLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/**
	* Converts a Json Data Object to a string
	*/
	UFUNCTION(Category = "AutomationToolchain|Json", BlueprintCallable, BlueprintPure, Meta = (DevelopmentOnly, DisplayName = "To String (JsonDataObject)", CompactNodeTitle = "->", BlueprintAutocast))
	static FString Conv_JsonDataObjectToString(const FJsonDataObject& InJsonDataObject);

	/**
	* Parse JSON data
	*/
	UFUNCTION(Category = "AutomationToolchain|Json", BlueprintCallable, BlueprintPure, Meta = (DevelopmentOnly, CompactNodeTitle = "Parse JSON"))
	static FJsonDataObject parseJson(const FString& jsonData, bool& result);

	/**
	* Parse JSON file
	*/
	UFUNCTION(Category = "AutomationToolchain|Json", BlueprintCallable, BlueprintPure, Meta = (DevelopmentOnly, CompactNodeTitle = "Parse JSON File"))
	static FJsonDataObject parseJsonFile(const FString& pathToFile, bool& result);

#pragma region Set
	/**
	* Set boolean
	* @return Modified JsonDataObject
	*/
	UFUNCTION(Category = "AutomationToolchain|Json", BlueprintCallable, Meta = (DevelopmentOnly, CompactNodeTitle = "Set"))
	static FJsonDataObject& setJsonBoolean(const FString& fieldName, bool value, UPARAM(ref) FJsonDataObject& jsonObject);

	/**
	* Set integer
	* @return Modified JsonDataObject
	*/
	UFUNCTION(Category = "AutomationToolchain|Json", BlueprintCallable, Meta = (DevelopmentOnly, CompactNodeTitle = "Set"))
	static FJsonDataObject& setJsonInteger(const FString& fieldName, int32 value, UPARAM(ref) FJsonDataObject& jsonObject);

	/**
	* Set float
	* @return Modified JsonDataObject
	*/
	UFUNCTION(Category = "AutomationToolchain|Json", BlueprintCallable, Meta = (DevelopmentOnly, CompactNodeTitle = "Set"))
	static FJsonDataObject& setJsonFloat(const FString& fieldName, float value, UPARAM(ref) FJsonDataObject& jsonObject);

	/**
	* Set string
	* @return Modified JsonDataObject
	*/
	UFUNCTION(Category = "AutomationToolchain|Json", BlueprintCallable, Meta = (DevelopmentOnly, CompactNodeTitle = "Set"))
	static FJsonDataObject& setJsonString(const FString& fieldName, const FString& value, UPARAM(ref) FJsonDataObject& jsonObject);

	/**
	* Set JsonDataObject
	* @return Modified JsonDataObject
	*/
	UFUNCTION(Category = "AutomationToolchain|Json", BlueprintCallable, Meta = (DevelopmentOnly, CompactNodeTitle = "Set"))
	static FJsonDataObject& setJsonObject(const FString& fieldName, const FJsonDataObject& value, UPARAM(ref) FJsonDataObject& jsonObject);

	/**
	* Set boolean array
	* @return Modified JsonDataObject
	*/
	UFUNCTION(Category = "AutomationToolchain|Json", BlueprintCallable, Meta = (DevelopmentOnly, CompactNodeTitle = "Set"))
	static FJsonDataObject& setJsonBooleanArray(const FString& fieldName, const TArray<bool>& values, UPARAM(ref) FJsonDataObject& jsonObject);

	/**
	* Set integer array
	* @return Modified JsonDataObject
	*/
	UFUNCTION(Category = "AutomationToolchain|Json", BlueprintCallable, Meta = (DevelopmentOnly, CompactNodeTitle = "Set"))
	static FJsonDataObject& setJsonIntegerArray(const FString& fieldName, const TArray<int32>& values, UPARAM(ref) FJsonDataObject& jsonObject);

	/**
	* Set float array
	* @return Modified JsonDataObject
	*/
	UFUNCTION(Category = "AutomationToolchain|Json", BlueprintCallable, Meta = (DevelopmentOnly, CompactNodeTitle = "Set"))
	static FJsonDataObject& setJsonFloatArray(const FString& fieldName, const TArray<float>& values, UPARAM(ref) FJsonDataObject& jsonObject);

	/**
	* Set string array
	* @return Modified JsonDataObject
	*/
	UFUNCTION(Category = "AutomationToolchain|Json", BlueprintCallable, Meta = (DevelopmentOnly, CompactNodeTitle = "Set"))
	static FJsonDataObject& setJsonStringArray(const FString& fieldName, const TArray<FString>& values, UPARAM(ref) FJsonDataObject& jsonObject);

	/**
	* Set JsonDataObject array
	* @return Modified JsonDataObject
	*/
	UFUNCTION(Category = "AutomationToolchain|Json", BlueprintCallable, Meta = (DevelopmentOnly, CompactNodeTitle = "Set"))
	static FJsonDataObject& setJsonObjectArray(const FString& fieldName, const TArray<FJsonDataObject>& values, UPARAM(ref) FJsonDataObject& jsonObject);
#pragma endregion

#pragma region Get
	/**
	* Get boolean from JsonDataObject
	*/
	UFUNCTION(Category = "AutomationToolchain|Json", BlueprintCallable, BlueprintPure, Meta = (DevelopmentOnly, CompactNodeTitle = "Get"))
	static bool getJsonBoolean(const FString& fieldName, const FJsonDataObject& jsonObject);

	/**
	* Get integer from JsonDataObject
	*/
	UFUNCTION(Category = "AutomationToolchain|Json", BlueprintCallable, BlueprintPure, Meta = (DevelopmentOnly, CompactNodeTitle = "Get"))
	static int32 getJsonInteger(const FString& fieldName, const FJsonDataObject& jsonObject);

	/**
	* Get float from JsonDataObject
	*/
	UFUNCTION(Category = "AutomationToolchain|Json", BlueprintCallable, BlueprintPure, Meta = (DevelopmentOnly, CompactNodeTitle = "Get"))
	static float getJsonNumber(const FString& fieldName, const FJsonDataObject& jsonObject);

	/**
	* Get string from JsonDataObject
	*/
	UFUNCTION(Category = "AutomationToolchain|Json", BlueprintCallable, BlueprintPure, Meta = (DevelopmentOnly, CompactNodeTitle = "Get"))
	static FString getJsonString(const FString& fieldName, const FJsonDataObject& jsonObject);

	/**
	* Get JsonDataObject from JsonDataObject
	*/
	UFUNCTION(Category = "AutomationToolchain|Json", BlueprintCallable, BlueprintPure, Meta = (DevelopmentOnly, CompactNodeTitle = "Get"))
	static FJsonDataObject getJsonObject(const FString& fieldName, const FJsonDataObject& jsonObject);

	/**
	* Get boolean array from JsonDataObject
	*/
	UFUNCTION(Category = "AutomationToolchain|Json", BlueprintCallable, BlueprintPure, Meta = (DevelopmentOnly, CompactNodeTitle = "Get"))
	static TArray<bool> getJsonBooleanArray(const FString& fieldName, const FJsonDataObject& jsonObject);

	/**
	* Get integer array from JsonDataObject
	*/
	UFUNCTION(Category = "AutomationToolchain|Json", BlueprintCallable, BlueprintPure, Meta = (DevelopmentOnly, CompactNodeTitle = "Get"))
	static TArray<int32> getJsonIntegerArray(const FString& fieldName, const FJsonDataObject& jsonObject);

	/**
	* Get float array from JsonDataObject
	*/
	UFUNCTION(Category = "AutomationToolchain|Json", BlueprintCallable, BlueprintPure, Meta = (DevelopmentOnly, CompactNodeTitle = "Get"))
	static TArray<float> getJsonNumberArray(const FString& fieldName, const FJsonDataObject& jsonObject);

	/**
	* Get string array from JsonDataObject
	*/
	UFUNCTION(Category = "AutomationToolchain|Json", BlueprintCallable, BlueprintPure, Meta = (DevelopmentOnly, CompactNodeTitle = "Get"))
	static TArray<FString> getJsonStringArray(const FString& fieldName, const FJsonDataObject& jsonObject);

	/**
	* Get JsonDataObject array from JsonDataObject
	*/
	UFUNCTION(Category = "AutomationToolchain|Json", BlueprintCallable, BlueprintPure, Meta = (DevelopmentOnly, CompactNodeTitle = "Get"))
	static TArray<FJsonDataObject> getJsonObjectArray(const FString& fieldName, const FJsonDataObject& jsonObject);
#pragma endregion

#pragma region TryGet
	/**
	* Try to get boolean from JsonDataObject
	*/
	UFUNCTION(Category = "AutomationToolchain|Json", BlueprintCallable, BlueprintPure, Meta = (DevelopmentOnly, CompactNodeTitle = "Try Get"))
	static bool tryGetJsonBoolean(const FString& fieldName, const FJsonDataObject& jsonObject, bool& result);

	/**
	* Try to get integer from JsonDataObject
	*/
	UFUNCTION(Category = "AutomationToolchain|Json", BlueprintCallable, BlueprintPure, Meta = (DevelopmentOnly, CompactNodeTitle = "Try Get"))
	static int32 tryGetJsonInteger(const FString& fieldName, const FJsonDataObject& jsonObject, bool& result);

	/**
	* Try to get float from JsonDataObject
	*/
	UFUNCTION(Category = "AutomationToolchain|Json", BlueprintCallable, BlueprintPure, Meta = (DevelopmentOnly, CompactNodeTitle = "Try Get"))
	static float tryGetJsonNumber(const FString& fieldName, const FJsonDataObject& jsonObject, bool& result);

	/**
	* Try to get string from JsonDataObject
	*/
	UFUNCTION(Category = "AutomationToolchain|Json", BlueprintCallable, BlueprintPure, Meta = (DevelopmentOnly, CompactNodeTitle = "Try Get"))
	static FString tryGetJsonString(const FString& fieldName, const FJsonDataObject& jsonObject, bool& result);

	/**
	* Try to get JsonDataObject from JsonDataObject
	*/
	UFUNCTION(Category = "AutomationToolchain|Json", BlueprintCallable, BlueprintPure, Meta = (DevelopmentOnly, CompactNodeTitle = "Try Get"))
	static FJsonDataObject tryGetJsonObject(const FString& fieldName, const FJsonDataObject& jsonObject, bool& result);

	/**
	* Try to get boolean array from JsonDataObject
	*/
	UFUNCTION(Category = "AutomationToolchain|Json", BlueprintCallable, BlueprintPure, Meta = (DevelopmentOnly, CompactNodeTitle = "Try Get"))
	static TArray<bool> tryGetJsonBooleanArray(const FString& fieldName, const FJsonDataObject& jsonObject, bool& result);

	/**
	* Try to get integer array from JsonDataObject
	*/
	UFUNCTION(Category = "AutomationToolchain|Json", BlueprintCallable, BlueprintPure, Meta = (DevelopmentOnly, CompactNodeTitle = "Try Get"))
	static TArray<int32> tryGetJsonIntegerArray(const FString& fieldName, const FJsonDataObject& jsonObject, bool& result);

	/**
	* Try to get float array from JsonDataObject
	*/
	UFUNCTION(Category = "AutomationToolchain|Json", BlueprintCallable, BlueprintPure, Meta = (DevelopmentOnly, CompactNodeTitle = "Try Get"))
	static TArray<float> tryGetJsonNumberArray(const FString& fieldName, const FJsonDataObject& jsonObject, bool& result);

	/**
	* Try to get string array from JsonDataObject
	*/
	UFUNCTION(Category = "AutomationToolchain|Json", BlueprintCallable, BlueprintPure, Meta = (DevelopmentOnly, CompactNodeTitle = "Try Get"))
	static TArray<FString> tryGetJsonStringArray(const FString& fieldName, const FJsonDataObject& jsonObject, bool& result);

	/**
	* Try to get JsonDataObject array from JsonDataObject
	*/
	UFUNCTION(Category = "AutomationToolchain|Json", BlueprintCallable, BlueprintPure, Meta = (DevelopmentOnly, CompactNodeTitle = "Try Get"))
	static TArray<FJsonDataObject> tryGetJsonObjectArray(const FString& fieldName, const FJsonDataObject& jsonObject, bool& result);
#pragma endregion
};
