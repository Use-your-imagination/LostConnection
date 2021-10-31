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
#include "Utility/Blueprints/UtilityBlueprintFunctionLibrary.h"

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

	firstAbility.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliable(this, "castFirstAbility"); });
	secondAbility.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliable(this, "castSecondAbility"); });
	thirdAbility.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliable(this, "castThirdAbility"); });
	ultimateAbility.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliable(this, "castUltimateAbility"); });

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

	FInputActionBinding holdJump("Jump", IE_Pressed);
	FInputActionBinding releaseJump("Jump", IE_Released);

	FInputActionBinding holdSprint("Sprint", IE_Pressed);
	FInputActionBinding releaseSprint("Sprint", IE_Released);

	FInputActionBinding pressCrouch("Crouch", IE_Pressed);
	FInputActionBinding releaseCrouch("Crouch", IE_Released);

	FInputActionBinding changeWeapon("ChangeWeapon", IE_Pressed);

	FInputActionBinding	alternativeWeaponMode("Alternative", IE_Pressed);

	FInputActionBinding	action("Action", IE_Pressed);

	FInputActionBinding	dropWeapon("DropWeapon", IE_Pressed);

	FInputActionBinding	cancelAbility("CancelAbility", IE_Pressed);

	reload.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "reload"); });

	pressShoot.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "shoot"); });
	releaseShoot.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliable(this, "resetShoot"); });

	holdJump.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "Jump"); });
	releaseJump.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "StopJumping"); });

	holdSprint.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "holdSprint"); });
	releaseSprint.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "releaseSprint"); });

	pressCrouch.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "pressCrouch"); });
	releaseCrouch.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "releaseCrouch"); });

	changeWeapon.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliable(this, "changeWeapon"); });

	alternativeWeaponMode.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "alternativeWeaponMode"); });

	action.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliable(this, "action"); });

	dropWeapon.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliable(this, "dropWeapon"); });

	cancelAbility.ActionDelegate.GetDelegateForManualSet().BindLambda([this]()
		{
			if (currentAbility && currentAbility->getIsCancelable())
			{
				UUtilityBlueprintFunctionLibrary::cancelCurrentAbilityAnimation(this);

				this->setCurrentAbility(nullptr);
			}
		});

	result.Add(reload);

	result.Add(pressShoot);
	result.Add(releaseShoot);

	result.Add(holdJump);
	result.Add(releaseJump);

	result.Add(holdSprint);
	result.Add(releaseSprint);

	result.Add(pressCrouch);
	result.Add(releaseCrouch);

	result.Add(changeWeapon);

	result.Add(alternativeWeaponMode);

	result.Add(action);

	result.Add(dropWeapon);

	result.Add(cancelAbility);

	return result;
}

void ABaseDrone::zoomTimerUpdate_Implementation()
{

}

void ABaseDrone::slideTimerUpdate_Implementation()
{

}

void ABaseDrone::wallrunTimerUpdate_Implementation()
{

}

void ABaseDrone::wallrunCooldown_Implementation()
{

}

void ABaseDrone::setSlideCooldown_Implementation(float newSlideCooldown)
{
	slideCooldown = newSlideCooldown;
}

void ABaseDrone::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseDrone, energy);

	DOREPLIFETIME(ABaseDrone, currentEnergy);

	DOREPLIFETIME(ABaseDrone, energyRestorationPerSecond);

	DOREPLIFETIME(ABaseDrone, cooldownReduction);

	DOREPLIFETIME(ABaseDrone, duration);

	DOREPLIFETIME(ABaseDrone, power);

	DOREPLIFETIME(ABaseDrone, energyEfficiency);

	DOREPLIFETIME(ABaseDrone, AOE);

	DOREPLIFETIME(ABaseDrone, castPoint);

	DOREPLIFETIME(ABaseDrone, currentAbility);

	DOREPLIFETIME(ABaseDrone, passiveAbility);

	DOREPLIFETIME(ABaseDrone, firstAbility);

	DOREPLIFETIME(ABaseDrone, secondAbility);

	DOREPLIFETIME(ABaseDrone, thirdAbility);

	DOREPLIFETIME(ABaseDrone, ultimateAbility);

	DOREPLIFETIME(ABaseDrone, firstWeaponSlot);

	DOREPLIFETIME(ABaseDrone, secondWeaponSlot);

	DOREPLIFETIME(ABaseDrone, slideCooldown);
}

