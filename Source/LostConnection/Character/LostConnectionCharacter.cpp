// Copyright Epic Games, Inc. All Rights Reserved.

#include "LostConnectionCharacter.h"

#include <algorithm>

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerInput.h"
#include "DrawDebugHelpers.h"

#include "WorldPlaceables/DroppedWeapon.h"

#pragma warning(disable: 4458)

using namespace std;

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

	pressFirstAbility.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { this->runOnServerReliable("firstAbility"); });
	pressSecondAbility.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { this->runOnServerReliable("secondAbility"); });
	pressThirdAbility.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { this->runOnServerReliable("thirdAbility"); });
	pressUltimateAbility.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { this->runOnServerReliable("ultimateAbility"); });

	releaseFirstAbility.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { this->runOnServerReliable("releaseFirstAbilityHandle"); });
	releaseSecondAbility.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { this->runOnServerReliable("releaseSecondAbilityHandle"); });
	releaseThirdAbility.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { this->runOnServerReliable("releaseThirdAbilityHandle"); });
	releaseUltimateAbility.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { this->runOnServerReliable("releaseUltimateAbilityHandle"); });

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

	pressSelectFirstPlayer.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { this->runOnServerReliable("selectFirstPlayer"); });
	pressSelectSecondPlayer.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { this->runOnServerReliable("selectSecondPlayer"); });
	pressSelectThirdPlayer.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { this->runOnServerReliable("selectThirdPlayer"); });
	pressSelectFourthPlayer.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { this->runOnServerReliable("selectFourthPlayer"); });

	releaseSelectFirstPlayer.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { this->runOnServerReliable("releaseSelectFirstPlayerHandle"); });
	releaseSelectSecondPlayer.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { this->runOnServerReliable("releaseSelectSecondPlayerHandle"); });
	releaseSelectThirdPlayer.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { this->runOnServerReliable("releaseSelectThirdPlayerHandle"); });
	releaseSelectFourthPlayer.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { this->runOnServerReliable("releaseSelectFourthPlayerHandle"); });

	result.Add(pressSelectFirstPlayer);
	result.Add(pressSelectSecondPlayer);
	result.Add(pressSelectThirdPlayer);
	result.Add(pressSelectFourthPlayer);

	result.Add(releaseSelectFirstPlayer);
	result.Add(releaseSelectSecondPlayer);
	result.Add(releaseSelectThirdPlayer);
	result.Add(releaseSelectFourthPlayer);
#pragma endregion

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

	pressCrouch.ActionDelegate.GetDelegateForManualSet().BindLambda(&IMovementActions::Execute_pressCrouchAction, this);
	releaseCrouch.ActionDelegate.GetDelegateForManualSet().BindLambda(&IMovementActions::Execute_releaseCrouchAction, this);

	sprint.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { this->runOnServerUnreliable("sprint"); });
	run.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { this->runOnServerUnreliable("run"); });

	pressChangeWeapon.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { this->runOnServerReliable("pressChangeWeaponHandle"); });
	releaseChangeWeapon.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { this->runOnServerReliable("releaseChangeWeaponHandle"); });

	pressAlternative.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { this->runOnServerReliable("pressAlternativeHandle"); });
	releaseAlternative.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { this->runOnServerReliable("releaseAlternativeHandle"); });

	pressAction.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { this->runOnServerReliable("pressActionHandle"); });
	releaseAction.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { this->runOnServerReliable("releaseActionHandle"); });

	pressDropWeapon.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { this->runOnServerReliable("dropWeapon"); });
	releaseDropWeapon.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() { this->runOnServerReliable("releaseDropWeaponHandle"); });

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

	DOREPLIFETIME(ALostConnectionCharacter, health);

	DOREPLIFETIME(ALostConnectionCharacter, currentHealth);

	DOREPLIFETIME(ALostConnectionCharacter, isAlly);

	DOREPLIFETIME(ALostConnectionCharacter, currentAmmoHolding);

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

