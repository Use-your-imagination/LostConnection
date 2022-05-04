// Copyright (c) 2022 Semyon Gritsenko

#include "AutomationToolchainCommands.h"

#define LOCTEXT_NAMESPACE "FAutomationToolchainModule"

FAutomationToolchainCommands::FAutomationToolchainCommands() :
	TCommands<FAutomationToolchainCommands>("AutomationToolchain", NSLOCTEXT("Contexts", "AutomationToolchain", "AutomationToolchain Plugin"), NAME_None, FAutomationToolchainStyle::getStyleSetName())
{

}

void FAutomationToolchainCommands::RegisterCommands()
{
	UI_COMMAND(openPluginWindow, "AutomationToolchain", "Open Automation Toolchain window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
