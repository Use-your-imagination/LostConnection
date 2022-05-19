// Copyright (c) 2022 Semyon Gritsenko

#include "ToolchainAction.h"

UToolchainAction::UToolchainAction() :
	continueToolchain(true)
{

}

bool UToolchainAction::getContinueToolchain() const
{
	return continueToolchain;
}
