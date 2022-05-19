// Copyright (c) 2022 Semyon Gritsenko

#include "JSONLibrary.h"

#include "Serialization/JsonSerializer.h"

template<typename JsonT, typename T>
static FJsonDataObject& setArray(const FString& fieldName, const TArray<T>& values, FJsonDataObject& jsonObject)
{
	TArray<TSharedPtr<FJsonValue>> result;

	result.Reserve(values.Num());

	for (const T& value : values)
	{
		result.Add(MakeShared<JsonT>(value));
	}

	jsonObject.data->SetArrayField(fieldName, result);

	return jsonObject;
}

FJsonDataObject::FJsonDataObject(const TSharedPtr<FJsonObject>& jsonObject) :
	data(jsonObject)
{

}

FString UJsonLibrary::Conv_JsonDataObjectToString(const FJsonDataObject& InJsonDataObject)
{
	FString result;

	if (InJsonDataObject.data.IsValid())
	{
		FJsonSerializer::Serialize(InJsonDataObject.data.ToSharedRef(), TJsonWriterFactory<>::Create(&result));
	}

	return result;
}

FJsonDataObject UJsonLibrary::parseJson(const FString& jsonData, bool& result)
{
	FJsonDataObject json;

	result = FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(jsonData), json.data);

	return json;
}

FJsonDataObject UJsonLibrary::parseJsonFile(const FString& pathToFile, bool& result)
{
	FString jsonData;

	if (!UAutomationToolchainLibrary::readFile(pathToFile, jsonData))
	{
		result = false;

		return FJsonDataObject();
	}

	return UJsonLibrary::parseJson(jsonData, result);
}

#pragma region Set
FJsonDataObject& UJsonLibrary::setJsonBoolean(const FString& fieldName, bool value, FJsonDataObject& jsonObject)
{
	jsonObject.data->SetBoolField(fieldName, value);

	return jsonObject;
}

FJsonDataObject& UJsonLibrary::setJsonInteger(const FString& fieldName, int32 value, FJsonDataObject& jsonObject)
{
	jsonObject.data->SetNumberField(fieldName, StaticCast<double>(value));

	return jsonObject;
}

FJsonDataObject& UJsonLibrary::setJsonFloat(const FString& fieldName, float value, FJsonDataObject& jsonObject)
{
	jsonObject.data->SetNumberField(fieldName, StaticCast<double>(value));

	return jsonObject;
}

FJsonDataObject& UJsonLibrary::setJsonString(const FString& fieldName, const FString& value, FJsonDataObject& jsonObject)
{
	jsonObject.data->SetStringField(fieldName, value);

	return jsonObject;
}

FJsonDataObject& UJsonLibrary::setJsonObject(const FString& fieldName, const FJsonDataObject& value, FJsonDataObject& jsonObject)
{
	jsonObject.data->SetObjectField(fieldName, value.data);

	return jsonObject;
}

FJsonDataObject& UJsonLibrary::setJsonBooleanArray(const FString& fieldName, const TArray<bool>& values, FJsonDataObject& jsonObject)
{
	return setArray<FJsonValueBoolean>(fieldName, values, jsonObject);
}

FJsonDataObject& UJsonLibrary::setJsonIntegerArray(const FString& fieldName, const TArray<int32>& values, FJsonDataObject& jsonObject)
{
	return setArray<FJsonValueNumber>(fieldName, values, jsonObject);
}

FJsonDataObject& UJsonLibrary::setJsonFloatArray(const FString& fieldName, const TArray<float>& values, FJsonDataObject& jsonObject)
{
	return setArray<FJsonValueNumber>(fieldName, values, jsonObject);
}

FJsonDataObject& UJsonLibrary::setJsonStringArray(const FString& fieldName, const TArray<FString>& values, FJsonDataObject& jsonObject)
{
	return setArray<FJsonValueString>(fieldName, values, jsonObject);
}