void ALostConnectionCharacter::runMulticastReliable_Implementation(const FName& methodName)
{
	FTimerDelegate delegate;

	delegate.BindUFunction(this, methodName);

	delegate.Execute();
}

void ALostConnectionCharacter::runOnServerReliable_Implementation(const FName& methodName)
{
	this->runMulticastReliable(methodName);
}

void ALostConnectionCharacter::runMulticastUnreliable_Implementation(const FName& methodName)
{
	FTimerDelegate delegate;

	delegate.BindUFunction(this, methodName);

	delegate.Execute();
}

void ALostConnectionCharacter::runOnServerUnreliable_Implementation(const FName& methodName)
{
	this->runMulticastUnreliable(methodName);
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

	TArray<FInputActionBinding> inputs = this->initInputs();

	for (const auto& i : inputs)
	{
		PlayerInputComponent->AddActionBinding(i);
	}

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ALostConnectionCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ALostConnectionCharacter::StopJumping);

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

void ALostConnectionCharacter::sprint()
{
	this->changeMaxSpeed(575.0f);

	IMovementActions::Execute_sprintAction(this);
}

void ALostConnectionCharacter::run()
{
	this->changeMaxSpeed(450.0f);

	IMovementActions::Execute_runAction(this);
}

void ALostConnectionCharacter::changeMaxSpeed_Implementation(float speed)
{
	GetCharacterMovement()->MaxWalkSpeed = speed;
}

void ALostConnectionCharacter::reloadLogicMulticast_Implementation()
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

void ALostConnectionCharacter::reloadAnimationMulticast_Implementation()
{
	this->reloadAnimation();
}

void ALostConnectionCharacter::reloadAnimation_Implementation()
{

}

void ALostConnectionCharacter::reloadLogic_Implementation()
{
	this->reloadLogicMulticast();
}

void ALostConnectionCharacter::shootLogic()
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

void ALostConnectionCharacter::resetShootLogic()
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
	NetUpdateFrequency = 60;

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

void ALostConnectionCharacter::shoot()
{
	this->runOnServerUnreliable("shootLogic");
}

void ALostConnectionCharacter::resetShoot()
{
	this->runOnServerReliable("resetShootLogic");
}

void ALostConnectionCharacter::reload_Implementation()
{
	this->reloadAnimationMulticast();
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

void ALostConnectionCharacter::dropWeapon()
{
	// if (currentWeapon == defaultWeaponSlot)
	// {
	// 	return;
	// }

	UWorld* world = GetWorld();

	if (!world)
	{
		return;
	}

	ADroppedWeapon* droppedWeapon = world->SpawnActorDeferred<ADroppedWeapon>(ADroppedWeapon::StaticClass(), {});
	FTransform spawnPoint(currentWeaponMesh->GetComponentRotation(), currentWeaponMesh->GetComponentLocation() + 100.0f * GetActorForwardVector());

	droppedWeapon->setWeapon(currentWeapon);

	if (currentWeapon && currentWeapon == firstWeaponSlot)
	{
		currentWeapon = firstWeaponSlot = nullptr;
	}
	else if (currentWeapon && currentWeapon == secondWeaponSlot)
	{
		currentWeapon = secondWeaponSlot = nullptr;
	}

	droppedWeapon->FinishSpawning(spawnPoint);

	this->pressDropWeapon();
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
	FVector start = FollowCamera->GetComponentLocation();
	FVector end = start + (CameraOffset->TargetArmLength + 200.0f) * FollowCamera->GetForwardVector();
	FCollisionQueryParams ignoreParameters;
	IActionable* object = nullptr;

	ignoreParameters.AddIgnoredActor(this);

	world->LineTraceSingleByChannel(hit, start, end, ECollisionChannel::ECC_Visibility, ignoreParameters);

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

float ALostConnectionCharacter::getFlatDamageReduction_Implementation() const
{
	return 200.0f;
}

float ALostConnectionCharacter::getPercentageDamageReduction_Implementation() const
{
	return 25.0f;
}