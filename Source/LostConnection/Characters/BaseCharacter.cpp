#include "BaseCharacter.h"

#include <algorithm>

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"

#include "Utility/MultiplayerUtility.h"

#pragma warning(disable: 4458)

using namespace std;

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!isDead && currentHealth <= 0.0f)
	{
		if (HasAuthority())
		{
			MultiplayerUtility::runOnServerReliableWithMulticast(this, "death");
		}
	}

	if (defaultWeaponSlot)
	{
		if (HasAuthority())
		{
			defaultWeaponSlot->reduceShootRemainigTime(DeltaTime);
		}
	}
}

void ABaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseCharacter, health);

	DOREPLIFETIME(ABaseCharacter, currentHealth);

	DOREPLIFETIME(ABaseCharacter, isAlly);

	DOREPLIFETIME(ABaseCharacter, isDead);

	DOREPLIFETIME(ABaseCharacter, spareAmmo);

	DOREPLIFETIME(ABaseCharacter, currentWeapon);

	DOREPLIFETIME(ABaseCharacter, defaultWeaponSlot);
}

bool ABaseCharacter::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool wroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	wroteSomething |= Channel->ReplicateSubobject(defaultWeaponSlot, *Bunch, *RepFlags);

	return wroteSomething;
}

void ABaseCharacter::onCurrentWeaponChange()
{
	this->updateWeaponMesh();
}

void ABaseCharacter::updateWeaponMesh()
{
	if (currentWeapon)
	{
		currentWeaponMesh->SetSkeletalMesh(currentWeapon->getWeaponMesh());

		magazine->AttachToComponent(currentWeaponMesh, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false), "magazine");

		magazine->SetStaticMesh(currentWeapon->getMagazineMesh());
	}
	else
	{
		magazine->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepRelative, false));

		magazine->SetStaticMesh(nullptr);

		currentWeaponMesh->SetSkeletalMesh(nullptr);
	}
}

void ABaseCharacter::holdSprint()
{
	this->setMaxSpeed(575.0f);

	IMovementActions::Execute_pressSprintAction(this);
}

void ABaseCharacter::releaseSprint()
{
	this->setMaxSpeed(450.0f);

	IMovementActions::Execute_releaseSprintAction(this);
}

void ABaseCharacter::Jump()
{
	Super::Jump();

	IMovementActions::Execute_pressJumpAction(this);
}

void ABaseCharacter::StopJumping()
{
	Super::StopJumping();

	IMovementActions::Execute_releaseJumpAction(this);
}

void ABaseCharacter::setMaxSpeed_Implementation(float speed)
{
	GetCharacterMovement()->MaxWalkSpeed = speed;
}

#pragma region Reload
void ABaseCharacter::reloadVisual()
{

}

void ABaseCharacter::reloadLogic()
{
	if (!currentWeapon)
	{
		return;
	}

	int currentMagazineSize = currentWeapon->getCurrentMagazineSize();
	int magazineSize = currentWeapon->getMagazineSize();

	if (currentMagazineSize == magazineSize)
	{
		return;
	}

	int32& ammoCount = spareAmmo[static_cast<size_t>(currentWeapon->getAmmo()->getAmmoType())];

	if (!ammoCount)
	{
		return;
	}

	int reloadedAmmoRequire = min(magazineSize - currentMagazineSize, ammoCount);

	currentWeapon->setCurrentMagazineSize(currentMagazineSize + reloadedAmmoRequire);

	if (ammoCount != 9999)
	{
		ammoCount -= reloadedAmmoRequire;
	}
}

void ABaseCharacter::runReloadLogic_Implementation()
{
	this->reloadLogic();

	IReload::Execute_reloadEventLogic(this);
}
#pragma endregion

#pragma region Shoot
void ABaseCharacter::shootVisual()
{

}

void ABaseCharacter::shootLogic()
{
	if (currentWeapon)
	{
		UWorld* world = GetWorld();

		if (world)
		{
			currentWeapon->shoot(world, currentWeaponMesh, this);
		}
	}
}

void ABaseCharacter::runShootLogic_Implementation()
{
	this->shootLogic();

	IShoot::Execute_shootEventLogic(this);
}
#pragma endregion

#pragma region Death
void ABaseCharacter::deathVisual()
{

}

void ABaseCharacter::deathLogic()
{
	isDead = true;
}

void ABaseCharacter::runDeathLogic_Implementation()
{
	this->deathLogic();

	IDeath::Execute_deathEventLogic(this);
}
#pragma endregion

void ABaseCharacter::resetShootLogic()
{
	if (currentWeapon)
	{
		UWorld* world = GetWorld();

		if (world)
		{
			currentWeapon->resetShoot(world, currentWeaponMesh, this);
		}
	}
}

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	USkeletalMeshComponent* mesh = ACharacter::GetMesh();
	NetUpdateFrequency = 60;

	spareAmmo.Init(0, 4);

	spareAmmo[static_cast<size_t>(ammoTypes::defaultType)] = 9999;

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	mesh->SetGenerateOverlapEvents(true);
	mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	currentWeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CurrentWeaponMesh"));
	currentWeaponMesh->SetupAttachment(mesh, "Hand_WeaponSocket_R");

	magazine = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Magazine"));
	magazine->SetupAttachment(currentWeaponMesh);

#pragma region BlueprintFunctionLibrary
	isReloading = false;


#pragma endregion
}

void ABaseCharacter::shoot()
{
	this->shootVisual();

	IShoot::Execute_shootEventVisual(this);
}

void ABaseCharacter::resetShoot()
{
	MultiplayerUtility::runOnServerReliable(this, "resetShootLogic");
}

void ABaseCharacter::changeToDefaultWeapon_Implementation()
{
	currentWeapon = defaultWeaponSlot;

	this->updateWeaponMesh();
}

void ABaseCharacter::restoreHealth(float amount)
{
	float tem = this->getCurrentHealth();

	tem += amount;

	if (tem > this->getHealth())
	{
		this->setCurrentHealth(this->getHealth());
	}
	else
	{
		this->setCurrentHealth(tem);
	}
}

void ABaseCharacter::takeDamage(float amount)
{
	this->setCurrentHealth(this->getCurrentHealth() - amount);
}

void ABaseCharacter::setHealth_Implementation(float newHealth)
{
	health = newHealth;
}

void ABaseCharacter::setCurrentHealth_Implementation(float newCurrentHealth)
{
	currentHealth = newCurrentHealth;
}

void ABaseCharacter::setIsAlly_Implementation(bool newIsAlly)
{
	isAlly = newIsAlly;
}

float ABaseCharacter::getHealth() const
{
	return health;
}

float ABaseCharacter::getCurrentHealth() const
{
	return currentHealth;
}

bool ABaseCharacter::getIsAlly() const
{
	return isAlly;
}

int32 ABaseCharacter::getSpareAmmo(ammoTypes type) const
{
	return spareAmmo[static_cast<size_t>(type)];
}

bool ABaseCharacter::getIsReloading() const
{
	return isReloading;
}

USkeletalMeshComponent* ABaseCharacter::getCurrentWeaponMesh() const
{
	return currentWeaponMesh;
}

int ABaseCharacter::getWeaponCount() const
{
	int result = 0;

	result += static_cast<bool>(defaultWeaponSlot);

	return result;
}

float ABaseCharacter::getFlatDamageReduction_Implementation() const
{
	return 200.0f;
}

float ABaseCharacter::getPercentageDamageReduction_Implementation() const
{
	return 25.0f;
}
