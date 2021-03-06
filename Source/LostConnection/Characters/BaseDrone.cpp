// Copyright (c) 2021 Use Your Imagination

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
static void setCooldown(TObjectPtr<T> cooldownableObject, float newCooldown = 0.0f)
{
	Cast<ICooldownable>(cooldownableObject)->startCooldown(newCooldown);
}

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

	FInputActionBinding pressGrapple("Grapple", IE_Pressed);
	FInputActionBinding releaseGrapple("Grapple", IE_Released);

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

	pressGrapple.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerUnreliable(this, "pressGrapple"); });

	releaseGrapple.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerUnreliable(this, "releaseGrapple"); });

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

	result.Add(pressGrapple);
	result.Add(releaseGrapple);

	return result;
}

void ABaseDrone::zoomTimerUpdate_Implementation()
{

}

void ABaseDrone::slideTimerUpdate_Implementation()
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

	DOREPLIFETIME(ABaseDrone, grappleHandler);
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

	if (IsValid(grappleHandler))
	{
		wroteSomething |= Channel->ReplicateSubobject(grappleHandler, *Bunch, *RepFlags);

		wroteSomething |= grappleHandler->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	return wroteSomething;
}

void ABaseDrone::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (HasAuthority())
	{
		if (IsValid(grappleHandlerClass))
		{
			grappleHandler = NewObject<UBaseGrappleHandler>(this, grappleHandlerClass);
		}
	}
}

void ABaseDrone::onAbilityUsed()
{
	switch (abilityId)
	{
	case EAbilitySlot::empty:
		currentAbility = nullptr;

		break;

	case EAbilitySlot::passiveAbility:
		currentAbility = passiveAbility;

		break;

	case EAbilitySlot::firstAbility:
		currentAbility = firstAbility;

		break;

	case EAbilitySlot::secondAbility:
		currentAbility = secondAbility;

		break;

	case EAbilitySlot::thirdAbility:
		currentAbility = thirdAbility;

		break;

	case EAbilitySlot::ultimateAbility:
		currentAbility = ultimateAbility;

		break;
	}
}

TArray<TScriptInterface<IOnCastEvent>>& ABaseDrone::getCastEvents()
{
	return castEvents;
}

TArray<TScriptInterface<IOnWaveBeginEvent>>& ABaseDrone::getWaveBeginEvents()
{
	return waveBeginEvents;
}

TArray<TScriptInterface<IOnWaveEndEvent>>& ABaseDrone::getWaveEndEvents()
{
	return waveEndEvents;
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

		grappleHandler->init(this);

		this->restoreAbilitiesCooldown();

		this->restoreWeaponsCooldown();
	}
}

void ABaseDrone::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	TObjectPtr<ALostConnectionPlayerState> playerState = Utility::getPlayerState(this);

	if (HasAuthority() && !isDead && playerState)
	{
		TObjectPtr<UBaseWeapon> primaryWeapon = playerState->getPrimaryWeapon();
		TObjectPtr<UBaseWeapon> secondaryWeapon = playerState->getSecondaryWeapon();

		if (primaryWeapon)
		{
			primaryWeapon->Tick(DeltaSeconds);
		}

		if (secondaryWeapon)
		{
			secondaryWeapon->Tick(DeltaSeconds);
		}

		if (slideCooldown)
		{
			slideCooldown = FMath::Max(0.0f, slideCooldown - DeltaSeconds);
		}

		passiveAbility->Tick(DeltaSeconds);
		firstAbility->Tick(DeltaSeconds);
		secondAbility->Tick(DeltaSeconds);
		thirdAbility->Tick(DeltaSeconds);
		ultimateAbility->Tick(DeltaSeconds);

		Utility::processCooldown(passiveAbility, DeltaSeconds);
		Utility::processCooldown(firstAbility, DeltaSeconds);
		Utility::processCooldown(secondAbility, DeltaSeconds);
		Utility::processCooldown(thirdAbility, DeltaSeconds);
		Utility::processCooldown(ultimateAbility, DeltaSeconds);

		grappleHandler->processCooldown(DeltaSeconds);
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
		case EAbilitySlot::passiveAbility:
			setCooldown(passiveAbility, data.remainingCooldown);

			break;

		case EAbilitySlot::firstAbility:
			setCooldown(firstAbility, data.remainingCooldown);

			break;

		case EAbilitySlot::secondAbility:
			setCooldown(secondAbility, data.remainingCooldown);

			break;

		case EAbilitySlot::thirdAbility:
			setCooldown(thirdAbility, data.remainingCooldown);

			break;

		case EAbilitySlot::ultimateAbility:
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
		case EWeaponSlotType::primaryWeaponSlot:
			setCooldown(this->getPrimaryWeapon(), data.remainingCooldown);

			break;

		case EWeaponSlotType::secondaryWeaponSlot:
			setCooldown(this->getSecondaryWeapon(), data.remainingCooldown);

			break;

		case EWeaponSlotType::defaultWeaponSlot:
			setCooldown(this->getDefaultWeapon(), data.remainingCooldown);

			break;

		case EWeaponSlotType::firstInactiveWeaponSlot:
			setCooldown(this->getFirstInactiveWeapon(), data.remainingCooldown);

			break;

		case EWeaponSlotType::secondInactiveWeaponSlot:
			setCooldown(this->getSecondInactiveWeapon(), data.remainingCooldown);

			break;
		}
	}
}

void ABaseDrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	for (const auto& i : this->initInputs())
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

void ABaseDrone::pressGrapple()
{
	grappleHandler->grappleActionPress();
}

