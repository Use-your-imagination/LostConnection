// Copyright (c) 2021 Use-your-imagination

#include "BaseDrone.h"

#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerInput.h"
#include "Algo/Find.h"

#include "Engine/LostConnectionGameState.h"
#include "Weapons/SubmachineGuns/Hipter.h"
#include "Weapons/Pistols/Gauss.h"
#include "Utility/MultiplayerUtility.h"
#include "Utility/Blueprints/UtilityBlueprintFunctionLibrary.h"
#include "WorldPlaceables/DeathPlaceholder.h"
#include "Interfaces/UI/InventoryUIHolder.h"

#pragma warning(disable: 4458)

using namespace std;

template<typename T>
static void setCooldown(T* cooldownableObject, float newCooldown = 0.0f)
{
	Cast<ICooldownable>(cooldownableObject)->startCooldown(newCooldown);
}

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

	FInputActionBinding pressZoomAction("Zoom", IE_Pressed);
	FInputActionBinding releaseZoomAction("Zoom", IE_Released);

	FInputActionBinding reload("Reload", IE_Pressed);

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

	FInputActionBinding	inventory("Inventory", IE_Pressed);

	pressZoomAction.ActionDelegate.GetDelegateForManualSet().BindLambda([this]()
		{
			MultiplayerUtility::runOnServerReliableWithMulticast(this, "pressZoom");
		});

	releaseZoomAction.ActionDelegate.GetDelegateForManualSet().BindLambda([this]()
		{
			MultiplayerUtility::runOnServerReliableWithMulticast(this, "releaseZoom");
		});

	reload.ActionDelegate.GetDelegateForManualSet().BindLambda([this]()
		{
			if (IsValid(currentWeapon) && this->getSpareAmmo(currentWeapon->getAmmoType()) != 0)
			{
				MultiplayerUtility::runOnServerReliableWithMulticast(this, "reload");
			}
		});

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
			}
		});

	inventory.ActionDelegate.GetDelegateForManualSet().BindLambda([this]()
		{
			ALostConnectionPlayerState* playerState = Utility::getPlayerState(this);

			if (!playerState)
			{
				return;
			}

			UUserWidget* currentUI = playerState->getCurrentUI();

			if (IInventoryUIHolder::Execute_getInventoryWidget(currentUI)->IsInViewport())
			{
				IInventoryUIHolder::Execute_hideInventory(currentUI, Utility::getPlayerController(this));
			}
			else
			{
				IInventoryUIHolder::Execute_showInventory(currentUI, Utility::getPlayerController(this));
			}
		});

	result.Add(pressZoomAction);
	result.Add(releaseZoomAction);

	result.Add(reload);

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

	result.Add(inventory);

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

	DOREPLIFETIME(ABaseDrone, abilityId);

	DOREPLIFETIME(ABaseDrone, passiveAbility);

	DOREPLIFETIME(ABaseDrone, firstAbility);

	DOREPLIFETIME(ABaseDrone, secondAbility);

	DOREPLIFETIME(ABaseDrone, thirdAbility);

	DOREPLIFETIME(ABaseDrone, ultimateAbility);

	DOREPLIFETIME(ABaseDrone, slideCooldown);

	DOREPLIFETIME(ABaseDrone, secondaryHold);
}

