#include "IrradiationStatus.h"

#include "Utility/Utility.h"

FString UIrradiationStatus::getStatusName() const
{
	return "Irradiation";
}

SIZE_T UIrradiationStatus::getActiveStatusesCount() const
{
	return Utility::countStatuses(target, StaticClass());
}
