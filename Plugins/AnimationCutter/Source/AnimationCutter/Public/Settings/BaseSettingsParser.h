// Copyright (c) 2022 Arkadiy Zakharov

#pragma once

#include "CoreMinimal.h"

#include "Dom/JsonObject.h"

class BaseSettingsParser
{
protected:
	TArray<FString> errors;

protected:
	virtual void parse(const TSharedPtr<FJsonObject>& settings) = 0;

public:
	BaseSettingsParser() = default;

	const TArray<FString>& getErrors() const;

	virtual ~BaseSettingsParser() = default;
};
