// Copyright Epic Games, Inc. All Rights Reserved.

#include "LostConnectionCharacter.h"

#include <algorithm>

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"

#pragma warning(disable: 4458)

DECLARE_DELEGATE_OneParam(FStaticInterfaceMethod, UObject*);

using namespace std;

TArray<FInputActionBinding> ALostConnectionCharacter::initInterfaceInputs()
{
	TArray<FInputActionBinding> result;

	FInputActionBinding releaseFirstAbility("FirstAbility", IE_Released);
	FInputActionBinding releaseSecondAbility("SecondAbility", IE_Released);
	FInputActionBinding releaseThirdAbility("ThirdAbility", IE_Released);
	FInputActionBinding releaseUltimateAbility("UltimateAbility", IE_Released);

	FInputActionBinding releaseSelectFirstPlayer("SelectFirstPlayer", IE_Released);
	FInputActionBinding releaseSelectSecondPlayer("SelectSecondPlayer", IE_Released);
	FInputActionBinding releaseSelectThirdPlayer("SelectThirdPlayer", IE_Released);
	FInputActionBinding releaseSelectFourthPlayer("SelectFourthPlayer", IE_Released);

	FInputActionBinding pressCrouch("Crouch", IE_Pressed);
	FInputActionBinding releaseCrouch("Crouch", IE_Released);

	releaseFirstAbility.ActionDelegate.GetDelegateForManualSet().BindLambda(&IAbilities::Execute_releaseFirstAbility, this);
	releaseSecondAbility.ActionDelegate.GetDelegateForManualSet().BindLambda(&IAbilities::Execute_releaseSecondAbility, this);
	releaseThirdAbility.ActionDelegate.GetDelegateForManualSet().BindLambda(&IAbilities::Execute_releaseThirdAbility, this);
	releaseUltimateAbility.ActionDelegate.GetDelegateForManualSet().BindLambda(&IAbilities::Execute_releaseUltimateAbility, this);

	releaseSelectFirstPlayer.ActionDelegate.GetDelegateForManualSet().BindLambda(&IAllySelection::Execute_releaseSelectFirstPlayer, this);
	releaseSelectSecondPlayer.ActionDelegate.GetDelegateForManualSet().BindLambda(&IAllySelection::Execute_releaseSelectSecondPlayer, this);
	releaseSelectThirdPlayer.ActionDelegate.GetDelegateForManualSet().BindLambda(&IAllySelection::Execute_releaseSelectThirdPlayer, this);
	releaseSelectFourthPlayer.ActionDelegate.GetDelegateForManualSet().BindLambda(&IAllySelection::Execute_releaseSelectFourthPlayer, this);

	pressCrouch.ActionDelegate.GetDelegateForManualSet().BindLambda(&IMovementActions::Execute_pressCrouchAction, this);
	releaseCrouch.ActionDelegate.GetDelegateForManualSet().BindLambda(&IMovementActions::Execute_releaseCrouchAction, this);

	result.Add(releaseFirstAbility);
	result.Add(releaseSecondAbility);
	result.Add(releaseThirdAbility);
	result.Add(releaseUltimateAbility);

	result.Add(releaseSelectFirstPlayer);
	result.Add(releaseSelectSecondPlayer);
	result.Add(releaseSelectThirdPlayer);
	result.Add(releaseSelectFourthPlayer);

	result.Add(pressCrouch);
	result.Add(releaseCrouch);

	return result;
}

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

	TArray<FInputActionBinding> inputs = this->initInterfaceInputs();

	for (const auto& i : inputs)
	{
		PlayerInputComponent->AddActionBinding(i);
	}

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ALostConnectionCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ALostConnectionCharacter::StopJumping);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ALostConnectionCharacter::sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ALostConnectionCharacter::run);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ALostConnectionCharacter::shoot);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &ALostConnectionCharacter::resetShoot);

	PlayerInputComponent->BindAction("Alternative", IE_Pressed, this, &ALostConnectionCharacter::pressAlternative);
	PlayerInputComponent->BindAction("Alternative", IE_Released, this, &ALostConnectionCharacter::releaseAlternative);

	PlayerInputComponent->BindAction("ChangeWeapon", IE_Pressed, this, &ALostConnectionCharacter::changeWeapon);
	PlayerInputComponent->BindAction("ChangeWeapon", IE_Released, this, &ALostConnectionCharacter::releaseChangeWeapon);

	PlayerInputComponent->BindAction("Action", IE_Pressed, this, &ALostConnectionCharacter::pressAction);
	PlayerInputComponent->BindAction("Action", IE_Released, this, &ALostConnectionCharacter::releaseAction);

#pragma region Abilities
	PlayerInputComponent->BindAction("FirstAbility", IE_Pressed, this, &ALostConnectionCharacter::firstAbility);

	PlayerInputComponent->BindAction("SecondAbility", IE_Pressed, this, &ALostConnectionCharacter::secondAbility);

	PlayerInputComponent->BindAction("ThirdAbility", IE_Pressed, this, &ALostConnectionCharacter::thirdAbility);

	PlayerInputComponent->BindAction("UltimateAbility", IE_Pressed, this, &ALostConnectionCharacter::ultimateAbility);