bool ABaseDrone::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool wroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	if (IsValid(passiveAbility))
	{
		wroteSomething |= Channel->ReplicateSubobject(passiveAbility, *Bunch, *RepFlags);

		wroteSomething |= passiveAbility->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	if (IsValid(firstAbility))
	{
		wroteSomething |= Channel->ReplicateSubobject(firstAbility, *Bunch, *RepFlags);

		wroteSomething |= firstAbility->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	if (IsValid(secondAbility))
	{
		wroteSomething |= Channel->ReplicateSubobject(secondAbility, *Bunch, *RepFlags);

		wroteSomething |= secondAbility->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	if (IsValid(thirdAbility))
	{
		wroteSomething |= Channel->ReplicateSubobject(thirdAbility, *Bunch, *RepFlags);

		wroteSomething |= thirdAbility->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	if (IsValid(ultimateAbility))
	{
		wroteSomething |= Channel->ReplicateSubobject(ultimateAbility, *Bunch, *RepFlags);

		wroteSomething |= ultimateAbility->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	return wroteSomething;
}

void ABaseDrone::onAbilityUsed()
{
	switch (abilityId)
	{
	case abilitySlot::empty:
		currentAbility = nullptr;

		break;

	case abilitySlot::passiveAbility:
		currentAbility = passiveAbility;

		break;

	case abilitySlot::firstAbility:
		currentAbility = firstAbility;

		break;

	case abilitySlot::secondAbility:
		currentAbility = secondAbility;

		break;

	case abilitySlot::thirdAbility:
		currentAbility = thirdAbility;

		break;

	case abilitySlot::ultimateAbility:
		currentAbility = ultimateAbility;

		break;
	}
}

bool ABaseDrone::checkPassiveAbilityCast() const
{
	return true;
}

bool ABaseDrone::checkFirstAbilityCast() const
{
	if (firstAbility->getIsDisabled() ||
		currentAbility ||
		currentEnergy < firstAbility->getCost() ||
		(firstAbility->getIsGrounded() && GetCharacterMovement()->IsFalling()))
	{
		return false;
	}

	return true;
}

bool ABaseDrone::checkSecondAbilityCast() const
{
	if (secondAbility->getIsDisabled() ||
		currentAbility ||
		currentEnergy < secondAbility->getCost() ||
		(secondAbility->getIsGrounded() && GetCharacterMovement()->IsFalling()))
	{
		return false;
	}

	return true;
}

bool ABaseDrone::checkThirdAbilityCast() const
{
	if (thirdAbility->getIsDisabled() ||
		currentAbility ||
		currentEnergy < thirdAbility->getCost() ||
		(thirdAbility->getIsGrounded() && GetCharacterMovement()->IsFalling()))
	{
		return false;
	}

	return true;
}

bool ABaseDrone::checkUltimateAbilityCast() const
{
	if (ultimateAbility->getIsDisabled() ||
		currentAbility ||
		currentEnergy < ultimateAbility->getCost() ||
		ultimateAbility->getCurrentCooldown() ||
		(ultimateAbility->getIsGrounded() && GetCharacterMovement()->IsFalling()))
	{
		return false;
	}

	return true;
}

float& ABaseDrone::getCurrentEnergy()
{
	return currentEnergy;
}

void ABaseDrone::BeginPlay()
{
	Super::BeginPlay();

	if (GetController() && !Utility::getPlayerState(this)->getCurrentUI())
	{
		this->initDefaultUI();
	}

	if (HasAuthority())
	{
		timers.addTimer([this]()
			{
				if (currentEnergy != energy)
				{
					this->restoreEnergy(energyRestorationPerSecond);
				}
			}, 1.0f);

		passiveAbility->initAbility();

		firstAbility->initAbility();

		secondAbility->initAbility();

		thirdAbility->initAbility();

		ultimateAbility->initAbility();

		this->restoreAbilitiesCooldown();

		this->restoreWeaponsCooldown();

		Utility::getPlayerState(this)->getPrimaryWeapon()->setOwner(this);
	}
}

void ABaseDrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority() && GetController())
	{
		ALostConnectionPlayerState* playerState = Utility::getPlayerState(this);
		UBaseWeapon* primaryWeapon = playerState->getPrimaryWeapon();
		UBaseWeapon* secondaryWeapon = playerState->getSecondaryWeapon();

		if (primaryWeapon)
		{
			primaryWeapon->Tick(DeltaTime);
		}

		if (secondaryWeapon)
		{
			secondaryWeapon->Tick(DeltaTime);
		}

		if (slideCooldown)
		{
			slideCooldown = FMath::Max(0.0f, slideCooldown - DeltaTime);
		}

		passiveAbility->Tick(DeltaTime);
		firstAbility->Tick(DeltaTime);
		secondAbility->Tick(DeltaTime);
		thirdAbility->Tick(DeltaTime);
		ultimateAbility->Tick(DeltaTime);

		Utility::processCooldown(passiveAbility, DeltaTime);
		Utility::processCooldown(firstAbility, DeltaTime);
		Utility::processCooldown(secondAbility, DeltaTime);
		Utility::processCooldown(thirdAbility, DeltaTime);
		Utility::processCooldown(ultimateAbility, DeltaTime);
	}

	this->showBotHealthBar();
}

void ABaseDrone::MoveForward(float Value)
{
	if (Controller && Value)
	{
		FRotator Rotation = Controller->GetControlRotation();
		FRotator YawRotation(0, Rotation.Yaw, 0);
		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(Direction, Value);
	}
}

void ABaseDrone::MoveRight(float Value)
{
	if (Controller && Value)
	{
		FRotator Rotation = Controller->GetControlRotation();
		FRotator YawRotation(0, Rotation.Yaw, 0);
		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Direction, Value);
	}
}

void ABaseDrone::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABaseDrone::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ABaseDrone::restoreAbilitiesCooldown()
{
	const TArray<FCooldownableAbilitiesData>& abilities = Utility::getPlayerState(this)->getCooldownableAbilities();

	for (const auto& data : abilities)
	{
		switch (data.slot)
		{
		case abilitySlot::passiveAbility:
			setCooldown(passiveAbility, data.remainingCooldown);

			break;

		case abilitySlot::firstAbility:
			setCooldown(firstAbility, data.remainingCooldown);

			break;

		case abilitySlot::secondAbility:
			setCooldown(secondAbility, data.remainingCooldown);

			break;

		case abilitySlot::thirdAbility:
			setCooldown(thirdAbility, data.remainingCooldown);

			break;

		case abilitySlot::ultimateAbility:
			setCooldown(ultimateAbility, data.remainingCooldown);

			break;
		}
	}
}

void ABaseDrone::restoreWeaponsCooldown()
{
	const TArray<FCooldownableWeaponsData>& weapons = Utility::getPlayerState(this)->getCooldownableWeapons();

	for (const auto& data : weapons)
	{
		switch (data.slot)
		{
		case weaponSlotTypes::primaryWeaponSlot:
			setCooldown(this->getPrimaryWeapon(), data.remainingCooldown);

			break;

		case weaponSlotTypes::secondaryWeaponSlot:
			setCooldown(this->getSecondaryWeapon(), data.remainingCooldown);

			break;

		case weaponSlotTypes::defaultWeaponSlot:
			setCooldown(this->getDefaultWeapon(), data.remainingCooldown);

			break;

		case weaponSlotTypes::firstInactiveWeaponSlot:
			setCooldown(this->getFirstInactiveWeapon(), data.remainingCooldown);

			break;

		case weaponSlotTypes::secondInactiveWeaponSlot:
			setCooldown(this->getSecondInactiveWeapon(), data.remainingCooldown);

			break;
		}
	}
}

void ABaseDrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	TArray<FInputActionBinding> inputs = this->initInputs();

	for (const auto& i : inputs)
	{
		PlayerInputComponent->AddActionBinding(i);
	}

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ABaseCharacter::shoot);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &ABaseCharacter::resetShoot);

	PlayerInputComponent->BindAction("WeaponSelector", IE_Pressed, this, &ABaseDrone::pressWeaponSelector);
	PlayerInputComponent->BindAction("WeaponSelector", IE_Released, this, &ABaseDrone::releaseWeaponSelector);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABaseDrone::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABaseDrone::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ABaseDrone::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ABaseDrone::LookUpAtRate);
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

