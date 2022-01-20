// Copyright (c) 2021 Use-your-imagination

#include "FakeAmmo.h"

#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"

#include "Constants/Constants.h"

AFakeAmmo::AFakeAmmo()
{	
	PrimaryActorTick.bCanEverTick = false;
	NetUpdateFrequency = UConstants::actorNetUpdateFrequency;
	bReplicates = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>("AmmoMesh");
	tracer = CreateDefaultSubobject<UNiagaraComponent>("Tracer");
	movement = CreateDefaultSubobject<UProjectileMovementComponent>("Movement");

	SetRootComponent(mesh);

	mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	movement->SetUpdatedComponent(mesh);

	movement->ProjectileGravityScale = 0.0f;

	movement->SetIsReplicated(true);

	tracer->SetupAttachment(mesh);
}

void AFakeAmmo::setSpeed(float speed)
{
	movement->InitialSpeed = speed;
	movement->MaxSpeed = speed;
}

UStaticMeshComponent* AFakeAmmo::getFakeAmmoMeshComponent() const
{
	return mesh;
}

UNiagaraComponent* AFakeAmmo::getFakeTracerComponent() const
{
	return tracer;
}
