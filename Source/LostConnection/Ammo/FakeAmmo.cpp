// Copyright (c) 2021 Use-your-imagination

#include "FakeAmmo.h"

#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"

#include "Constants/Constants.h"

AFakeAmmo::AFakeAmmo() :
	ammoSpeed(UConstants::ammoSpeed)
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

	movement->InitialSpeed = ammoSpeed;
	movement->MaxSpeed = ammoSpeed;

	tracer->SetupAttachment(mesh);
}

UStaticMeshComponent* AFakeAmmo::getFakeAmmoMeshComponent() const
{
	return mesh;
}
