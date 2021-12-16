// Copyright (c) 2021 Use-your-imagination

#include "Constants.h"

const FString UConstants::projectVersion = "0.1.5.0";

FText UConstants::getProjectVersion()
{
	return FText::FromString(UConstants::projectVersion);
}
