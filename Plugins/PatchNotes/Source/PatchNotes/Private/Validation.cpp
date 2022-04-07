// Copyright (c) 2022 Arkadiy Zakharov

#include "Validation.h"

#include "PatchNotes.h"

Validation::Validation(const FPatchNotesModule& module) :
	module(module)
{

}

void Validation::checkConfigurationExist()
{
	FString pathToConfigurationFile = module.getPathToConfigurations() / module.getConfigurations()->getCurrentSelectionString() + TEXT(".json");

	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*pathToConfigurationFile))
	{
		errors.Append(TEXT("Configuration file doesn't exist")).Append(LINE_TERMINATOR);
	}
}

void Validation::checkConfiguration()
{
	if (module.getConfigurations()->getCurrentSelectionString().IsEmpty())
	{
		errors.Append(TEXT("Configuration can't be empty")).Append(LINE_TERMINATOR);
	}
}

void Validation::checkCategory()
{
	if (module.getCategories()->getCurrentSelectionString().IsEmpty())
	{
		errors.Append(TEXT("Category can't be empty")).Append(LINE_TERMINATOR);
	}
}

bool Validation::isErrorsFinded() const
{
	return StaticCast<bool>(errors.Len());
}

const FString& Validation::getErrors() const
{
	return errors;
}
