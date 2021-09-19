// Copyright Epic Games, Inc. All Rights Reserved.

#include "LostConnectionCharacter.h"

#include <algorithm>

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

FString ALostConnectionCharacter::actionHotkey = "F";

ALostConnectionCharacter* ALostConnectionCharacter::globalPlayerPtr = nullptr;

TArray<FInputActionBinding> ALostConnectionCharacter::initInputs()
{
	TArray<FInputActionBinding> result;

#pragma region Abilities
	FInputActionBinding pressFirstAbility("FirstAbility", IE_Pressed);
	FInputActionBinding pressSecondAbility("SecondAbility", IE_Pressed);
	FInputActionBinding pressThirdAbility("ThirdAbility", IE_Pressed);
	FInputActionBinding pressUltimateAbility("UltimateAbility", IE_Pressed);

	FInputActionBinding releaseFirstAbility("FirstAbility", IE_Released);
	FInputActionBinding releaseSecondAbility("SecondAbility", IE_Released);
	FInputActionBinding releaseThirdAbility("ThirdAbility", IE_Released);
	FInputActionBinding releaseUltimateAbility("UltimateAbility", IE_Released);

	pressFirstAbility.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "firstAbility"); });
	pressSecondAbility.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "secondAbility"); });
	pressThirdAbility.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "thirdAbility"); });
	pressUltimateAbility.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "ultimateAbility"); });

	releaseFirstAbility.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "releaseFirstAbilityHandle"); });
	releaseSecondAbility.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "releaseSecondAbilityHandle"); });
	releaseThirdAbility.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "releaseThirdAbilityHandle"); });
	releaseUltimateAbility.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "releaseUltimateAbilityHandle"); });

	result.Add(pressFirstAbility);
	result.Add(pressSecondAbility);
	result.Add(pressThirdAbility);
	result.Add(pressUltimateAbility);

	result.Add(releaseFirstAbility);
	result.Add(releaseSecondAbility);
	result.Add(releaseThirdAbility);
	result.Add(releaseUltimateAbility);
#pragma endregion

#pragma region Selection
	FInputActionBinding pressSelectFirstPlayer("FirstPlayer", IE_Pressed);
	FInputActionBinding pressSelectSecondPlayer("SecondPlayer", IE_Pressed);
	FInputActionBinding pressSelectThirdPlayer("ThirdPlayer", IE_Pressed);
	FInputActionBinding pressSelectFourthPlayer("FourthPlayer", IE_Pressed);

	FInputActionBinding releaseSelectFirstPlayer("FirstPlayer", IE_Released);
	FInputActionBinding releaseSelectSecondPlayer("SecondPlayer", IE_Released);
	FInputActionBinding releaseSelectThirdPlayer("ThirdPlayer", IE_Released);
	FInputActionBinding releaseSelectFourthPlayer("FourthPlayer", IE_Released);

	pressSelectFirstPlayer.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "selectFirstPlayer"); });
	pressSelectSecondPlayer.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "selectSecondPlayer"); });
	pressSelectThirdPlayer.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "selectThirdPlayer"); });
	pressSelectFourthPlayer.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "selectFourthPlayer"); });
	
	releaseSelectFirstPlayer.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "releaseSelectFirstPlayerHandle"); });
	releaseSelectSecondPlayer.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "releaseSelectSecondPlayerHandle"); });
	releaseSelectThirdPlayer.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "releaseSelectThirdPlayerHandle"); });
	releaseSelectFourthPlayer.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "releaseSelectFourthPlayerHandle"); });

	result.Add(pressSelectFirstPlayer);
	result.Add(pressSelectSecondPlayer);
	result.Add(pressSelectThirdPlayer);
	result.Add(pressSelectFourthPlayer);

	result.Add(releaseSelectFirstPlayer);
	result.Add(releaseSelectSecondPlayer);
	result.Add(releaseSelectThirdPlayer);
	result.Add(releaseSelectFourthPlayer);
