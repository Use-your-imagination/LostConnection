// Copyright Epic Games, Inc. All Rights Reserved.

#include "BaseDrone.h"

#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerInput.h"

#include "Engine/LostConnectionPlayerState.h"
#include "Engine/LostConnectionGameState.h"
#include "Weapons/SubmachineGuns/Hipter.h"
#include "Weapons/Pistols/Gauss.h"
#include "Utility/MultiplayerUtility.h"

#pragma warning(disable: 4458)

using namespace std;

ABaseDrone* ABaseDrone::globalPlayerPtr = nullptr;

TArray<FInputActionBinding> ABaseDrone::initInputs()
{
	TArray<FInputActionBinding> result;

#pragma region Abilities
	FInputActionBinding firstAbility("FirstAbility", IE_Pressed);
	FInputActionBinding secondAbility("SecondAbility", IE_Pressed);
	FInputActionBinding thirdAbility("ThirdAbility", IE_Pressed);
	FInputActionBinding ultimateAbility("UltimateAbility", IE_Pressed);

	firstAbility.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "firstAbility"); });
	secondAbility.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "secondAbility"); });
	thirdAbility.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "thirdAbility"); });
	ultimateAbility.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "ultimateAbility"); });

	result.Add(firstAbility);
	result.Add(secondAbility);
	result.Add(thirdAbility);
	result.Add(ultimateAbility);
#pragma endregion

#pragma region Selection
	// FInputActionBinding pressSelectFirstPlayer("FirstPlayer", IE_Pressed);
	// FInputActionBinding pressSelectSecondPlayer("SecondPlayer", IE_Pressed);
	// FInputActionBinding pressSelectThirdPlayer("ThirdPlayer", IE_Pressed);
	// FInputActionBinding pressSelectFourthPlayer("FourthPlayer", IE_Pressed);
	// 
	// FInputActionBinding releaseSelectFirstPlayer("FirstPlayer", IE_Released);
	// FInputActionBinding releaseSelectSecondPlayer("SecondPlayer", IE_Released);
	// FInputActionBinding releaseSelectThirdPlayer("ThirdPlayer", IE_Released);
	// FInputActionBinding releaseSelectFourthPlayer("FourthPlayer", IE_Released);
	// 
	// pressSelectFirstPlayer.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "selectFirstPlayer"); });
	// pressSelectSecondPlayer.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "selectSecondPlayer"); });
	// pressSelectThirdPlayer.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "selectThirdPlayer"); });
	// pressSelectFourthPlayer.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "selectFourthPlayer"); });
	// 
	// releaseSelectFirstPlayer.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "releaseSelectFirstPlayerHandle"); });
	// releaseSelectSecondPlayer.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "releaseSelectSecondPlayerHandle"); });
	// releaseSelectThirdPlayer.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "releaseSelectThirdPlayerHandle"); });
	// releaseSelectFourthPlayer.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "releaseSelectFourthPlayerHandle"); });
	// 
	// result.Add(pressSelectFirstPlayer);
	// result.Add(pressSelectSecondPlayer);
	// result.Add(pressSelectThirdPlayer);
	// result.Add(pressSelectFourthPlayer);
	// 
	// result.Add(releaseSelectFirstPlayer);
	// result.Add(releaseSelectSecondPlayer);
	// result.Add(releaseSelectThirdPlayer);
	// result.Add(releaseSelectFourthPlayer);
#pragma endregion

	FInputActionBinding reload("Reload", IE_Pressed);

	FInputActionBinding pressShoot("Shoot", IE_Pressed);
	FInputActionBinding releaseShoot("Shoot", IE_Released);

	FInputActionBinding holdSprint("Sprint", IE_Pressed);
	FInputActionBinding releaseSprint("Sprint", IE_Released);

	FInputActionBinding changeWeapon("ChangeWeapon", IE_Pressed);

	FInputActionBinding	alternativeWeaponMode("Alternative", IE_Pressed);

	FInputActionBinding	action("Action", IE_Pressed);

	FInputActionBinding	dropWeapon("DropWeapon", IE_Pressed);

	reload.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "reload"); });

	pressShoot.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "shoot"); });
	releaseShoot.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliable(this, "resetShoot"); });

	holdSprint.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerUnreliableWithMulticast(this, "holdSprint"); });
	releaseSprint.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerUnreliableWithMulticast(this, "releaseSprint"); });

	changeWeapon.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliable(this, "changeWeapon"); });

	alternativeWeaponMode.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "alternativeWeaponMode"); });

	action.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliable(this, "action"); });

	dropWeapon.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliable(this, "dropWeapon"); });

	result.Add(reload);

	result.Add(pressShoot);
	result.Add(releaseShoot);

	result.Add(holdSprint);
	result.Add(releaseSprint);

	result.Add(changeWeapon);

	result.Add(alternativeWeaponMode);

	result.Add(action);

	result.Add(dropWeapon);

	return result;
}

