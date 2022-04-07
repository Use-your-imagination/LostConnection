// Copyright (c) 2022 Arkadiy Zakharov

#pragma once

#include "CoreMinimal.h"

#include "Dialogs/CustomDialog.h"
#include "Validation.h"

class PATCHNOTES_API BaseDialog
{
private:
	const class FPatchNotesModule& module;

protected:
	virtual void collectData(const class FPatchNotesModule& module, Validation& validation) = 0;

	virtual TSharedPtr<SCustomDialog> createDialog() = 0;

public:
	BaseDialog(const class FPatchNotesModule& module);

	void execute();

	virtual ~BaseDialog() = default;
};
