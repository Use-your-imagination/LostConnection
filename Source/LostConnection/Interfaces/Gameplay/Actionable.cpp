#include "Actionable.h"

#include "Characters/BaseDrone.h"

FString IActionable::getActionMessage() const
{
	return FText::FormatNamed(FText::FromStringTable("/Game/Text/Actions.Actions", "DefaultActionMessage"), TEXT("ActionHotkey"), FText::FromString(ABaseDrone::actionHotkey)).ToString();
}
