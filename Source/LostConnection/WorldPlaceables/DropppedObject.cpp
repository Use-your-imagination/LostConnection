// Fill out your copyright notice in the Description page of Project Settings.


#include "DropppedObject.h"

void ADropppedObject::BeginPlay()
{
	Super::BeginPlay();
}

ADropppedObject::ADropppedObject()
{
	PrimaryActorTick.bCanEverTick = false;

	collisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	vfx = CreateDefaultSubobject<UNiagaraComponent>(TEXT("VFX"));

	SetRootComponent(collisionBox);

	collisionBox->SetSimulatePhysics(true);

	collisionBox->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);

	collisionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	collisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	collisionBox->InitBoxExtent({ 5.0f, 5.0f, 5.0f });

	mesh->SetupAttachment(collisionBox);

	mesh->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);

	mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	vfx->SetupAttachment(mesh);
}

void ADropppedObject::setMesh(USkeletalMesh* mesh)
{
	this->mesh->SetSkeletalMesh(mesh);
}
