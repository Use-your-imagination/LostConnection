// Copyright (c) 2022 Use Your Imagination

#include "AISpawnManagerSettings.h"

AAISpawnManagerSettings::AAISpawnManagerSettings()
{
	PrimaryActorTick.bCanEverTick = false;
}

const FWaveSettings& AAISpawnManagerSettings::getWaveSettings(int32 waveNumber) const
{
	return waveSettings[waveNumber];
}

int32 AAISpawnManagerSettings::getWaveCount() const
{
	return waveSettings.Num();
}
