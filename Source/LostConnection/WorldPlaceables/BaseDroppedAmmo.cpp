// Copyright (c) 2022 Use-your-imagination

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
	lifetime(20.0f)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 1.0f;
	bReplicates = false;

	pickupArea = CreateDefaultSubobject<USphereComponent>("PickupArea");

	pickupArea->SetSphereRadius(1500.0f);

	pickupArea->OnComponentBeginOverlap.AddDynamic(this, &ABaseDroppedAmmo::onBeginOverlap);

	pickupArea->OnComponentEndOverlap.AddDynamic(this, &ABaseDroppedAmmo::onEndOverlap);

	pickupArea->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	pickupArea->SetCollisionResponseToChannel(UConstants::droneInteractiveChannel, ECollisionResponse::ECR_Overlap);

	SetRootComponent(pickupArea);

	mesh->SetupAttachment(pickupArea);
}

void ABaseDroppedAmmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	lifetime -= DeltaTime;

	if (lifetime <= 0.0f)
	{
		Destroy();
	}
	else
	{
		this->pickup();
	}
}
