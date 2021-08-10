// Copyright Epic Games, Inc. All Rights Reserved.

#include "LostConnectionCharacter.h"

#include <algorithm>

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"

#pragma warning(disable: 4458)

using namespace std;

void ALostConnectionCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALostConnectionCharacter, health);

	DOREPLIFETIME(ALostConnectionCharacter, currentHealth);

	DOREPLIFETIME(ALostConnectionCharacter, isAlly);

	DOREPLIFETIME(ALostConnectionCharacter, currentWeapon);

	DOREPLIFETIME(ALostConnectionCharacter, firstWeaponSlot);

	DOREPLIFETIME(ALostConnectionCharacter, secondWeaponSlot);

	DOREPLIFETIME(ALostConnectionCharacter, defaultWeaponSlot);
}

void ALostConnectionCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (HasAuthority())
	{
		defaultWeaponSlot = NewObject<UDefaultWeapon>(this);
	}
}

bool ALostConnectionCharacter::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool WroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	if (defaultWeaponSlot)
	{
		WroteSomething |= Channel->ReplicateSubobject(defaultWeaponSlot, *Bunch, *RepFlags);
	}

	return WroteSomething;
}

void ALostConnectionCharacter::onRepCurrentWeapon()
{
	this->updateWeaponMesh();
}

void ALostConnectionCharacter::BeginPlay()
{
	Super::BeginPlay();

	this->changeToDefaultWeapon();
}

void ALostConnectionCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (currentHealth <= 0.0f)
	{
		Destroy();
	}

	if (shootRemainingTime > 0.0f)
	{
		shootRemainingTime -= DeltaSeconds;
	}
}

void ALostConnectionCharacter::MoveForward(float Value)
{
	if (Controller && Value)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ALostConnectionCharacter::MoveRight(float Value)
{
	if (Controller && Value)
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ALostConnectionCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ALostConnectionCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ALostConnectionCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ALostConnectionCharacter::sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ALostConnectionCharacter::run);

	PlayerInputComponent->BindAction("SelectFirstWeapon", IE_Pressed, this, &ALostConnectionCharacter::changeToFirstWeapon);
	PlayerInputComponent->BindAction("SelectSecondWeapon", IE_Pressed, this, &ALostConnectionCharacter::changeToSecondWeapon);
	PlayerInputComponent->BindAction("SelectDefaultWeapon", IE_Pressed, this, &ALostConnectionCharacter::changeToDefaultWeapon);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ALostConnectionCharacter::shoot);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &ALostConnectionCharacter::resetShoot);

	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ALostConnectionCharacter::reload);

	PlayerInputComponent->BindAxis("MoveForward", this, &ALostConnectionCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ALostConnectionCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ALostConnectionCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ALostConnectionCharacter::LookUpAtRate);
}

void ALostConnectionCharacter::sprint_Implementation()
{
	this->changeMaxSpeed(575.0f);
}

void ALostConnectionCharacter::run_Implementation()
{
	this->changeMaxSpeed(450.0f);
}

void ALostConnectionCharacter::changeMaxSpeed_Implementation(float speed)
{
	GetCharacterMovement()->MaxWalkSpeed = speed;
}

void ALostConnectionCharacter::reloadAnimationMulticast_Implementation()
{
	this->reloadAnimation();
}

void ALostConnectionCharacter::reloadGameplay()
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

	int32& ammoCount = currentAmmoHolding[static_cast<size_t>(currentWeapon->getAmmo()->getAmmoType())];

	if (!ammoCount)
	{
		return;
	}

	int reloadedAmmoRequire = min(magazineSize - currentMagazineSize, ammoCount);

	// TODO: start reload animation

	currentWeapon->setCurrentMagazineSize(currentMagazineSize + reloadedAmmoRequire);

	if (ammoCount != 9999)
	{
		ammoCount -= reloadedAmmoRequire;
	}
}

void ALostConnectionCharacter::reloadAnimation_Implementation()
{

}