void ABaseDrone::releaseGrapple()
{
	grappleHandler->grappleActionRelease();
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
		playerState->addCooldownableAbility(EAbilitySlot::passiveAbility, cooldownable);
	}

	if (ICooldownable* cooldownable = Cast<ICooldownable>(firstAbility))
	{
		playerState->addCooldownableAbility(EAbilitySlot::firstAbility, cooldownable);
	}

	if (ICooldownable* cooldownable = Cast<ICooldownable>(secondAbility))
	{
		playerState->addCooldownableAbility(EAbilitySlot::secondAbility, cooldownable);
	}

	if (ICooldownable* cooldownable = Cast<ICooldownable>(thirdAbility))
	{
		playerState->addCooldownableAbility(EAbilitySlot::thirdAbility, cooldownable);
	}

	playerState->addCooldownableAbility(EAbilitySlot::ultimateAbility, ultimateAbility);
}

void ABaseDrone::saveCurrentWeaponsCooldown(ALostConnectionPlayerState* playerState)
{
	if (ICooldownable* cooldownable = Cast<ICooldownable>(this->getPrimaryWeapon()))
	{
		playerState->addCooldownableWeapon(EWeaponSlotType::primaryWeaponSlot, cooldownable);
	}

	if (ICooldownable* cooldownable = Cast<ICooldownable>(this->getSecondaryWeapon()))
	{
		playerState->addCooldownableWeapon(EWeaponSlotType::secondaryWeaponSlot, cooldownable);
	}

	if (ICooldownable* cooldownable = Cast<ICooldownable>(this->getDefaultWeapon()))
	{
		playerState->addCooldownableWeapon(EWeaponSlotType::defaultWeaponSlot, cooldownable);
	}

	if (ICooldownable* cooldownable = Cast<ICooldownable>(this->getFirstInactiveWeapon()))
	{
		playerState->addCooldownableWeapon(EWeaponSlotType::firstInactiveWeaponSlot, cooldownable);
	}

	if (ICooldownable* cooldownable = Cast<ICooldownable>(this->getSecondInactiveWeapon()))
	{
		playerState->addCooldownableWeapon(EWeaponSlotType::secondInactiveWeaponSlot, cooldownable);
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
	static ConstructorHelpers::FClassFinder<UBaseGrappleHandler> grappleHandlerFinder(TEXT("/Game/Grapple/BP_BaseGrappleHandler"));

	TObjectPtr<USkeletalMeshComponent> mesh = GetMesh();

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

	GetCapsuleComponent()->SetCollisionResponseToChannel(UConstants::droneInteractiveChannel, ECollisionResponse::ECR_Overlap);

	grappleHandlerClass = grappleHandlerFinder.Class;

#pragma region BlueprintFunctionLibrary
	secondaryHold = false;

	weaponSelectorHold = false;

	selectedWeaponId = 0;

	inputDimensions = FVector(0.0f);

	zooming = false;

	zoomBlocked = false;

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

void ABaseDrone::pickupAmmo_Implementation(EAmmoType type, int32 count)
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

	ADroppedWeapon* droppedWeapon = Utility::getGameState(this)->spawn<ADroppedWeapon>({ currentWeaponMesh->GetComponentRotation(), location + currentWeapon->getLength() * GetActorForwardVector() });

	playerState->returnAmmoToSpare(currentWeapon);

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
	if (!IsValid(weaponToEquip))
	{
		return;
	}

	ALostConnectionPlayerState* playerState = Utility::getPlayerState(this);
	UBaseWeapon* primaryWeapon = playerState->getPrimaryWeapon();
	UBaseWeapon* secondaryWeapon = playerState->getSecondaryWeapon();
	UBaseWeapon* defaultWeapon = playerState->getDefaultWeapon();
	AInventory* inventory = playerState->getInventory();

	UBaseWeapon* weapon = weaponToEquip->getWeapon();

	weapon->Rename(nullptr, playerState);

	if (currentWeapon)
	{
		if (currentWeapon == primaryWeapon && !secondaryWeapon)
		{
			playerState->setSecondaryWeapon(weapon);
		}
		else if (currentWeapon == secondaryWeapon && !primaryWeapon)
		{
			playerState->setPrimaryWeapon(weapon);
		}
		else
		{
			inventory->addUnequippedWeapon(weapon);
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
	TObjectPtr<ALostConnectionPlayerState> playerState = Utility::getPlayerState(this);

	if (currentWeapon)
	{
		currentWeapon->resetShoot(currentWeaponMesh);
	}

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
	TObjectPtr<UWorld> world = GetWorld();

	if (!world)
	{
		return;
	}

	FHitResult hit;
	FCollisionQueryParams ignoreParameters;
	IActionable* object = nullptr;

	ignoreParameters.AddIgnoredActor(this);

	world->LineTraceSingleByChannel(hit, this->getStartActionLineTrace(), this->getEndActionLineTrace(), ECollisionChannel::ECC_Visibility, ignoreParameters);

	object = Cast<IActionable>(hit.GetActor());

	if (object)
	{
		object->doAction(this);
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

void ABaseDrone::setPrimaryWeapon_Implementation(TSubclassOf<UBaseWeapon> primaryWeapon, EWeaponRarity rarity)
{
	TObjectPtr<ALostConnectionPlayerState> playerState = Utility::getPlayerState(this);

	playerState->setPrimaryWeapon(Utility::createWeapon(primaryWeapon, rarity, playerState->getInventory()));
}

void ABaseDrone::setSecondaryWeapon_Implementation(TSubclassOf<UBaseWeapon> secondaryWeapon, EWeaponRarity rarity)
{
	TObjectPtr<ALostConnectionPlayerState> playerState = Utility::getPlayerState(this);

	playerState->setSecondaryWeapon(Utility::createWeapon(secondaryWeapon, rarity, playerState->getInventory()));
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
		abilityId = EAbilitySlot::empty;
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