#pragma endregion

#pragma region PlayerSelection
	PlayerInputComponent->BindAction("SelectFirstPlayer", IE_Pressed, this, &ALostConnectionCharacter::selectFirstPlayer);

	PlayerInputComponent->BindAction("SelectSecondPlayer", IE_Pressed, this, &ALostConnectionCharacter::selectSecondPlayer);

	PlayerInputComponent->BindAction("SelectThirdPlayer", IE_Pressed, this, &ALostConnectionCharacter::selectThirdPlayer);

	PlayerInputComponent->BindAction("SelectFourthPlayer", IE_Pressed, this, &ALostConnectionCharacter::selectFourthPlayer);
#pragma endregion

	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ALostConnectionCharacter::reload);

	PlayerInputComponent->BindAxis("MoveForward", this, &ALostConnectionCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ALostConnectionCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ALostConnectionCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ALostConnectionCharacter::LookUpAtRate);
}

void ALostConnectionCharacter::Jump()
{
	Super::Jump();

	IMovementActions::Execute_pressJumpAction(this);
}

void ALostConnectionCharacter::StopJumping()
{
	Super::StopJumping();

	IMovementActions::Execute_releaseJumpAction(this);
}

void ALostConnectionCharacter::sprint_Implementation()
{
	this->changeMaxSpeed(575.0f);

	IMovementActions::Execute_sprintAction(this);
}

void ALostConnectionCharacter::run_Implementation()
{
	this->changeMaxSpeed(450.0f);

	IMovementActions::Execute_runAction(this);
}

void ALostConnectionCharacter::changeMaxSpeed_Implementation(float speed)
{
	GetCharacterMovement()->MaxWalkSpeed = speed;
}

void ALostConnectionCharacter::reloadAnimationMulticast_Implementation()
{
	this->reloadAnimation();
}

void ALostConnectionCharacter::pressAlternative_Implementation()
{

}

void ALostConnectionCharacter::releaseAlternative_Implementation()
{

}

void ALostConnectionCharacter::pressShoot_Implementation()
{

}

void ALostConnectionCharacter::releaseShoot_Implementation()
{

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

			this->pressShoot();
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

		this->releaseShoot();
	}
}

void ALostConnectionCharacter::reload_Implementation()
{
	this->reloadAnimationMulticast();

	this->reloadGameplay();
}

void ALostConnectionCharacter::changeWeapon_Implementation()
{
	if (currentWeapon == firstWeaponSlot)
	{
		this->changeToSecondWeapon();
	}
	else if (currentWeapon == secondWeaponSlot)
	{
		this->changeToFirstWeapon();
	}
	else
	{
		this->changeToFirstWeapon();
	}

	this->pressChangeWeapon();
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

void ALostConnectionCharacter::firstAbility_Implementation()
{
	IAbilities::Execute_pressFirstAbility(this);
}

void ALostConnectionCharacter::secondAbility_Implementation()
{
	IAbilities::Execute_pressSecondAbility(this);
}

void ALostConnectionCharacter::thirdAbility_Implementation()
{
	IAbilities::Execute_pressThirdAbility(this);
}

void ALostConnectionCharacter::ultimateAbility_Implementation()
{
	IAbilities::Execute_pressUltimateAbility(this);
}

void ALostConnectionCharacter::selectFirstPlayer_Implementation()
{
	IAllySelection::Execute_pressSelectFirstPlayer(this);
}

void ALostConnectionCharacter::selectSecondPlayer_Implementation()
{
	IAllySelection::Execute_pressSelectSecondPlayer(this);
}

void ALostConnectionCharacter::selectThirdPlayer_Implementation()
{
	IAllySelection::Execute_pressSelectThirdPlayer(this);
}

void ALostConnectionCharacter::selectFourthPlayer_Implementation()
{
	IAllySelection::Execute_pressSelectFourthPlayer(this);
}

void ALostConnectionCharacter::pressChangeWeapon_Implementation()
{

}

void ALostConnectionCharacter::releaseChangeWeapon_Implementation()
{

}

void ALostConnectionCharacter::pressAction_Implementation()
{

}

void ALostConnectionCharacter::releaseAction_Implementation()
{

}

USkeletalMeshComponent* ALostConnectionCharacter::getCurrentWeaponMesh() const
{
	return currentWeaponMesh;
}

int ALostConnectionCharacter::getWeaponCount() const
{
	int result = 0;

	result += static_cast<bool>(firstWeaponSlot);

	result += static_cast<bool>(secondWeaponSlot);

	result += static_cast<bool>(defaultWeaponSlot);

	return result;
}

float ALostConnectionCharacter::getFlatDamageReduction_Implementation() const
{
	return 200.0f;
}

float ALostConnectionCharacter::getPercentageDamageReduction_Implementation() const
{
	return 25.0f;
}
