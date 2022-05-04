// Copyright (c) 2022 Semyon Gritsenko

#pragma once

#include "CoreMinimal.h"

#include "Framework/Commands/Commands.h"

#include "AutomationToolchainStyle.h"

class FAutomationToolchainCommands : public TCommands<FAutomationToolchainCommands>
{
public:
	TSharedPtr<FUICommandInfo> openPluginWindow;

public:
	FAutomationToolchainCommands();

	void RegisterCommands() override;
};