void ABaseDrone::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseDrone, energy);

	DOREPLIFETIME(ABaseDrone, currentEnergy);

	DOREPLIFETIME(ABaseDrone, energyRestorationPerSecond);

	DOREPLIFETIME(ABaseDrone, firstWeaponSlot);

	DOREPLIFETIME(ABaseDrone, secondWeaponSlot);

	DOREPLIFETIME(ABaseDrone, passiveAbility);

	DOREPLIFETIME(ABaseDrone, firstAbility);

	DOREPLIFETIME(ABaseDrone, secondAbility);

	DOREPLIFETIME(ABaseDrone, thirdAbility);

	DOREPLIFETIME(ABaseDrone, ultimateAbility);
}

void ABaseDrone::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (HasAuthority())
	{
		defaultWeaponSlot = NewObject<UGauss>(this);

		firstWeaponSlot = NewObject<UHipter>(this);
	}
}

bool ABaseDrone::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool wroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	wroteSomething |= Channel->ReplicateSubobject(firstWeaponSlot, *Bunch, *RepFlags);

	wroteSomething |= Channel->ReplicateSubobject(secondWeaponSlot, *Bunch, *RepFlags);

	wroteSomething |= Channel->ReplicateSubobject(passiveAbility, *Bunch, *RepFlags);

	wroteSomething |= Channel->ReplicateSubobject(firstAbility, *Bunch, *RepFlags);

	wroteSomething |= Channel->ReplicateSubobject(secondAbility, *Bunch, *RepFlags);

	wroteSomething |= Channel->ReplicateSubobject(thirdAbility, *Bunch, *RepFlags);

	wroteSomething |= Channel->ReplicateSubobject(ultimateAbility, *Bunch, *RepFlags);

	return wroteSomething;
}

void ABaseDrone::BeginPlay()
{
	Super::BeginPlay();

	UWorld* world = GetWorld();
	
	if (world)
	{
		ABaseDrone::globalPlayerPtr = UGameplayStatics::GetPlayerController(world, 0)->GetPawn<ABaseDrone>();

		if (HasAuthority())
		{
			timers = NewObject<UTimersUtility>();

			timers->setWorld(world);

			timers->addTimer([this]() 
				{
					if (IsValid(this))
					{
						if (currentEnergy != energy)
						{
							ICaster::Execute_setCurrentEnergy(this, currentEnergy + energyRestorationPerSecond);
						}
					}
				}, 1.0f);
		}
	}
}

void ABaseDrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		if (firstWeaponSlot)
		{
			firstWeaponSlot->reduceShootRemainigTime(DeltaTime);
		}

		if (secondWeaponSlot)
		{
			secondWeaponSlot->reduceShootRemainigTime(DeltaTime);
		}
	}
}

void ABaseDrone::MoveForward(float Value)
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

void ABaseDrone::MoveRight(float Value)
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

void ABaseDrone::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABaseDrone::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ABaseDrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	TArray<FInputActionBinding> inputs = this->initInputs();

	for (const auto& i : inputs)
	{
		PlayerInputComponent->AddActionBinding(i);
	}

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABaseDrone::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ABaseDrone::StopJumping);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ABaseDrone::pressCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ABaseDrone::releaseCrouch);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABaseDrone::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABaseDrone::MoveRight);

	PlayerInputComponent->BindAction("Zoom", IE_Pressed, this, &ABaseDrone::pressZoom);
	PlayerInputComponent->BindAction("Zoom", IE_Released, this, &ABaseDrone::releaseZoom);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ABaseDrone::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ABaseDrone::LookUpAtRate);

	PlayerInputComponent->BindAction("WeaponSelector", IE_Pressed, this, &ABaseDrone::pressWeaponSelector);
	PlayerInputComponent->BindAction("WeaponSelector", IE_Released, this, &ABaseDrone::releaseWeaponSelector);
}

void ABaseDrone::pressCrouch()
{
	crouchHold = true;

	IMovementActions::Execute_pressCrouchAction(this);
}

void ABaseDrone::releaseCrouch()
{
	crouchHold = false;

	IMovementActions::Execute_releaseCrouchAction(this);
}

void ABaseDrone::pressZoom()
{
	secondaryHold = true;

	IInputActions::Execute_pressZoomAction(this);
}

void ABaseDrone::releaseZoom()
{
	secondaryHold = false;

	IInputActions::Execute_releaseZoomAction(this);
}

