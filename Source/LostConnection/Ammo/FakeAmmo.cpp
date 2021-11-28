// Copyright (c) 2021 Use-your-imagination

#include "FakeAmmo.h"

#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"

void AFakeAmmo::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFakeAmmo, movement);
}

bool AFakeAmmo::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool wroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	wroteSomething |= Channel->ReplicateSubobject(movement, *Bunch, *RepFlags);

	return wroteSomething;
}

AFakeAmmo::AFakeAmmo()
{
	PrimaryActorTick.bCanEverTick = false;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AmmoMesh"));
	tracer = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Tracer"));
	movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	NetUpdateFrequency = 60;

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