#pragma endregion

	FInputActionBinding reload("Reload", IE_Pressed);

	FInputActionBinding pressShoot("Shoot", IE_Pressed);
	FInputActionBinding releaseShoot("Shoot", IE_Released);

	FInputActionBinding pressCrouch("Crouch", IE_Pressed);
	FInputActionBinding releaseCrouch("Crouch", IE_Released);

	FInputActionBinding sprint("Sprint", IE_Pressed);
	FInputActionBinding run("Sprint", IE_Released);

	FInputActionBinding pressChangeWeapon("ChangeWeapon", IE_Pressed);
	FInputActionBinding releaseChangeWeapon("ChangeWeapon", IE_Pressed);

	FInputActionBinding	pressAlternative("Alternative", IE_Pressed);
	FInputActionBinding releaseAlternative("Alternative", IE_Released);

	FInputActionBinding	pressAction("Action", IE_Pressed);
	FInputActionBinding releaseAction("Action", IE_Released);

	FInputActionBinding	pressDropWeapon("DropWeapon", IE_Pressed);
	FInputActionBinding releaseDropWeapon("DropWeapon", IE_Released);

	reload.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "reload"); });

	pressShoot.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "shoot"); });
	releaseShoot.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliable(this, "resetShoot"); });

	pressCrouch.ActionDelegate.GetDelegateForManualSet().BindLambda(&IMovementActions::Execute_pressCrouchAction, this);
	releaseCrouch.ActionDelegate.GetDelegateForManualSet().BindLambda(&IMovementActions::Execute_releaseCrouchAction, this);

	sprint.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerUnreliableWithMulticast(this, "sprint"); });
	run.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerUnreliableWithMulticast(this, "run"); });
	
	pressChangeWeapon.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliable(this, "pressChangeWeaponHandle"); });
	releaseChangeWeapon.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "releaseChangeWeaponHandle"); });
	
	pressAlternative.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "pressAlternativeHandle"); });
	releaseAlternative.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "releaseAlternativeHandle"); });
	
	pressAction.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliable(this, "pressActionHandle"); });
	releaseAction.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "releaseActionHandle"); });
	
	pressDropWeapon.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliable(this, "dropWeapon"); });
	releaseDropWeapon.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { MultiplayerUtility::runOnServerReliableWithMulticast(this, "releaseDropWeaponHandle"); });

	result.Add(reload);

	result.Add(pressShoot);
	result.Add(releaseShoot);

	result.Add(pressCrouch);
	result.Add(releaseCrouch);

	result.Add(sprint);
	result.Add(run);

	result.Add(pressChangeWeapon);
	result.Add(releaseChangeWeapon);

	result.Add(pressAlternative);
	result.Add(releaseAlternative);

	result.Add(pressAction);
	result.Add(releaseAction);

	result.Add(pressDropWeapon);
	result.Add(releaseDropWeapon);

	return result;
}

void ALostConnectionCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALostConnectionCharacter, currentAmmoHolding);

	DOREPLIFETIME(ALostConnectionCharacter, firstWeaponSlot);

	DOREPLIFETIME(ALostConnectionCharacter, secondWeaponSlot);
}

void ALostConnectionCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (HasAuthority())
	{
		defaultWeaponSlot = NewObject<UGauss>(this);

		firstWeaponSlot = NewObject<UHipter>(this);
	}
}

bool ALostConnectionCharacter::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool wroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	wroteSomething |= Channel->ReplicateSubobject(firstWeaponSlot, *Bunch, *RepFlags);

	wroteSomething |= Channel->ReplicateSubobject(secondWeaponSlot, *Bunch, *RepFlags);

	return wroteSomething;
}

void ALostConnectionCharacter::BeginPlay()
{
	Super::BeginPlay();

	UWorld* world = GetWorld();

	if (world)
	{
		ALostConnectionCharacter::globalPlayerPtr = UGameplayStatics::GetPlayerController(world, 0)->GetPawn<ALostConnectionCharacter>();
	}
}

void ALostConnectionCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (firstWeaponSlot)
	{
		if (HasAuthority())
		{
			firstWeaponSlot->reduceShootRemainigTime(DeltaSeconds);
		}
	}

	if (secondWeaponSlot)
	{
		if (HasAuthority())
		{
			secondWeaponSlot->reduceShootRemainigTime(DeltaSeconds);
		}
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
	check(PlayerInputComponent);

	TArray<FInputActionBinding> inputs = this->initInputs();

	for (const auto& i : inputs)
	{
		PlayerInputComponent->AddActionBinding(i);
	}

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ALostConnectionCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ALostConnectionCharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ALostConnectionCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ALostConnectionCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ALostConnectionCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ALostConnectionCharacter::LookUpAtRate);
}

void ALostConnectionCharacter::reloadLogic()
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

	currentWeapon->setCurrentMagazineSize(currentMagazineSize + reloadedAmmoRequire);

	if (ammoCount != 9999)
	{
		ammoCount -= reloadedAmmoRequire;
	}
}

ALostConnectionCharacter::ALostConnectionCharacter()
{
	firstWeaponSlot = nullptr;
	secondWeaponSlot = nullptr;
	health = 1000.0f;
	currentHealth = health;
	isAlly = true;

	currentAmmoHolding.Reserve(4);

	for (size_t i = 0; i < 3; i++)
	{
		currentAmmoHolding.Add(0);
	}

	currentAmmoHolding[static_cast<size_t>(ammoTypes::small)] = 720;

	currentAmmoHolding.Add(9999);

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

void ALostConnectionCharacter::pickupAmmo(ammoTypes type, int32 count)
{
	currentAmmoHolding[static_cast<size_t>(type)] += count;
}

void ALostConnectionCharacter::dropWeapon()
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

	this->pressDropWeapon();
}

