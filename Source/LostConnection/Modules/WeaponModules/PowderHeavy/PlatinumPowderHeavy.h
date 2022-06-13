// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "PowderHeavy.h"
#include "Interfaces/Modules/Descriptions/PlatinumModule.h"

#include "PlatinumPowderHeavy.generated.h"

UCLASS()
class LOSTCONNECTION_API UPlatinumPowderHeavy :
	public UPowderHeavy,
	public IPlatinumModule
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = PowderHeavy, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float duration;

private:
	TArray<FFormatArgumentValue> getFormatArguments() const override;
	
public:
	UPlatinumPowderHeavy() = default;

	void uniqueAction_Implementation(AActor* caller) override;

	~UPlatinumPowderHeavy() = default;
};