void ABaseDrone::destroyDrone()
{
	ADeathPlaceholder* placeholder = Utility::getGameState(this)->spawn<ADeathPlaceholder>(ULostConnectionAssetManager::get().getDefaults().getDeathPlaceholder(), {});

	GetController()->Possess(placeholder);

	placeholder->FinishSpawning({ FRotator::ZeroRotator, GetActorLocation() });

	Destroy();
}

void ABaseDrone::saveCurrentAbilitiesCooldown(ALostConnectionPlayerState* playerState)
{
	if (ICooldownable* cooldownable = Cast<ICooldownable>(passiveAbility))
	{
		playerState->addCooldownableAbility(abilitySlot::passiveAbility, cooldownable);
	}

	if (ICooldownable* cooldownable = Cast<ICooldownable>(firstAbility))
	{
		playerState->addCooldownableAbility(abilitySlot::firstAbility, cooldownable);
	}

	if (ICooldownable* cooldownable = Cast<ICooldownable>(secondAbility))
	{
		playerState->addCooldownableAbility(abilitySlot::secondAbility, cooldownable);
	}

	if (ICooldownable* cooldownable = Cast<ICooldownable>(thirdAbility))
	{
		playerState->addCooldownableAbility(abilitySlot::thirdAbility, cooldownable);
	}

	playerState->addCooldownableAbility(abilitySlot::ultimateAbility, ultimateAbility);
}