void ALostConnectionCharacter::pickupWeapon_Implementation(ADroppedWeapon* weaponToEquip)
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

int32 ALostConnectionCharacter::getAmmoHoldingCount(ammoTypes type) const
{
	return currentAmmoHolding[static_cast<size_t>(type)];
}

void ALostConnectionCharacter::firstAbility()
{
	IAbilities::Execute_pressFirstAbility(this);
}

void ALostConnectionCharacter::secondAbility()
{
	IAbilities::Execute_pressSecondAbility(this);
}

void ALostConnectionCharacter::thirdAbility()
{
	IAbilities::Execute_pressThirdAbility(this);
}

void ALostConnectionCharacter::ultimateAbility()
{
	IAbilities::Execute_pressUltimateAbility(this);
}

void ALostConnectionCharacter::releaseFirstAbilityHandle()
{
	IAbilities::Execute_releaseFirstAbility(this);
}

void ALostConnectionCharacter::releaseSecondAbilityHandle()
{
	IAbilities::Execute_releaseSecondAbility(this);
}

void ALostConnectionCharacter::releaseThirdAbilityHandle()
{
	IAbilities::Execute_releaseThirdAbility(this);
}

void ALostConnectionCharacter::releaseUltimateAbilityHandle()
{
	IAbilities::Execute_releaseUltimateAbility(this);
}

void ALostConnectionCharacter::selectFirstPlayer()
{
	IAllySelection::Execute_pressSelectFirstPlayer(this);
}

void ALostConnectionCharacter::selectSecondPlayer()
{
	IAllySelection::Execute_pressSelectSecondPlayer(this);
}

void ALostConnectionCharacter::selectThirdPlayer()
{
	IAllySelection::Execute_pressSelectThirdPlayer(this);
}

void ALostConnectionCharacter::selectFourthPlayer()
{
	IAllySelection::Execute_pressSelectFourthPlayer(this);
}

void ALostConnectionCharacter::releaseSelectFirstPlayerHandle()
{
	IAllySelection::Execute_releaseSelectFirstPlayer(this);
}

void ALostConnectionCharacter::releaseSelectSecondPlayerHandle()
{
	IAllySelection::Execute_releaseSelectSecondPlayer(this);
}

void ALostConnectionCharacter::releaseSelectThirdPlayerHandle()
{
	IAllySelection::Execute_releaseSelectThirdPlayer(this);
}

void ALostConnectionCharacter::releaseSelectFourthPlayerHandle()
{
	IAllySelection::Execute_releaseSelectFourthPlayer(this);
}

void ALostConnectionCharacter::pressChangeWeapon_Implementation()
{

}

void ALostConnectionCharacter::pressAction_Implementation(AActor* object)
{

}

void ALostConnectionCharacter::pressAlternative_Implementation()
{
	if (currentWeapon)
	{
		currentWeapon->alternativeMode();
	}
}

void ALostConnectionCharacter::pressShoot_Implementation()
{

}

void ALostConnectionCharacter::pressDropWeapon_Implementation()
{

}

void ALostConnectionCharacter::pressChangeWeaponHandle()
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

void ALostConnectionCharacter::pressActionHandle()
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

		this->pressAction(hit.Actor.Get());
	}
}

void ALostConnectionCharacter::pressAlternativeHandle()
{
	this->pressAlternative();
}

void ALostConnectionCharacter::releaseChangeWeapon_Implementation()
{

}

void ALostConnectionCharacter::releaseAction_Implementation()
{

}

void ALostConnectionCharacter::releaseAlternative_Implementation()
{

}

void ALostConnectionCharacter::releaseShoot_Implementation()
{

}

void ALostConnectionCharacter::releaseDropWeapon_Implementation()
{

}

void ALostConnectionCharacter::releaseChangeWeaponHandle()
{
	this->releaseChangeWeapon();
}

void ALostConnectionCharacter::releaseActionHandle()
{
	this->releaseAction();
}

void ALostConnectionCharacter::releaseAlternativeHandle()
{
	this->releaseAlternative();
}

void ALostConnectionCharacter::releaseDropWeaponHandle()
{
	this->releaseDropWeapon();
}

FVector ALostConnectionCharacter::getStartActionLineTrace() const
{
	return FollowCamera->GetComponentLocation();
}

FVector ALostConnectionCharacter::getEndActionLineTrace() const
{
	return this->getStartActionLineTrace() + (CameraOffset->TargetArmLength + 200.0f) * FollowCamera->GetForwardVector();
}

float ALostConnectionCharacter::getFlatDamageReduction_Implementation() const
{
	return 200.0f;
}

float ALostConnectionCharacter::getPercentageDamageReduction_Implementation() const
{
	return 25.0f;
}
