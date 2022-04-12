// Copyright (c) 2022 Use-your-imagination

#include "BaseDroppedAmmo.h"

#include "Constants/Constants.h"

void ABaseDroppedAmmo::onBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	this->pickup(Cast<ABaseDrone>(OtherActor));
}

void ABaseDroppedAmmo::pickup(TObjectPtr<ABaseDrone> drone)
{
	TObjectPtr<AInventory> inventory = Utility::getPlayerState(drone)->getInventory();
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

ABaseDroppedAmmo::ABaseDroppedAmmo()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = false;

	pickupArea = CreateDefaultSubobject<USphereComponent>("PickupArea");

	pickupArea->SetSphereRadius(1500.0f);

	pickupArea->OnComponentBeginOverlap.AddDynamic(this, &ABaseDroppedAmmo::onBeginOverlap);

	pickupArea->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	pickupArea->SetCollisionResponseToChannel(UConstants::droneChannel, ECollisionResponse::ECR_Overlap);

	SetRootComponent(pickupArea);

	mesh->SetupAttachment(pickupArea);
}
