// Copyright (c) 2021 Use-your-imagination

#include "Constants.h"

const FString UConstants::projectVersion = "0.1.7.0";

const FName UConstants::actionStringTablePath = "/Game/Text/Actions.Actions";

const FString UConstants::defaultActionMessageKey = "DefaultActionMessage";

const FString UConstants::actionHotkey = "ActionHotkey";

FText UConstants::getProjectVersion()
{
	return FText::FromString(UConstants::projectVersion);
}
