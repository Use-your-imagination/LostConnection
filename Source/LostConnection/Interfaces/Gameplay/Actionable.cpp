#include "Actionable.h"

#include "Kismet/GameplayStatics.h"

FString IActionable::getActionMessage() const
{
	return FText::FormatNamed(FText::FromStringTable("/Game/Text/Actions.Actions", "DefaultActionMessage"), TEXT("ActionHotkey"), FText::FromString("F")).ToString();
}
