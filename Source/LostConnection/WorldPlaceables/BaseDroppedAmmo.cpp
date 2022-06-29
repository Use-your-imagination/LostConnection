// Copyright (c) 2022 Use Your Imagination

#include "BaseDroppedAmmo.h"

#include "Constants/Constants.h"

void ABaseDroppedAmmo::onBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	drone = Cast<ABaseDrone>(OtherActor);

	this->pickup();
}

void ABaseDroppedAmmo::onEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	drone.Reset();
}

void ABaseDroppedAmmo::pickup()
{
	if (!drone.IsValid())
	{
		return;
	}

	TObjectPtr<AInventory> inventory = Utility::getPlayerState(drone.Get())->getInventory();
	int32 maxAmmo = inventory->getMaxAmmoCount(type);
	int32 spareAmmo = drone->getSpareAmmo(type);
	int32 neededAmmo = FMath::Min(currentAmount, maxAmmo - spareAmmo);

	drone->pickupAmmo(type, neededAmmo);

	currentAmount -= neededAmmo;

	if (!currentAmount)
	{
		Destroy();
	}
	else if (currentAmount < amount * 0.67f && currentAmount > amount * 0.33f)
	{
		mesh->SetSkeletalMesh(mid);
	}
	else if (currentAmount <= amount * 0.33f)
	{
		mesh->SetSkeletalMesh(empty);
	}
}

void ABaseDroppedAmmo::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	currentAmount = amount;
}

ABaseDroppedAmmo::ABaseDroppedAmmo() :
	lifetime(60.0f)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 1.0f;
	bReplicates = false;

	collisionBox = CreateDefaultSubobject<UBoxComponent>("CollisionBox");

	collisionBox->SetBoxExtent(FVector(25.0, 14.0, 12.5));

	collisionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	collisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	collisionBox->SetSimulatePhysics(true);

	collisionBox->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);

	SetRootComponent(collisionBox);

	pickupArea = CreateDefaultSubobject<USphereComponent>("PickupArea");

	pickupArea->SetupAttachment(collisionBox);

	pickupArea->SetSphereRadius(150.0f);

	pickupArea->OnComponentBeginOverlap.AddDynamic(this, &ABaseDroppedAmmo::onBeginOverlap);

	pickupArea->OnComponentEndOverlap.AddDynamic(this, &ABaseDroppedAmmo::onEndOverlap);

	pickupArea->SetCollisionObjectType(UConstants::droneInteractiveChannel);

	pickupArea->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	pickupArea->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	mesh->SetupAttachment(pickupArea);
}

void ABaseDroppedAmmo::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	lifetime -= DeltaSeconds;

	if (lifetime <= 0.0f)
	{
		Destroy();
	}
	else
	{
		this->pickup();
	}
}
