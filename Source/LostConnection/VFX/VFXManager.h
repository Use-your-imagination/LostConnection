// Copyright (c) 2022 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/NoExportTypes.h"
#include "NiagaraSystem.h"

#include "VFXManager.generated.h"

#pragma warning(disable: 4458)

UCLASS()
class LOSTCONNECTION_API UVFXManager : public UObject
{
	GENERATED_BODY()

public:
	UVFXManager() = default;

	void spawnVFX(UWorld* world, const FVector& location, UNiagaraSystem* vfx);

	void spawnVFX(UWorld* world, const FTransform& transform, UNiagaraSystem* vfx);

	~UVFXManager() = default;
};
