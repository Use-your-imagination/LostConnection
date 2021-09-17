#include "Actionable.h"

#include "Characters/LostConnectionCharacter.h"

FString IActionable::getActionMessage() const
{
	return FText::FormatNamed(FText::FromStringTable("/Game/Text/Actions.Actions", "DefaultActionMessage"), TEXT("ActionHotkey"), FText::FromString(ALostConnectionCharacter::actionHotkey)).ToString();
}
