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

private:
	UPROPERTY(Category = Overclocking, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float duration;

private:
	TArray<FFormatArgumentValue> getFormatArguments() const override;

public:
	UPlatinumOverclocking() = default;

	void uniqueAction_Implementation(AActor* caller) override;

	~UPlatinumOverclocking() = default;
};