void ABaseDrone::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (HasAuthority())
	{
		UWorld* world = GetWorld();

		if (world)
		{
			defaultWeaponSlot = NewObject<UGauss>(this);

			defaultWeaponSlot->setWorld(world);

			defaultWeaponSlot->setCharacter(this);

			firstWeaponSlot = NewObject<UHipter>(this);

			firstWeaponSlot->setWorld(world);

			firstWeaponSlot->setCharacter(this);
		}
	}
}

bool ABaseDrone::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool wroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	wroteSomething |= Channel->ReplicateSubobject(firstWeaponSlot, *Bunch, *RepFlags);

	wroteSomething |= Channel->ReplicateSubobject(secondWeaponSlot, *Bunch, *RepFlags);

	wroteSomething |= Channel->ReplicateSubobject(currentAbility, *Bunch, *RepFlags);

	wroteSomething |= Channel->ReplicateSubobject(passiveAbility, *Bunch, *RepFlags);

	wroteSomething |= Channel->ReplicateSubobject(firstAbility, *Bunch, *RepFlags);

	wroteSomething |= Channel->ReplicateSubobject(secondAbility, *Bunch, *RepFlags);

	wroteSomething |= Channel->ReplicateSubobject(thirdAbility, *Bunch, *RepFlags);

	wroteSomething |= Channel->ReplicateSubobject(ultimateAbility, *Bunch, *RepFlags);

	return wroteSomething;
}

bool ABaseDrone::checkPassiveAbilityCast() const
{
	return true;
}

bool ABaseDrone::checkFirstAbilityCast() const
{
	if (currentAbility || currentEnergy < firstAbility->getCost())
	{
		return false;
	}

	return true;
}

bool ABaseDrone::checkSecondAbilityCast() const
{
	if (currentAbility || currentEnergy < firstAbility->getCost())
	{
		return false;
	}

	return true;
}

bool ABaseDrone::checkThirdAbilityCast() const
{
	if (currentAbility || currentEnergy < firstAbility->getCost())
	{
		return false;
	}

	return true;
}