ALostConnectionCharacter::ALostConnectionCharacter()
{
	firstWeaponSlot = nullptr;
	secondWeaponSlot = nullptr;
	health = 1000.0f;
	currentHealth = health;
	isAlly = true;
	USkeletalMeshComponent* mesh = ACharacter::GetMesh();
	shootRemainingTime = 0.0f;
	clearTimer = false;
	NetUpdateFrequency = 20;

	currentAmmoHolding.Reserve(4);

	for (size_t i = 0; i < 3; i++)
	{
		currentAmmoHolding.Add(0);
	}

	currentAmmoHolding.Add(9999);

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	mesh->SetGenerateOverlapEvents(true);
	mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);

	// set our turn rates for input
	BaseTurnRate = 45.0f;
	BaseLookUpRate = 45.0f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera offset (pulls in towards the player if there is a collision)
	CameraOffset = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraOffset"));
	CameraOffset->SetupAttachment(RootComponent);
	CameraOffset->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraOffset->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	CameraOffset->AddLocalOffset({ 0.0f, 0.0f, 50.0f });
	CameraOffset->SocketOffset = { 0.0f, 90.0f, 0.0f };

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraOffset, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	currentWeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CurrentWeaponMesh"));
	currentWeaponMesh->SetupAttachment(mesh, "Hand_WeaponSocket_R");

	magazine = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Magazine"));
	magazine->SetupAttachment(currentWeaponMesh);
}

void ALostConnectionCharacter::changeToFirstWeapon_Implementation()
{
	currentWeapon = firstWeaponSlot;

	this->updateWeaponMesh();
}

void ALostConnectionCharacter::changeToSecondWeapon_Implementation()
{
	currentWeapon = secondWeaponSlot;

	this->updateWeaponMesh();
}

void ALostConnectionCharacter::changeToDefaultWeapon_Implementation()
{
	currentWeapon = defaultWeaponSlot;

	this->updateWeaponMesh();
}

void ALostConnectionCharacter::updateWeaponMesh()
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

void ALostConnectionCharacter::shoot_Implementation()
{
	if (currentWeapon)
	{
		UWorld* world = GetWorld();

		if (world)
		{
			FTimerManager& manager = world->GetTimerManager();

			if (manager.IsTimerActive(shootHandle))
			{
				return;
			}

			FTimerDelegate delegate;

			delegate.BindLambda([this, &manager]()
				{
					if (IsPendingKill())
					{
						return;
					}

					if (clearTimer)
					{
						clearTimer = false; manager.ClearTimer(shootHandle);

						return;
					}

					currentWeapon->shoot(currentWeaponMesh, this);
				});

			manager.SetTimer(shootHandle, delegate, 1.0f / static_cast<float>(currentWeapon->getRateOfFire()), true, shootRemainingTime > 0.0f ? shootRemainingTime : 0.0f);

			shootRemainingTime = 1.0f / static_cast<float>(currentWeapon->getRateOfFire());
		}
	}
}

void ALostConnectionCharacter::resetShoot_Implementation()
{
	UWorld* world = GetWorld();

	if (world)
	{
		if (shootRemainingTime > 0.0f)
		{
			clearTimer = true;

			return;
		}

		world->GetTimerManager().ClearTimer(shootHandle);
	}
}

void ALostConnectionCharacter::reload_Implementation()
{
	this->reloadAnimationMulticast();

	this->reloadGameplay();
}

void ALostConnectionCharacter::restoreHealth(float amount)
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

void ALostConnectionCharacter::takeDamage(float amount)
{
	this->setCurrentHealth(this->getCurrentHealth() - amount);
}

void ALostConnectionCharacter::pickupAmmo(ammoTypes type, int32 count)
{
	currentAmmoHolding[static_cast<size_t>(type)] += count;
}

void ALostConnectionCharacter::setCurrentHealth_Implementation(int newCurrentHealth)
{
	currentHealth = newCurrentHealth;
}

void ALostConnectionCharacter::setIsAlly_Implementation(bool newIsAlly)
{
	isAlly = newIsAlly;
}

float ALostConnectionCharacter::getHealth() const
{
	return health;
}

float ALostConnectionCharacter::getCurrentHealth() const
{
	return currentHealth;
}

bool ALostConnectionCharacter::getIsAlly() const
{
	return isAlly;
}

int32 ALostConnectionCharacter::getAmmoHoldingCount(ammoTypes type) const
{
	return currentAmmoHolding[static_cast<size_t>(type)];
}

void ALostConnectionCharacter::changeWeapon_Implementation()
{

}

void ALostConnectionCharacter::action_Implementation()
{

}

USkeletalMeshComponent* ALostConnectionCharacter::getCurrentWeaponMesh() const
{
	return currentWeaponMesh;
}

float ALostConnectionCharacter::getFlatDamageReduction_Implementation() const
{
	return 200.0f;
}

float ALostConnectionCharacter::getPercentageDamageReduction_Implementation() const
{
	return 25.0f;
}