FJsonDataObject& UJsonLibrary::setJsonObjectArray(const FString& fieldName, const TArray<FJsonDataObject>& values, FJsonDataObject& jsonObject)
{
	TArray<TSharedPtr<FJsonValue>> result;

	result.Reserve(values.Num());

	for (const FJsonDataObject& value : values)
	{
		result.Add(MakeShared<FJsonValueObject>(value.data));
	}

	jsonObject.data->SetArrayField(fieldName, result);

	return jsonObject;
}
#pragma endregion

#pragma region Get
bool UJsonLibrary::getJsonBoolean(const FString& fieldName, const FJsonDataObject& jsonObject)
{
	return jsonObject.data->GetBoolField(fieldName);
}

int32 UJsonLibrary::getJsonInteger(const FString& fieldName, const FJsonDataObject& jsonObject)
{
	return jsonObject.data->GetIntegerField(fieldName);
}

float UJsonLibrary::getJsonNumber(const FString& fieldName, const FJsonDataObject& jsonObject)
{
	return StaticCast<float>(jsonObject.data->GetNumberField(fieldName));
}

FString UJsonLibrary::getJsonString(const FString& fieldName, const FJsonDataObject& jsonObject)
{
	return jsonObject.data->GetStringField(fieldName);
}

FJsonDataObject UJsonLibrary::getJsonObject(const FString& fieldName, const FJsonDataObject& jsonObject)
{
	return FJsonDataObject(jsonObject.data->GetObjectField(fieldName));
}

TArray<bool> UJsonLibrary::getJsonBooleanArray(const FString& fieldName, const FJsonDataObject& jsonObject)
{
	TArray<TSharedPtr<FJsonValue>> tem = jsonObject.data->GetArrayField(fieldName);
	TArray<bool> result;

	result.Reserve(tem.Num());

	for (const TSharedPtr<FJsonValue>& value : tem)
	{
		result.Add(value->AsBool());
	}

	return result;
}

TArray<int32> UJsonLibrary::getJsonIntegerArray(const FString& fieldName, const FJsonDataObject& jsonObject)
{
	TArray<TSharedPtr<FJsonValue>> tem = jsonObject.data->GetArrayField(fieldName);
	TArray<int32> result;

	result.Reserve(tem.Num());

	for (const TSharedPtr<FJsonValue>& value : tem)
	{
		result.Add(StaticCast<int32>(value->AsNumber()));
	}

	return result;
}

TArray<float> UJsonLibrary::getJsonNumberArray(const FString& fieldName, const FJsonDataObject& jsonObject)
{
	TArray<TSharedPtr<FJsonValue>> tem = jsonObject.data->GetArrayField(fieldName);
	TArray<float> result;

	result.Reserve(tem.Num());

	for (const TSharedPtr<FJsonValue>& value : tem)
	{
		result.Add(StaticCast<float>(value->AsNumber()));
	}

	return result;
}

TArray<FString> UJsonLibrary::getJsonStringArray(const FString& fieldName, const FJsonDataObject& jsonObject)
{
	TArray<FString> result;

	jsonObject.data->TryGetStringArrayField(fieldName, result);

	return result;
}

TArray<FJsonDataObject> UJsonLibrary::getJsonObjectArray(const FString& fieldName, const FJsonDataObject& jsonObject)
{
	TArray<TSharedPtr<FJsonValue>> tem = jsonObject.data->GetArrayField(fieldName);
	TArray<FJsonDataObject> result;

	result.Reserve(tem.Num());

	for (const TSharedPtr<FJsonValue>& value : tem)
	{
		result.Emplace(value->AsObject());
	}

	return result;
}
#pragma endregion

#pragma region TryGet
bool UJsonLibrary::tryGetJsonBoolean(const FString& fieldName, const FJsonDataObject& jsonObject, bool& result)
{
	bool out;

	result = jsonObject.data->TryGetBoolField(fieldName, out);

	return out;
}

