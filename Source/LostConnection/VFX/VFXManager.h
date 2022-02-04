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

private:
	AActor* owner;
	
public:
	UVFXManager() = default;

	void init(AActor* owner);

	void spawnVFX(const FVector& location, UNiagaraSystem* vfx);

	void spawnVFX(const FTransform& transform, UNiagaraSystem* vfx);

	~UVFXManager() = default;
};
