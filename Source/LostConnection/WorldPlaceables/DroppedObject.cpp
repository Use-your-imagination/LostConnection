// Fill out your copyright notice in the Description page of Project Settings.


#include "DroppedObject.h"

void ADroppedObject::BeginPlay()
{
	Super::BeginPlay();
}

void ADroppedObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

ADroppedObject::ADroppedObject()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	vfx = CreateDefaultSubobject<UNiagaraComponent>(TEXT("VFX"));

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

void ADroppedObject::action(AActor* player)
{
	
}
