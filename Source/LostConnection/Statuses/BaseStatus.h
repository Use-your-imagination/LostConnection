#pragma once

#include "CoreMinimal.h"

#include "UObject/NoExportTypes.h"

#include "BaseStatus.generated.h"

UCLASS(BlueprintType, DefaultToInstanced)
class LOSTCONNECTION_API UBaseStatus : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = Statuses, EditDefaultsOnly, BlueprintReadOnly)
	FText name;

	UPROPERTY(Category = Statuses, EditDefaultsOnly, BlueprintReadOnly)
	FText description;

public:
	UBaseStatus();

	virtual ~UBaseStatus() = default;
};
