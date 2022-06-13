// Copyright (c) 2022 Arkadiy Zakharov

#pragma once

#include "Modules/ModuleManager.h"

class FBlueprintsAlgorithmsModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;

	virtual void ShutdownModule() override;
};
