#include "Shoot.h"

void IShoot::shoot()
{
	this->shootVisual();

	IShoot::Execute_shootEventVisual(Cast<UObject>(this));
}
