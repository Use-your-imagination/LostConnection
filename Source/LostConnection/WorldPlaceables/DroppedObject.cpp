// Copyright (c) 2021 Use Your Imagination

#include "DroppedObject.h"

void ADroppedObject::BeginPlay()
{
	Super::BeginPlay();
}

void ADroppedObject::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

ADroppedObject::ADroppedObject()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	vfx = CreateDefaultSubobject<UNiagaraComponent>("VFX");

	SetRootComponent(mesh);

	mesh->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);

	mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Block);

	vfx->SetupAttachment(mesh);
}

void ADroppedObject::setMesh(USkeletalMesh* mesh)
{
	this->mesh->SetSkeletalMesh(mesh);
}
