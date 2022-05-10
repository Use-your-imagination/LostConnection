// Copyright (c) 2022 Use Your Imagination

#include "VFXManager.h"

#include "NiagaraFunctionLibrary.h"

void UVFXManager::spawnVFX(UWorld* world, const FVector& location, UNiagaraSystem* vfx)
{
	this->spawnVFX(world, FTransform(FRotator::ZeroRotator, location), vfx);
}

void UVFXManager::spawnVFX(UWorld* world, const FTransform& transform, UNiagaraSystem* vfx)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation
	(
		world,
		vfx,
		transform.GetLocation(),
		transform.GetRotation().Rotator(),
		transform.GetScale3D(),
		true,
		true,
		ENCPoolMethod::AutoRelease
	);
}