int32 UJsonLibrary::tryGetJsonInteger(const FString& fieldName, const FJsonDataObject& jsonObject, bool& result)
{
	int32 out;

	result = jsonObject.data->TryGetNumberField(fieldName, out);

	return out;
}

float UJsonLibrary::tryGetJsonNumber(const FString& fieldName, const FJsonDataObject& jsonObject, bool& result)
{
	float out;

	result = jsonObject.data->TryGetNumberField(fieldName, out);

	return out;
}

FString UJsonLibrary::tryGetJsonString(const FString& fieldName, const FJsonDataObject& jsonObject, bool& result)
{
	FString out;

	result = jsonObject.data->TryGetStringField(fieldName, out);

	return out;
}

FJsonDataObject UJsonLibrary::tryGetJsonObject(const FString& fieldName, const FJsonDataObject& jsonObject, bool& result)
{
	const TSharedPtr<FJsonObject>* out = nullptr;

	result = jsonObject.data->TryGetObjectField(fieldName, out);

	if (out)
	{
		return FJsonDataObject(*out);
	}

	return FJsonDataObject();
}

TArray<bool> UJsonLibrary::tryGetJsonBooleanArray(const FString& fieldName, const FJsonDataObject& jsonObject, bool& result)
{
	TArray<TSharedPtr<FJsonValue>> tem = jsonObject.data->GetArrayField(fieldName);
	TArray<bool> out;

	out.Reserve(tem.Num());

	for (const TSharedPtr<FJsonValue>& value : tem)
	{
		bool temValue;

		if (!value->TryGetBool(temValue))
		{
			break;
		}

		out.Add(temValue);
	}

	result = out.Num() == tem.Num();

	return out;
}

TArray<int32> UJsonLibrary::tryGetJsonIntegerArray(const FString& fieldName, const FJsonDataObject& jsonObject, bool& result)
{
	TArray<TSharedPtr<FJsonValue>> tem = jsonObject.data->GetArrayField(fieldName);
	TArray<int32> out;

	out.Reserve(tem.Num());

	for (const TSharedPtr<FJsonValue>& value : tem)
	{
		int32 temValue;

		if (!value->TryGetNumber(temValue))
		{
			break;
		}

		out.Add(temValue);
	}

	result = out.Num() == tem.Num();

	return out;
}

TArray<float> UJsonLibrary::tryGetJsonNumberArray(const FString& fieldName, const FJsonDataObject& jsonObject, bool& result)
{
	TArray<TSharedPtr<FJsonValue>> tem = jsonObject.data->GetArrayField(fieldName);
	TArray<float> out;

	out.Reserve(tem.Num());

	for (const TSharedPtr<FJsonValue>& value : tem)
	{
		float temValue;

		if (!value->TryGetNumber(temValue))
		{
			break;
		}

		out.Add(temValue);
	}

	result = out.Num() == tem.Num();

	return out;
}

TArray<FString> UJsonLibrary::tryGetJsonStringArray(const FString& fieldName, const FJsonDataObject& jsonObject, bool& result)
{
	TArray<FString> out;

	result = jsonObject.data->TryGetStringArrayField(fieldName, out);

	return out;
}

TArray<FJsonDataObject> UJsonLibrary::tryGetJsonObjectArray(const FString& fieldName, const FJsonDataObject& jsonObject, bool& result)
{
	TArray<TSharedPtr<FJsonValue>> tem = jsonObject.data->GetArrayField(fieldName);
	TArray<FJsonDataObject> out;

	out.Reserve(tem.Num());

	for (const TSharedPtr<FJsonValue>& value : tem)
	{
		const TSharedPtr<FJsonObject>* temValue = nullptr;

		if (!value->TryGetObject(temValue))
		{
			break;
		}

		out.Emplace(*temValue);
	}

	result = out.Num() == tem.Num();

	return out;
}
#pragma endregion