void ABaseDrone::pressWeaponSelector()
{
	weaponSelectorHold = true;

	IInputActions::Execute_pressWeaponSelectorAction(this);
}

void ABaseDrone::releaseWeaponSelector()
{
	weaponSelectorHold = false;

	IInputActions::Execute_releaseWeaponSelectorAction(this);
}

ABaseDrone::ABaseDrone()
{
	firstWeaponSlot = nullptr;
	secondWeaponSlot = nullptr;
	health = currentHealth = 1000.0f;
	energy = currentEnergy = 1000.0f;
	energyRestorationPerSecond = 5.0f;
	isAlly = true;

	spareAmmo[static_cast<size_t>(ammoTypes::small)] = 720;

	BaseTurnRate = 45.0f;
	BaseLookUpRate = 45.0f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraOffset = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraOffset"));
	CameraOffset->SetupAttachment(RootComponent);
	CameraOffset->TargetArmLength = 300.0f;
	CameraOffset->bUsePawnControlRotation = true;
	CameraOffset->AddLocalOffset({ 0.0f, 0.0f, 50.0f });
	CameraOffset->SocketOffset = { 0.0f, 90.0f, 0.0f };

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraOffset, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

#pragma region BlueprintFunctionLibrary
	secondaryHold = false;

	weaponSelectorHold = false;

	selectedWeaponId = 0;

	inputDimensions = FVector(0.0f);

	zooming = false;

	zoomBlocked = false;

	wallrun = false;

	wallrunBlocked = false;

	wallrunForward = FRotator(0.0f);

	slideCooldown = false;
#pragma endregion
}

void ABaseDrone::shoot()
{
	ABaseCharacter::shoot();

	this->pressShoot();
}

void ABaseDrone::resetShoot()
{
	ABaseCharacter::resetShoot();

	MultiplayerUtility::runOnServerReliableWithMulticast(this, "releaseShoot");
}

void ABaseDrone::changeToFirstWeapon_Implementation()
{
	currentWeapon = firstWeaponSlot;

	this->updateWeaponMesh();
}

void ABaseDrone::changeToSecondWeapon_Implementation()
{
	currentWeapon = secondWeaponSlot;

	this->updateWeaponMesh();
}

void ABaseDrone::pickupAmmo(ammoTypes type, int32 count)
{
	spareAmmo[static_cast<size_t>(type)] += count;
}

void ABaseDrone::dropWeapon()
{
	if (!currentWeapon || currentWeapon == defaultWeaponSlot)
	{
		return;
	}

	UWorld* world = GetWorld();

	if (!world)
	{
		return;
	}

	FVector location = currentWeaponMesh->GetComponentLocation();

	location.Z -= GetMesh()->SkeletalMesh->GetImportedBounds().BoxExtent.Z / 2;

	FTransform spawnPoint(currentWeaponMesh->GetComponentRotation(), location + 100.0f * GetActorForwardVector());

	ADroppedWeapon* droppedWeapon = world->GetGameState<ALostConnectionGameState>()->spawn<ADroppedWeapon>(ADroppedWeapon::StaticClass(), spawnPoint);

	droppedWeapon->setWeapon(currentWeapon);

	if (currentWeapon && currentWeapon == firstWeaponSlot)
	{
		currentWeapon = firstWeaponSlot = nullptr;
	}
	else if (currentWeapon && currentWeapon == secondWeaponSlot)
	{
		currentWeapon = secondWeaponSlot = nullptr;
	}

	this->updateWeaponMesh();

	droppedWeapon->FinishSpawning({}, true);
}

void ABaseDrone::pickupWeapon_Implementation(ADroppedWeapon* weaponToEquip)
{
	if (!weaponToEquip)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Purple, L"Empty");

		return;
	}

	UBaseWeapon* weapon = weaponToEquip->getWeapon();

	if (currentWeapon)
	{
		if (currentWeapon == firstWeaponSlot)
		{
			this->dropWeapon();

			firstWeaponSlot = weapon;

			this->changeToFirstWeapon();
		}
		else if (currentWeapon == secondWeaponSlot)
		{
			this->dropWeapon();

			secondWeaponSlot = weapon;

			this->changeToSecondWeapon();
		}
		else
		{
			if (!firstWeaponSlot)
			{
				firstWeaponSlot = weapon;
			}
			else if (!secondWeaponSlot)
			{
				secondWeaponSlot = weapon;
			}
		}
	}
	else
	{
		if (!firstWeaponSlot)
		{
			firstWeaponSlot = weapon;

			this->changeToFirstWeapon();
		}
		else if (!secondWeaponSlot)
		{
			secondWeaponSlot = weapon;

			this->changeToSecondWeapon();
		}
	}

	weaponToEquip->Destroy(true);
}

