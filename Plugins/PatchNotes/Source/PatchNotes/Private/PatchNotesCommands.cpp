// Copyright (c) 2022 Arkadiy Zakharov

#include "PatchNotesCommands.h"

#include "PatchNotesStyle.h"

#define LOCTEXT_NAMESPACE "FPatchNotesModule"

FPatchNotesCommands::FPatchNotesCommands() :
	TCommands<FPatchNotesCommands>(TEXT("PatchNotes"), NSLOCTEXT("Contexts", "PatchNotes", "PatchNotes Plugin"), NAME_None, FPatchNotesStyle::getStyleSetName())
{

}

void FPatchNotesCommands::RegisterCommands()
{
	UI_COMMAND(openPluginWindow, "Patch Notes", "Open Patch Notes window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
