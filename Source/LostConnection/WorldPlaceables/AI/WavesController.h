// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"

#include "Utility/Enums.h"
#include "AI/AISpawnManager.h"

#include "WavesController.generated.h"

USTRUCT(BlueprintType)
struct LOSTCONNECTION_API FWaveSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = Waves, EditDefaultsOnly, BlueprintReadWrite)
	TMap<EBotType, int32> botsPerType;
};

UCLASS(BlueprintType, Blueprintable)
class LOSTCONNECTION_API AWavesController : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = Waves, EditDefaultsOnly, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	TArray<FWaveSettings> waveSettings;

private:
	AISpawnManager spawnManager;

protected:
	void BeginPlay() override;

public:
	AWavesController();

	UFUNCTION(Category = Waves, BlueprintCallable)
	const FWaveSettings& getWaveSettings(int32 waveNumber) const;

	void notify();

	int32 getWaveCount() const;

	AISpawnManager& getSpawnManager();

	~AWavesController() = default;
};
