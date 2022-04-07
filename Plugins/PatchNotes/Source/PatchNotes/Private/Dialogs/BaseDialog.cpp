// Copyright (c) 2022 Arkadiy Zakharov

#include "Dialogs/BaseDialog.h"

#include "PatchNotes.h"

BaseDialog::BaseDialog(const FPatchNotesModule& module) :
	module(module)
{

}

void BaseDialog::execute()
{
	Validation validation(module);

	this->collectData(module, validation);

	if (validation.isErrorsFinded())
	{
		FMessageDialog::Open(EAppMsgType::Type::Ok, FText::FromString(validation.getErrors()));

		return;
	}

	this->createDialog()->ShowModal();
}
