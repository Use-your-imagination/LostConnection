// Copyright Epic Games, Inc. All Rights Reserved.

#include "LostConnectionCharacter.h"

#include <algorithm>

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"

using namespace std;

void ALostConnectionCharacter::BeginPlay()
{
	Super::BeginPlay();

	defaultWeaponSlot = NewObject<ADefaultWeapon>();

	defaultWeaponSlot->character = this;
}

void ALostConnectionCharacter::Tick(float DeltaSeconds)
{
	if (healths <= 0.0f)
	{
		Destroy();
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

	PlayerInputComponent->BindAction("SelectFirstWeapon", IE_Pressed, this, &ALostConnectionCharacter::changeToFirstWeapon);
	PlayerInputComponent->BindAction("SelectSecondWeapon", IE_Pressed, this, &ALostConnectionCharacter::changeToSecondWeapon);
	PlayerInputComponent->BindAction("SelectDefaultWeapon", IE_Pressed, this, &ALostConnectionCharacter::changeToDefaultWeapon);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ALostConnectionCharacter::shoot);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ALostConnectionCharacter::reload);

	PlayerInputComponent->BindAxis("MoveForward", this, &ALostConnectionCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ALostConnectionCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ALostConnectionCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ALostConnectionCharacter::LookUpAtRate);
}

ALostConnectionCharacter::ALostConnectionCharacter()
{
	firstWeaponSlot = nullptr;
	secondWeaponSlot = nullptr;
	healths = 1000.0f;
	isAlly = true;
	USkeletalMeshComponent* mesh = ACharacter::GetMesh();

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

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	currentWeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CurrentWeaponMesh"));
	currentWeaponMesh->SetupAttachment(ACharacter::GetMesh(), "weapon_socket");

	magazine = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Magazine"));
	magazine->SetupAttachment(currentWeaponMesh, "BBarrel_end");
}

void ALostConnectionCharacter::changeToFirstWeapon()
{
	currentWeapon = firstWeaponSlot;

	this->updateWeaponMesh();
}

void ALostConnectionCharacter::changeToSecondWeapon()
{
	currentWeapon = secondWeaponSlot;

	this->updateWeaponMesh();
}

void ALostConnectionCharacter::changeToDefaultWeapon()
{
	currentWeapon = defaultWeaponSlot;

	this->updateWeaponMesh();
}

void ALostConnectionCharacter::updateWeaponMesh()
{
	if (currentWeapon)
	{
		currentWeaponMesh->SetSkeletalMesh(currentWeapon->getWeaponMesh());
	}
	else
	{
		currentWeaponMesh->SetSkeletalMesh(nullptr);
	}
}

void ALostConnectionCharacter::shoot()
{
	if (currentWeapon)
	{
		if (!currentWeapon->shoot(currentWeaponMesh))
		{
			this->reload();
		}
	}
}

void ALostConnectionCharacter::reload()
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

	ammoCount -= reloadedAmmoRequire;
}

void ALostConnectionCharacter::restoreHealths(float amount)
{
	healths += amount;
}

void ALostConnectionCharacter::pickupAmmo(ammoType type, int32 count)
{
	currentAmmoHolding[static_cast<size_t>(type)] += count;
}

void ALostConnectionCharacter::takeDamage(float amount)
{
	healths -= amount;
}

float ALostConnectionCharacter::getHealths() const
{
	return healths;
}

bool ALostConnectionCharacter::getIsAlly() const
{
	return isAlly;
}

int32 ALostConnectionCharacter::getAmmoHoldingCount(ammoType type) const
{
	return currentAmmoHolding[static_cast<size_t>(type)];
}

float ALostConnectionCharacter::getFlatDamageReduction_Implementation() const
{
	return 200.0f;
}

float ALostConnectionCharacter::getPercentageDamageReduction_Implementation() const
{
	return 0.25f;
}
