#include "Reload.h"

void IReload::reload()
{
	this->reloadVisual();
	
	IReload::Execute_reloadEventVisual(Cast<UObject>(this));
}
