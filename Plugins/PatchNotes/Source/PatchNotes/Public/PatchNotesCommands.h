// Copyright (c) 2022 Arkadiy Zakharov

#pragma once

#include "CoreMinimal.h"

#include "Framework/Commands/Commands.h"

class FPatchNotesCommands : public TCommands<FPatchNotesCommands>
{
public:
	TSharedPtr<FUICommandInfo> openPluginWindow;

public:
	FPatchNotesCommands();

	void RegisterCommands() override;
};
