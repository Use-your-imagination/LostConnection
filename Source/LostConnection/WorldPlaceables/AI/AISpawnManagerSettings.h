// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Info.h"

#include "AISpawnManagerSettings.generated.h"

USTRUCT(BlueprintType)
struct LOSTCONNECTION_API FWaveSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = Waves, EditDefaultsOnly, BlueprintReadOnly)
	int32 botsInWave;
};

UCLASS(BlueprintType, Blueprintable)
class LOSTCONNECTION_API AAISpawnManagerSettings : public AInfo
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = Waves, EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	TArray<FWaveSettings> waveSettings;

public:
	AAISpawnManagerSettings();

	UFUNCTION(Category = Waves, BlueprintCallable)
	const FWaveSettings& getWaveSettings(int32 waveNumber) const;

	int32 getWaveCount() const;

	~AAISpawnManagerSettings() = default;
};
