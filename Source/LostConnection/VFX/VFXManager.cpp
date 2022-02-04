// Copyright (c) 2022 Use-your-imagination

#include "VFXManager.h"

#include "NiagaraFunctionLibrary.h"

void UVFXManager::init(AActor* owner)
{
	this->owner = owner;
}

void UVFXManager::spawnVFX(const FVector& location, UNiagaraSystem* vfx)
{
	this->spawnVFX(FTransform(FRotator::ZeroRotator, location), vfx);
}

void UVFXManager::spawnVFX(const FTransform& transform, UNiagaraSystem* vfx)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation
	(
		owner->GetWorld(),
		vfx,
		transform.GetLocation(),
		transform.GetRotation().Rotator(),
		transform.GetScale3D(),
		true,
		true,
		ENCPoolMethod::AutoRelease
	);
}
