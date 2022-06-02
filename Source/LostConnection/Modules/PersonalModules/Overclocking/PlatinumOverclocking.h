// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Overclocking.h"
#include "Interfaces/Modules/Descriptions/PlatinumModule.h"

#include "PlatinumOverclocking.generated.h"

UCLASS()
class LOSTCONNECTION_API UPlatinumOverclocking :
	public UOverclocking,
	public IPlatinumModule
{
	GENERATED_BODY()
	
public:
	UPlatinumOverclocking() = default;

	void uniqueAction(TObjectPtr<AActor> caller) override;

	virtual ~UPlatinumOverclocking() = default;
};