void ABaseDrone::changeWeapon()
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
}

void ABaseDrone::alternativeWeaponMode()
{
	if (currentWeapon)
	{
		currentWeapon->alternativeMode();
	}
}

void ABaseDrone::action()
{
	UWorld* world = GetWorld();

	if (!world)
	{
		return;
	}

	FHitResult hit;
	FCollisionQueryParams ignoreParameters;
	IActionable* object = nullptr;

	ignoreParameters.AddIgnoredActor(this);

	world->LineTraceSingleByChannel(hit, this->getStartActionLineTrace(), this->getEndActionLineTrace(), ECollisionChannel::ECC_Visibility, ignoreParameters);

	if (!hit.Actor.IsValid())
	{
		return;
	}

	object = Cast<IActionable>(hit.Actor);

	if (object)
	{
		object->action(this);
	}
}

FVector ABaseDrone::getStartActionLineTrace() const
{
	return FollowCamera->GetComponentLocation();
}

FVector ABaseDrone::getEndActionLineTrace() const
{
	return this->getStartActionLineTrace() + (CameraOffset->TargetArmLength + 200.0f) * FollowCamera->GetForwardVector();
}

void ABaseDrone::pressShoot_Implementation()
{

}

void ABaseDrone::releaseShoot_Implementation()
{

}

float ABaseDrone::getFlatDamageReduction_Implementation() const
{
	return 200.0f;
}

float ABaseDrone::getPercentageDamageReduction_Implementation() const
{
	return 25.0f;
}

void ABaseDrone::setEnergy_Implementation(float newEnergy)
{
	energy = newEnergy;
}

void ABaseDrone::setCurrentEnergy_Implementation(float newCurrentEnergy)
{
	if (newCurrentEnergy > energy)
	{
		currentEnergy = energy;
	}
	else
	{
		currentEnergy = newCurrentEnergy;
	}
}

void ABaseDrone::setEnergyRestorationPerSecond_Implementation(float newEnergyRestorationPerSecond)
{
	energyRestorationPerSecond = newEnergyRestorationPerSecond;
}

float ABaseDrone::getEnergy() const
{
	return energy;
}

float ABaseDrone::getCurrentEnergy() const
{
	return currentEnergy;
}

float ABaseDrone::getEnergyRestorationPerSecond() const
{
	return energyRestorationPerSecond;
}

ABasePassiveAbility* ABaseDrone::getPassiveAbility()
{
	return passiveAbility;
}

ABaseAbility* ABaseDrone::getFirstAbility()
{
	return firstAbility;
}

ABaseAbility* ABaseDrone::getSecondAbility()
{
	return secondAbility;
}

ABaseAbility* ABaseDrone::getThirdAbility()
{
	return thirdAbility;
}

ABaseUltimateAbility* ABaseDrone::getUltimateAbility()
{
	return ultimateAbility;
}

#pragma region PassiveAbility
void ABaseDrone::passiveAbilityVisual()
{

}

void ABaseDrone::passiveAbilityLogic(ABaseCharacter* target)
{
	if (HasAuthority())
	{
		this->passiveAbilityLogic(target);

		IPassiveAbility::Execute_passiveAbilityEventLogic(this, target);
	}
}
#pragma endregion

#pragma region FirstAbility
void ABaseDrone::firstAbilityVisual()
{

}

void ABaseDrone::firstAbilityLogic(ABaseCharacter* target)
{
	if (HasAuthority())
	{
		this->firstAbilityLogic(target);

		IFirstAbility::Execute_firstAbilityEventLogic(this, target);
	}
}
#pragma endregion

#pragma region SecondAbility
void ABaseDrone::secondAbilityVisual()
{

}

void ABaseDrone::secondAbilityLogic(ABaseCharacter* target)
{
	if (HasAuthority())
	{
		this->secondAbilityLogic(target);

		ISecondAbility::Execute_secondAbilityEventLogic(this, target);
	}
}
#pragma endregion

#pragma region ThirdAbility
void ABaseDrone::thirdAbilityVisual()
{

}

void ABaseDrone::thirdAbilityLogic(ABaseCharacter* target)
{
	if (HasAuthority())
	{
		this->thirdAbilityLogic(target);

		IThirdAbility::Execute_thirdAbilityEventLogic(this, target);
	}
}
#pragma endregion

#pragma region UltimateAbility
void ABaseDrone::ultimateAbilityVisual()
{

}

void ABaseDrone::ultimateAbilityLogic(ABaseCharacter* target)
{
	if (HasAuthority())
	{
		this->ultimateAbilityLogic(target);

		IUltimateAbility::Execute_ultimateAbilityEventLogic(this, target);
	}
}
#pragma endregion
