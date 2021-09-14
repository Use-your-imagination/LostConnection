#include "DroppedWeapon.h"

#include "Net/UnrealNetwork.h"

#include "Character/LostConnectionCharacter.h"

void ADroppedWeapon::Tick(float DeltaSeconds)
{
	if (HasAuthority())
	{
		weapon->reduceShootRemainigTime(DeltaSeconds);
	}
}

void ADroppedWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADroppedWeapon, weapon);
}

bool ADroppedWeapon::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool wroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	wroteSomething |= Channel->ReplicateSubobject(weapon, *Bunch, *RepFlags);

	return wroteSomething;
}

void ADroppedWeapon::onWeaponChange()
{
	if (weapon)
	{
		this->setMesh(weapon->getWeaponMesh());
	}
}

ADroppedWeapon::ADroppedWeapon()
{
	magazine = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Magazine"));

	magazine->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);

	magazine->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	magazine->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	magazine->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Block);
}

void ADroppedWeapon::setWeapon_Implementation(UBaseWeapon* newWeapon)
{
	weapon = DuplicateObject(newWeapon, nullptr);

	this->setMesh(weapon->getWeaponMesh());
}

UBaseWeapon* ADroppedWeapon::getWeapon()
{
	return weapon;
}

void ADroppedWeapon::setMesh(USkeletalMesh* mesh)
{
	this->mesh->SetSkeletalMesh(mesh);

	magazine->AttachToComponent(this->mesh, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false), "magazine");

	magazine->SetStaticMesh(weapon->getMagazineMesh());
}

void ADroppedWeapon::action(AActor* player)
{
	Cast<ALostConnectionCharacter>(player)->pickupWeapon(this);
}
