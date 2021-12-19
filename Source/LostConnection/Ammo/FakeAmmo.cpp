// Copyright (c) 2021 Use-your-imagination

#include "FakeAmmo.h"

#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"

#include "Constants/Constants.h"

AFakeAmmo::AFakeAmmo()
{	
	PrimaryActorTick.bCanEverTick = false;

	NetUpdateFrequency = UConstants::actorNetUpdateFrequency;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AmmoMesh"));
	tracer = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Tracer"));
	movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));

	SetRootComponent(mesh);

	mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	movement->SetUpdatedComponent(mesh);

	movement->ProjectileGravityScale = 0.0f;

	movement->SetIsReplicated(true);

	movement->InitialSpeed = 5200.0f;
	movement->MaxSpeed = 5200.0f;

	tracer->SetupAttachment(mesh);
}

void AFakeAmmo::copyAmmo(ABaseAmmo* ammo)
{
	mesh->SetStaticMesh(ammo->mesh->GetStaticMesh());

	tracer->SetAsset(ammo->tracerAsset);

	brokenAmmoMesh = ammo->brokenAmmoMesh;
}

void AFakeAmmo::deactivateTracer()
{
	tracer->Deactivate();
}

UStaticMeshComponent* AFakeAmmo::getFakeAmmoMeshComponent() const
{
	return mesh;
}
