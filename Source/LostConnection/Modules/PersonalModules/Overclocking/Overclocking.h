// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Modules/Base/PersonalModules/BaseDamagePersonalModule.h"

#include "Overclocking.generated.h"

UCLASS()
class LOSTCONNECTION_API UOverclocking : public UBaseDamagePersonalModule
{
	GENERATED_BODY()

protected:
	virtual TArray<FFormatArgumentValue> getFormatArguments() const override;
	
public:
	UOverclocking() = default;

	bool applyCondition(const TObjectPtr<AActor>& caller) const override;

	EDamageAffecterType getDamageAffecterType() const override;

	~UOverclocking() = default;
};
