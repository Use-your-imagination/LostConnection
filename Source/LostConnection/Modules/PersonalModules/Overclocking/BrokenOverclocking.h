// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Overclocking.h"
#include "Interfaces/Modules/Descriptions/BrokenModule.h"

#include "BrokenOverclocking.generated.h"

UCLASS()
class LOSTCONNECTION_API UBrokenOverclocking :
	public UOverclocking,
	public IBrokenModule
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = Module, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float breakPercent;
	
public:
	UBrokenOverclocking() = default;

	bool applyCondition(TObjectPtr<AActor> caller) const override;

	virtual ~UBrokenOverclocking() = default;
};
