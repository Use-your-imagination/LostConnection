// Copyright (c) 2022 Arkadiy Zakharov

#pragma once

#include "CoreMinimal.h"

#define VALIDATION_CHECK() if (validation.isErrorsFinded()) { return; }

class PATCHNOTES_API Validation
{
private:
	const class FPatchNotesModule& module;
	FString errors;

public:
	Validation(const class FPatchNotesModule& module);

	void checkConfigurationExist();

	void checkConfiguration();

	void checkCategory();

	bool isErrorsFinded() const;

	const FString& getErrors() const;

	~Validation() = default;
};