bool ABaseDrone::checkUltimateAbilityCast() const
{
	if (currentAbility || currentEnergy < ultimateAbility->getCost() || !ultimateAbility->getCurrentCooldown())
	{
		return false;
	}

	return true;
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
			timers->addTimer([this]()
				{
					if (IsValidLowLevel())
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
			firstWeaponSlot->Tick(DeltaTime);
		}

		if (secondWeaponSlot)
		{
			secondWeaponSlot->Tick(DeltaTime);
		}

		if (slideCooldown > 0.0f)
		{
			float tem = slideCooldown - DeltaTime;

			if (tem < 0.0)
			{
				slideCooldown = 0.0f;
			}
			else
			{
				slideCooldown = tem;
			}
		}

		passiveAbility->Tick(DeltaTime);
		firstAbility->Tick(DeltaTime);
		secondAbility->Tick(DeltaTime);
		thirdAbility->Tick(DeltaTime);
		ultimateAbility->Tick(DeltaTime);
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

void ABaseDrone::deathLogic()
{
	if (timers)
	{
		timers->clear();
	}
}

ABaseDrone::ABaseDrone() :
	firstWeaponSlot(nullptr),
	secondWeaponSlot(nullptr),
	energy(1000.0f),
	currentEnergy(1000.0f),
	energyRestorationPerSecond(5.0f),
	cooldownReduction(0.0f),
	duration(100.0f),
	power(100.0f),
	energyEfficiency(100.0f),
	AOE(100.0f),
	castPoint(100.0f)
{
	health = 1000.0f;
	currentHealth = 1000.0f;
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

	JumpMaxCount = 2;

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

	isSlideCooldown = false;

	slideCooldown = 5.0f;
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

	object = Cast<IActionable>(hit.Actor);

	if (object)
	{
		object->action(this);
	}
}

UBaseWeapon* ABaseDrone::getFirstWeapon()
{
	return firstWeaponSlot;
}

UBaseWeapon* ABaseDrone::getSecondWeapon()
{
	return secondWeaponSlot;
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
	return 10.0f;
}

float ABaseDrone::getPercentageDamageReduction_Implementation() const
{
	return 15.0f;
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

void ABaseDrone::setCooldownReduction_Implementation(float newCooldownReduction)
{
	cooldownReduction = newCooldownReduction;
}

void ABaseDrone::setDuration_Implementation(float newDuration)
{
	duration = newDuration;
}

void ABaseDrone::setPower_Implementation(float newPower)
{
	power = newPower;
}

void ABaseDrone::setEnergyEfficiency_Implementation(float newEnergyEfficiency)
{
	energyEfficiency = newEnergyEfficiency;
}

void ABaseDrone::setAOE_Implementation(float newAOE)
{
	AOE = newAOE;
}

void ABaseDrone::setCastPoint_Implementation(float newCastPoint)
{
	castPoint = newCastPoint;
}

void ABaseDrone::setCurrentAbility_Implementation(UBaseAbility* ability)
{
	currentAbility = ability;
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

float ABaseDrone::getCooldownReduction() const
{
	return cooldownReduction;
}

float ABaseDrone::getDuration() const
{
	return duration;
}

float ABaseDrone::getPower() const
{
	return power;
}

float ABaseDrone::getEnergyEfficiency() const
{
	return energyEfficiency;
}

float ABaseDrone::getAOE() const
{
	return AOE;
}

float ABaseDrone::getCastPoint() const
{
	return castPoint;
}

UBaseAbility* ABaseDrone::getCurrentAbility()
{
	return currentAbility;
}

UBasePassiveAbility* ABaseDrone::getPassiveAbility()
{
	return passiveAbility;
}

UBaseAbility* ABaseDrone::getFirstAbility()
{
	return firstAbility;
}

UBaseAbility* ABaseDrone::getSecondAbility()
{
	return secondAbility;
}

UBaseAbility* ABaseDrone::getThirdAbility()
{
	return thirdAbility;
}

UBaseUltimateAbility* ABaseDrone::getUltimateAbility()
{
	return ultimateAbility;
}

#pragma region PassiveAbility
void ABaseDrone::castPassiveAbilityVisual()
{

}

void ABaseDrone::castPassiveAbilityLogic_Implementation()
{
	currentEnergy -= passiveAbility->getCost();

	passiveAbility->useAbility();

	IPassiveAbilityCast::Execute_castPassiveAbilityEventLogic(this);
}
#pragma endregion

#pragma region FirstAbility
void ABaseDrone::castFirstAbilityVisual()
{

}

void ABaseDrone::castFirstAbilityLogic_Implementation()
{
	currentEnergy -= firstAbility->getCost();

	firstAbility->useAbility();

	IFirstAbilityCast::Execute_castFirstAbilityEventLogic(this);
}
#pragma endregion

#pragma region SecondAbility
void ABaseDrone::castSecondAbilityVisual()
{

}

void ABaseDrone::castSecondAbilityLogic_Implementation()
{
	currentEnergy -= secondAbility->getCost();

	secondAbility->useAbility();

	ISecondAbilityCast::Execute_castSecondAbilityEventLogic(this);
}
#pragma endregion

#pragma region ThirdAbility
void ABaseDrone::castThirdAbilityVisual()
{

}

void ABaseDrone::castThirdAbilityLogic_Implementation()
{
	currentEnergy -= thirdAbility->getCost();

	thirdAbility->useAbility();

	IThirdAbilityCast::Execute_castThirdAbilityEventLogic(this);
}
#pragma endregion

#pragma region UltimateAbility
void ABaseDrone::castUltimateAbilityVisual()
{

}

void ABaseDrone::castUltimateAbilityLogic_Implementation()
{
	currentEnergy -= ultimateAbility->getCost();

	ultimateAbility->useAbility();

	IUltimateAbilityCast::Execute_castUltimateAbilityEventLogic(this);
}
#pragma endregion