void ABaseDrone::saveCurrentWeaponsCooldown(ALostConnectionPlayerState* playerState)
{
	if (ICooldownable* cooldownable = Cast<ICooldownable>(this->getPrimaryWeapon()))
	{
		playerState->addCooldownableWeapon(weaponSlotTypes::primaryWeaponSlot, cooldownable);
	}

	if (ICooldownable* cooldownable = Cast<ICooldownable>(this->getSecondaryWeapon()))
	{
		playerState->addCooldownableWeapon(weaponSlotTypes::secondaryWeaponSlot, cooldownable);
	}

	if (ICooldownable* cooldownable = Cast<ICooldownable>(this->getDefaultWeapon()))
	{
		playerState->addCooldownableWeapon(weaponSlotTypes::defaultWeaponSlot, cooldownable);
	}

	if (ICooldownable* cooldownable = Cast<ICooldownable>(this->getFirstInactiveWeapon()))
	{
		playerState->addCooldownableWeapon(weaponSlotTypes::firstInactiveWeaponSlot, cooldownable);
	}

	if (ICooldownable* cooldownable = Cast<ICooldownable>(this->getSecondInactiveWeapon()))
	{
		playerState->addCooldownableWeapon(weaponSlotTypes::secondInactiveWeaponSlot, cooldownable);
	}
}

void ABaseDrone::deathLogic()
{
	Super::deathLogic();

	ALostConnectionPlayerState* playerState = Utility::getPlayerState(this);

	this->saveCurrentAbilitiesCooldown(playerState);

	this->saveCurrentWeaponsCooldown(playerState);

	if (isFullyDestruction)
	{
		this->destroyDrone();
	}
}

ABaseDrone::ABaseDrone() :
	energy(1000.0f),
	currentEnergy(1000.0f),
	energyRestorationPerSecond(5.0f),
	cooldownReduction(0.0f),
	duration(100.0f),
	power(100.0f),
	energyEfficiency(100.0f),
	AOE(100.0f),
	castPoint(100.0f),
	isFullyDestruction(true)
{
	isAlly = true;

	BaseTurnRate = 45.0f;
	BaseLookUpRate = 45.0f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraOffset = CreateDefaultSubobject<USpringArmComponent>("CameraOffset");
	CameraOffset->SetupAttachment(RootComponent);
	CameraOffset->TargetArmLength = 300.0f;
	CameraOffset->bUsePawnControlRotation = true;
	CameraOffset->AddLocalOffset({ 0.0f, 0.0f, 50.0f });
	CameraOffset->SocketOffset = { 0.0f, 90.0f, 0.0f };

	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
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

void ABaseDrone::changeToPrimaryWeapon_Implementation()
{
	currentWeapon = Utility::getPlayerState(this)->getPrimaryWeapon();

	this->onCurrentWeaponChange();
}

void ABaseDrone::changeToSecondaryWeapon_Implementation()
{
	currentWeapon = Utility::getPlayerState(this)->getSecondaryWeapon();

	this->onCurrentWeaponChange();
}

void ABaseDrone::pickupAmmo_Implementation(ammoTypes type, int32 count)
{
	TArray<FAmmoData>& spareAmmo = Utility::getPlayerState(this)->getSpareAmmoArray();

	Algo::FindByPredicate(spareAmmo, [&type](FAmmoData& data) { return data.ammoType == type; })->ammoCount += count;
}

void ABaseDrone::dropWeapon_Implementation()
{
	ALostConnectionPlayerState* playerState = Utility::getPlayerState(this);
	UBaseWeapon* primaryWeapon = playerState->getPrimaryWeapon();
	UBaseWeapon* secondaryWeapon = playerState->getSecondaryWeapon();
	UBaseWeapon* defaultWeapon = playerState->getDefaultWeapon();

	if (!currentWeapon || currentWeapon == defaultWeapon)
	{
		return;
	}

	FVector location = currentWeaponMesh->GetComponentLocation();

	location.Z -= GetMesh()->SkeletalMesh->GetImportedBounds().BoxExtent.Z / 2;

	ADroppedWeapon* droppedWeapon = Utility::getGameState(this)->spawn<ADroppedWeapon>(ADroppedWeapon::StaticClass(), { currentWeaponMesh->GetComponentRotation(), location + currentWeapon->getLength() * GetActorForwardVector() });

	this->returnAmmoToSpare(currentWeapon);

	droppedWeapon->setWeapon(currentWeapon);

	currentWeapon->setOwner(nullptr);

	if (currentWeapon == primaryWeapon)
	{
		currentWeapon = primaryWeapon = nullptr;
	}
	else if (currentWeapon == secondaryWeapon)
	{
		currentWeapon = secondaryWeapon = nullptr;
	}

	this->onCurrentWeaponChange();

	droppedWeapon->FinishSpawning({}, true);
}

void ABaseDrone::pickupWeapon_Implementation(ADroppedWeapon* weaponToEquip)
{
	ALostConnectionPlayerState* playerState = Utility::getPlayerState(this);
	UBaseWeapon* primaryWeapon = playerState->getPrimaryWeapon();
	UBaseWeapon* secondaryWeapon = playerState->getSecondaryWeapon();
	UBaseWeapon* defaultWeapon = playerState->getDefaultWeapon();

	if (!weaponToEquip && !weaponToEquip->IsValidLowLevelFast())
	{
		return;
	}

	UBaseWeapon* weapon = weaponToEquip->getWeapon();

	weapon->setOwner(this);

	weapon->updateTimeBetweenShots();

	if (currentWeapon)
	{
		if (currentWeapon == primaryWeapon)
		{
			this->dropWeapon();

			playerState->setPrimaryWeapon(weapon);

			this->changeToPrimaryWeapon();
		}
		else if (currentWeapon == secondaryWeapon)
		{
			this->dropWeapon();

			playerState->setSecondaryWeapon(weapon);

			this->changeToSecondaryWeapon();
		}
		else
		{
			if (!primaryWeapon)
			{
				playerState->setPrimaryWeapon(weapon);
			}
			else if (!secondaryWeapon)
			{
				playerState->setSecondaryWeapon(secondaryWeapon);
			}
		}
	}
	else
	{
		if (!primaryWeapon)
		{
			playerState->setPrimaryWeapon(weapon);

			this->changeToPrimaryWeapon();
		}
		else if (!secondaryWeapon)
		{
			playerState->setSecondaryWeapon(weapon);

			this->changeToSecondaryWeapon();
		}
	}

	weaponToEquip->Destroy(true);
}

void ABaseDrone::changeWeapon()
{
	ALostConnectionPlayerState* playerState = Utility::getPlayerState(this);

	if (currentWeapon == playerState->getPrimaryWeapon())
	{
		this->changeToSecondaryWeapon();
	}
	else if (currentWeapon == playerState->getSecondaryWeapon())
	{
		this->changeToPrimaryWeapon();
	}
	else
	{
		this->changeToPrimaryWeapon();
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

void ABaseDrone::restoreEnergy_Implementation(float amount)
{
	currentEnergy = FMath::Min(energy, currentEnergy + amount);
}

void ABaseDrone::initDefaultUI()
{
	Utility::executeOnOwningClient(this, [this]()
		{
			Utility::setCurrentUI(ULostConnectionAssetManager::get().getUI().getDefaultUI(), this)->init(this);
		});
}

void ABaseDrone::setPrimaryWeapon_Implementation(TSubclassOf<UBaseWeapon> primaryWeapon)
{
	if (!primaryWeapon)
	{
		UE_LOG(LogTemp, Error, TEXT("Primary weapon is null"));

		return;
	}

	ALostConnectionPlayerState* playerState = Utility::getPlayerState(this);
	UBaseWeapon* weapon = NewObject<UBaseWeapon>(playerState, primaryWeapon);

	weapon->setOwner(this);

	weapon->updateTimeBetweenShots();

	playerState->setPrimaryWeapon(weapon);
}

void ABaseDrone::setSecondaryWeapon_Implementation(TSubclassOf<UBaseWeapon> secondaryWeapon)
{
	if (!secondaryWeapon)
	{
		UE_LOG(LogTemp, Error, TEXT("Secondary weapon is null"));

		return;
	}

	ALostConnectionPlayerState* playerState = Utility::getPlayerState(this);
	UBaseWeapon* weapon = NewObject<UBaseWeapon>(playerState, secondaryWeapon);

	weapon->setOwner(this);

	weapon->updateTimeBetweenShots();

	playerState->setSecondaryWeapon(weapon);
}

FVector ABaseDrone::getStartActionLineTrace() const
{
	return FollowCamera->GetComponentLocation();
}

FVector ABaseDrone::getEndActionLineTrace() const
{
	return this->getStartActionLineTrace() + (CameraOffset->TargetArmLength + 200.0f) * FollowCamera->GetForwardVector();
}

TArray<UBaseAbility*> ABaseDrone::getDroneAbilities() const
{
	return
	{
		passiveAbility,
		firstAbility,
		secondAbility,
		thirdAbility,
		ultimateAbility
	};
}

bool ABaseDrone::getZooming() const
{
	return zooming;
}

void ABaseDrone::addPersonalModule(UBasePersonalModule* module)
{
	Utility::getPlayerState(this)->addPersonalModule(module);
}

void ABaseDrone::addWeaponModule(UBaseWeaponModule* module)
{
	Utility::getPlayerState(this)->addWeaponModule(module);
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

void ABaseDrone::setCurrentAbility(UBaseAbility* ability)
{
	if (ability)
	{
		abilityId = ability->getId();
	}
	else
	{
		abilityId = abilitySlot::empty;
	}

	this->onAbilityUsed();
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

int32 ABaseDrone::getWeaponCount() const
{
	int32 result = Super::getWeaponCount();
	ALostConnectionPlayerState* playerState = Utility::getPlayerState(this);

	result += StaticCast<bool>(playerState->getPrimaryWeapon());

	result += StaticCast<bool>(playerState->getSecondaryWeapon());

	return result;
}

TArray<TWeakObjectPtr<UBaseWeapon>> ABaseDrone::getWeapons() const
{
	TArray<TWeakObjectPtr<UBaseWeapon>> weapons = Super::getWeapons();
	ALostConnectionPlayerState* playerState = Utility::getPlayerState(this);
	UBaseWeapon* primaryWeapon = playerState->getPrimaryWeapon();
	UBaseWeapon* secondaryWeapon = playerState->getSecondaryWeapon();

	if (primaryWeapon)
	{
		weapons.Add(primaryWeapon);
	}

	if (secondaryWeapon)
	{
		weapons.Add(secondaryWeapon);
	}

	return weapons;
}

UBaseAbility* ABaseDrone::getCurrentAbility() const
{
	return currentAbility;
}

UBasePassiveAbility* ABaseDrone::getPassiveAbility() const
{
	return passiveAbility;
}

UBaseAbility* ABaseDrone::getFirstAbility() const
{
	return firstAbility;
}

UBaseAbility* ABaseDrone::getSecondAbility() const
{
	return secondAbility;
}

UBaseAbility* ABaseDrone::getThirdAbility() const
{
	return thirdAbility;
}

UBaseUltimateAbility* ABaseDrone::getUltimateAbility() const
{
	return ultimateAbility;
}

const TArray<UAnimMontage*>& ABaseDrone::getAbilitiesAnimations() const
{
	return abilitiesAnimations;
}

const TArray<UBasePersonalModule*>& ABaseDrone::getPersonalModules() const
{
	return Utility::getPlayerState(this)->getPersonalModules();
}

const TArray<UBaseWeaponModule*>& ABaseDrone::getWeaponModules() const
{
	return Utility::getPlayerState(this)->getWeaponModules();
}

void ABaseDrone::castPassiveAbilityVisual()
{

}

void ABaseDrone::castPassiveAbilityLogic()
{
	this->castAbility(passiveAbility, [this]()
		{
			IPassiveAbilityCast::Execute_castPassiveAbilityEventLogic(this);
		});
}

void ABaseDrone::castFirstAbilityVisual()
{

}

void ABaseDrone::castFirstAbilityLogic()
{
	this->castAbility(firstAbility, [this]()
		{
			IFirstAbilityCast::Execute_castFirstAbilityEventLogic(this);
		});	
}

void ABaseDrone::castSecondAbilityVisual()
{

}

void ABaseDrone::castSecondAbilityLogic()
{
	this->castAbility(secondAbility, [this]()
		{
			ISecondAbilityCast::Execute_castSecondAbilityEventLogic(this);
		});
}

void ABaseDrone::castThirdAbilityVisual()
{

}

void ABaseDrone::castThirdAbilityLogic()
{
	this->castAbility(thirdAbility, [this]()
		{
			IThirdAbilityCast::Execute_castThirdAbilityEventLogic(this);
		});
}

void ABaseDrone::castUltimateAbilityVisual()
{

}

void ABaseDrone::castUltimateAbilityLogic()
{
	this->castAbility(ultimateAbility, [this]()
		{
			IUltimateAbilityCast::Execute_castUltimateAbilityEventLogic(this);
		});
}
