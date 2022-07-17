// Copyright (c) 2021 Use Your Imagination

#include "BaseCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "NiagaraFunctionLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "Algo/ForEach.h"
#include "Algo/Find.h"

#include "Statuses/BaseTriggerStatus.h"
#include "Statuses/Ailments/SwarmAilment.h"
#include "Utility/InitializationUtility.h"
#include "AI/BaseBot.h"
#include "BaseDrone.h"
#include "Interfaces/Gameplay/Descriptions/Base/DamageInflictor.h"
#include "Constants/Constants.h"
#include "Utility/Utility.h"
#include "Interfaces/Animations/WeaponUser.h"
#include "EnergyShields/EmptyEnergyShield.h"
#include "Utility/Blueprints/UtilityBlueprintFunctionLibrary.h"

#include "Utility/MultiplayerUtility.h"

#pragma warning(disable: 4458)

static TArray<UInventoryCell*> emptyCells = {};
static TArray<TObjectPtr<UInventoryCell>> emptyObjectCells = {};

void ABaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseCharacter, energyShield);

	DOREPLIFETIME(ABaseCharacter, health);

	DOREPLIFETIME(ABaseCharacter, currentHealth);

	DOREPLIFETIME(ABaseCharacter, reservedHealth);

	DOREPLIFETIME(ABaseCharacter, defaultMovementSpeed);

	DOREPLIFETIME(ABaseCharacter, sprintMovementSpeed);

	DOREPLIFETIME(ABaseCharacter, isAlly);

	DOREPLIFETIME(ABaseCharacter, isDead);

	DOREPLIFETIME(ABaseCharacter, currentWeapon);

	DOREPLIFETIME(ABaseCharacter, statuses);

	DOREPLIFETIME(ABaseCharacter, swarm);
}

bool ABaseCharacter::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool wroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	if (currentWeapon)
	{
		wroteSomething |= Channel->ReplicateSubobject(currentWeapon, *Bunch, *RepFlags);

		wroteSomething |= currentWeapon->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	if (energyShield)
	{
		wroteSomething |= Channel->ReplicateSubobject(energyShield, *Bunch, *RepFlags);

		wroteSomething |= energyShield->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	for (const auto& status : statuses)
	{
		wroteSomething |= Channel->ReplicateSubobject(status, *Bunch, *RepFlags);

		wroteSomething |= status->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	if (swarm.IsValid())
	{
		wroteSomething |= Channel->ReplicateSubobject(swarm.Get(), *Bunch, *RepFlags);

		wroteSomething |= swarm->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	return wroteSomething;
}

void ABaseCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	USkeletalMeshComponent* mesh = GetMesh();
	TArray<UMaterialInterface*> materials = mesh->GetMaterials();

	timelines = NewObject<UTimelinesUtility>(this);
	deathMaskRenderTexture = NewObject<UTextureRenderTarget2D>(this);

	deathMaskRenderTexture->InitCustomFormat(256, 256, EPixelFormat::PF_G16, false);

	for (int32 materialIndex = 0; materialIndex < materials.Num(); materialIndex++)
	{
		mesh->CreateAndSetMaterialInstanceDynamicFromMaterial(materialIndex, materials[materialIndex]);
	}

	if (HasAuthority())
	{
		if (IsValid(energyShieldClass))
		{
			energyShield = NewObject<UBaseEnergyShield>(this, energyShieldClass);

			energyShield->init(this);
		}
	}
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	healthBarWidget->GetWidget()->SetVisibility(ESlateVisibility::Hidden);

	if (HasAuthority())
	{
		ALostConnectionPlayerState* playerState = Utility::getPlayerState(this);
		TArray<FAmmoData>& spareAmmo = playerState->getSpareAmmoArray();

		if (!spareAmmo.Num())
		{
			spareAmmo =
			{
				FAmmoData(EAmmoType::small, this->getDefaultSmallAmmoCount()),
				FAmmoData(EAmmoType::large, this->getDefaultLargeAmmoCount()),
				FAmmoData(EAmmoType::energy, this->getDefaultEnergyAmmoCount()),
				FAmmoData(EAmmoType::defaultType, 9999)
			};
		}

		this->onEnergyShieldUpdate();
	}

	this->onHealthChange();
}

void ABaseCharacter::deathMaterialTimerUpdate_Implementation()
{

}

void ABaseCharacter::onCurrentWeaponChange()
{
	TObjectPtr<UAnimInstance> animInstance = GetMesh()->GetAnimInstance();

	this->updateWeaponMesh();

	if (currentWeapon)
	{
		currentWeapon->updateTimeBetweenShots();

		if (HasAuthority())
		{
			if (TObjectPtr<AInventory> inventory = Utility::getPlayerState(this)->getInventory())
			{
				inventory->updateActiveWeaponModules();
			}
		}
	}

	if (animInstance->Implements<UWeaponUser>())
	{
		IWeaponUser::Execute_weaponUpdate(animInstance, currentWeapon);
	}
}

void ABaseCharacter::onEnergyShieldUpdate()
{
	TObjectPtr<UHealthBarWidget> widget = this->getHealthBarWidget();

	if (widget)
	{
		widget->getImage()->GetDynamicMaterial()->SetVectorParameterValue("ShieldColor", energyShield->getEnergyShieldColor());
	}

	if (GetController() && Cast<ABaseDrone>(this))
	{
		if (!Utility::getPlayerState(this)->getCurrentUI())
		{
			Cast<ABaseDrone>(this)->initDefaultUI();
		}

		TObjectPtr<ULostConnectionUI> ui = Cast<ULostConnectionUI>(Utility::getPlayerState(this)->getCurrentUI());

		if (ui)
		{
			ui->onEnergyShieldUpdate();
		}
	}

	UUtilityBlueprintFunctionLibrary::setMaterialLinearColorParameter(GetMesh(), "ShieldColor", energyShield->getEnergyShieldColor());
}

void ABaseCharacter::onHealthChange()
{
	TObjectPtr<UHealthBarWidget> widget = this->getHealthBarWidget();

	if (widget.IsNull())
	{
		return;
	}

	TObjectPtr<UMaterialInstanceDynamic> healthBarMaterial = widget->getImage()->GetDynamicMaterial();

	if (healthBarMaterial && energyShield)
	{
		healthBarMaterial->SetScalarParameterValue("LifeToShieldMultiplier", health / energyShield->getCapacity());
	}
}

void ABaseCharacter::onCurrentHealthChange()
{
	if (currentHealth == 0.0f)
	{
		if (HasAuthority() && !isDead)
		{
			this->notifyDeathEvents(this);

			if (currentHealth != 0.0f)
			{
				return;
			}

			isDead = true;

			MultiplayerUtility::runOnServerReliableWithMulticast(this, "death");
		}

		this->setHealthBarVisibility(ESlateVisibility::Hidden);

		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	}
	else if (this->isDamaged() && !Utility::isYourPawn(this))
	{
		this->setHealthBarVisibility(ESlateVisibility::Visible);

		this->updateHealthBar();
	}
	else
	{
		this->setHealthBarVisibility(ESlateVisibility::Hidden);
	}
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

		currentWeaponMesh->SetAnimClass(nullptr);
	}
}

void ABaseCharacter::holdSprint()
{
	this->setMaxSpeed(sprintMovementSpeed);

	sprintHold = true;
}

void ABaseCharacter::releaseSprint()
{
	this->setMaxSpeed(defaultMovementSpeed);

	sprintHold = false;
}

void ABaseCharacter::Jump()
{
	Super::Jump();

	jumpHold = true;

	IMovementActions::Execute_pressJumpAction(this);
}

void ABaseCharacter::StopJumping()
{
	Super::StopJumping();

	jumpHold = false;
}

void ABaseCharacter::setMaxSpeed(float speed)
{
	GetCharacterMovement()->MaxWalkSpeed = speed;
}

void ABaseCharacter::reloadVisual()
{

}

void ABaseCharacter::reloadLogic()
{
	if (!currentWeapon)
	{
		return;
	}

	int32 currentMagazineSize = currentWeapon->getCurrentMagazineSize();
	int32 magazineSize = currentWeapon->getMagazineSize();
	EAmmoType ammoType = currentWeapon->getAmmoType();

	if (currentMagazineSize == magazineSize)
	{
		return;
	}

	TArray<FAmmoData>& spareAmmo = Utility::getPlayerState(this)->getSpareAmmoArray();
	int32& ammoCount = Algo::FindByPredicate(spareAmmo, [&ammoType](FAmmoData& data) { return data.ammoType == ammoType; })->ammoCount;

	if (!ammoCount)
	{
		return;
	}

	int32 reloadedAmmoRequire = FMath::Min(magazineSize - currentMagazineSize, ammoCount);

	currentWeapon->setCurrentMagazineSize(currentMagazineSize + reloadedAmmoRequire);

	if (ammoCount != 9999)
	{
		ammoCount -= reloadedAmmoRequire;
	}
}

void ABaseCharacter::deathVisual()
{

}

void ABaseCharacter::deathLogic()
{
	if (!GetController())
	{
		return;
	}

	TObjectPtr<ALostConnectionPlayerState> playerState = Utility::getPlayerState(this);

	playerState->returnAmmoToSpare(playerState->getPrimaryWeapon());

	playerState->returnAmmoToSpare(playerState->getSecondaryWeapon());
}

void ABaseCharacter::updateCharacterVisual()
{
	if (swarm.IsValid())
	{
		TObjectPtr<UHealthBarWidget> widget = this->getHealthBarWidget();

		if (!widget)
		{
			return;
		}

		widget->getImage()->GetDynamicMaterial()->SetScalarParameterValue("ThresholdPercent", swarm->getThreshold());
	}
}

TObjectPtr<UHealthBarWidget> ABaseCharacter::getHealthBarWidget() const
{
	return Cast<UHealthBarWidget>(healthBarWidget->GetWidget());
}

TArray<TScriptInterface<IOnDeathEvent>>& ABaseCharacter::getDeathEvents()
{
	return deathEvents;
}

TArray<TScriptInterface<IOnHitEvent>>& ABaseCharacter::getHitEvents()
{
	return hitEvents;
}

TArray<TScriptInterface<IOnShotEvent>>& ABaseCharacter::getShotEvents()
{
	return shotEvents;
}

TArray<TScriptInterface<IOnTakeDamageEvent>>& ABaseCharacter::getTakeDamageEvents()
{
	return takeDamageEvents;
}

void ABaseCharacter::runReloadLogic()
{
	Utility::executeOnlyOnServerFromMulticast(this, [this]()
		{
			this->reloadLogic();

			IReload::Execute_reloadEventLogic(this);
		});
}

void ABaseCharacter::runDeathLogic()
{
	Utility::executeOnlyOnServerFromMulticast(this, [this]()
		{
			this->deathLogic();

			IDeath::Execute_deathEventLogic(this);
		});
}

ABaseCharacter::ABaseCharacter() :
	energyShieldClass(UEmptyEnergyShield::StaticClass()),
	defaultMovementSpeed(450.0f),
	sprintMovementSpeed(575.0f),
	isDead(false),
	defaultSmallAmmoCount(700),
	defaultLargeAmmoCount(240),
	defaultEnergyAmmoCount(50)
{
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> underStatusFinder(TEXT("NiagaraSystem'/Game/Assets/FX/Statuses/Common/NPS_SatusState.NPS_SatusState'"));
	static ConstructorHelpers::FClassFinder<UUserWidget> healthBarWidgetFinder(TEXT("/Game/UI/WidgetComponents/BP_HealthBarWidget"));

	PrimaryActorTick.bCanEverTick = true;
	NetUpdateFrequency = UConstants::actorNetUpdateFrequency;
	bReplicates = true;

	UCapsuleComponent* capsule = GetCapsuleComponent();
	USkeletalMeshComponent* mesh = GetMesh();
	UCharacterMovementComponent* movement = GetCharacterMovement();

	capsule->InitCapsuleSize(42.0f, 96.0f);

	capsule->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);

	capsule->SetIsReplicated(true);

	mesh->SetGenerateOverlapEvents(true);

	mesh->SetCollisionResponseToChannel(UConstants::shotThroughChannel, ECollisionResponse::ECR_Overlap);

	mesh->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);

	mesh->SetIsReplicated(true);

	movement->bOrientRotationToMovement = true;
	movement->RotationRate = UConstants::rotationRate;
	movement->JumpZVelocity = UConstants::jumpVelocity;
	movement->AirControl = 1.0f;
	movement->MaxWalkSpeed = defaultMovementSpeed;
	movement->MaxWalkSpeedCrouched = defaultMovementSpeed / UConstants::crouchMaxWalkSpeedCoefficient;
	movement->bCanWalkOffLedgesWhenCrouching = true;

	movement->GetNavAgentPropertiesRef().bCanCrouch = true;

	currentWeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("CurrentWeaponMesh");

	currentWeaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	currentWeaponMesh->SetupAttachment(mesh, "Hand_WeaponSocket_R");

	magazine = CreateDefaultSubobject<UStaticMeshComponent>("Magazine");

	magazine->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	magazine->SetupAttachment(currentWeaponMesh);

	underStatusComponent = CreateDefaultSubobject<UNiagaraComponent>("UnderStatus");

	underStatusComponent->SetAsset(underStatusFinder.Object);

	underStatusComponent->SetupAttachment(mesh);

	underStatusComponent->AddLocalOffset(FVector(0.0f, 0.0f, this->getCapsuleComponent()->GetUnscaledCapsuleHalfHeight()));

	healthBarWidget = CreateDefaultSubobject<UWidgetComponent>("HealthBarWidget");

	healthBarWidget->SetDrawSize({ 175.0f, 40.0f });

	healthBarWidget->SetWidgetSpace(EWidgetSpace::Screen);

	healthBarWidget->SetWidgetClass(healthBarWidgetFinder.Class);

	healthBarWidget->SetupAttachment(mesh);

	healthBarWidget->AddLocalOffset(FVector(0.0f, 0.0f, 187.0f));

	healthBarWidget->SetPivot({ 0.5f, 1.0f });

#pragma region BlueprintFunctionLibrary
	isReloading = false;

	jumpHold = false;

	sprintHold = false;

	crouchHold = false;
#pragma endregion
}

void ABaseCharacter::changeToDefaultWeapon_Implementation()
{
	currentWeapon = Utility::getPlayerState(this)->getDefaultWeapon();

	this->onCurrentWeaponChange();
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

void ABaseCharacter::playAnimation_Implementation(UAnimMontage* animation)
{
	PlayAnimMontage(animation);
}

void ABaseCharacter::updateCharacterVisualCall()
{
	MultiplayerUtility::runOnServerUnreliableWithMulticast(this, "updateCharacterVisual");
}

void ABaseCharacter::setHealth_Implementation(float newHealth)
{
	health = newHealth;
}

void ABaseCharacter::setReservedHealth_Implementation(float newReservedHealth)
{
	reservedHealth = newReservedHealth;

	float maxCurrentHealth = health - reservedHealth;

	if (currentHealth > maxCurrentHealth)
	{
		this->setCurrentHealth(maxCurrentHealth);
	}
}

void ABaseCharacter::setDefaultMovementSpeed_Implementation(float speed)
{
	defaultMovementSpeed = speed;

	GetCharacterMovement()->MaxWalkSpeedCrouched = defaultMovementSpeed / 3;
}

void ABaseCharacter::setSprintMovementSpeed_Implementation(float speed)
{
	sprintMovementSpeed = speed;
}

void ABaseCharacter::setIsAlly_Implementation(bool newIsAlly)
{
	isAlly = newIsAlly;
}

void ABaseCharacter::setIsDead_Implementation(bool newIsDead)
{
	isDead = newIsDead;
}

UBaseWeapon* ABaseCharacter::getDefaultWeapon()
{
	return Utility::getPlayerState(this)->getDefaultWeapon();
}

float ABaseCharacter::getHealth() const
{
	return health;
}

float ABaseCharacter::getReservedHealth() const
{
	return reservedHealth;
}

float ABaseCharacter::getDefaultMovementSpeed() const
{
	return defaultMovementSpeed;
}

float ABaseCharacter::getSprintMovementSpeed() const
{
	return sprintMovementSpeed;
}

TObjectPtr<USkeletalMeshComponent> ABaseCharacter::getCurrentWeaponMeshComponent() const
{
	return currentWeaponMesh;
}

TObjectPtr<UBaseWeapon> ABaseCharacter::getCurrentWeapon() const
{
	return currentWeapon;
}

int32 ABaseCharacter::getWeaponCount() const
{
	return StaticCast<bool>(Utility::getPlayerState(this)->getDefaultWeapon());
}

const TWeakObjectPtr<USwarmAilment>& ABaseCharacter::getSwarm() const
{
	return swarm;
}

TArray<TWeakObjectPtr<UBaseWeapon>> ABaseCharacter::getWeapons() const
{
	UBaseWeapon* defaultWeapon = Utility::getPlayerState(this)->getDefaultWeapon();

	if (defaultWeapon)
	{
		return TArray<TWeakObjectPtr<UBaseWeapon>> { defaultWeapon };
	}

	return TArray<TWeakObjectPtr<UBaseWeapon>>();
}

int32 ABaseCharacter::getDefaultSmallAmmoCount() const
{
	return defaultSmallAmmoCount;
}

int32 ABaseCharacter::getDefaultLargeAmmoCount() const
{
	return defaultLargeAmmoCount;
}

int32 ABaseCharacter::getDefaultEnergyAmmoCount() const
{
	return defaultEnergyAmmoCount;
}

float ABaseCharacter::getStartEnergyShieldCapacity() const
{
	return startEnergyShieldCapacity;
}

TimersUtility& ABaseCharacter::getTimers()
{
	return timers;
}

void ABaseCharacter::shoot_Implementation()
{
	if (this->isWeaponEquipped())
	{
		currentWeapon->startShoot();
	}
}

void ABaseCharacter::resetShoot_Implementation()
{
	if (this->isWeaponEquipped())
	{
		currentWeapon->resetShoot(currentWeaponMesh);
	}
}

void ABaseCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	timelines->Tick(DeltaSeconds);

	TObjectPtr<ALostConnectionPlayerState> playerState = Utility::getPlayerState(this);

	if (HasAuthority() && !isDead && playerState)
	{
		TArray<TObjectPtr<UBaseStatus>> statusesToRemove;
		TObjectPtr<UBaseWeapon> defaultWeapon = playerState->getDefaultWeapon();

		if (defaultWeapon)
		{
			defaultWeapon->Tick(DeltaSeconds);
		}

		for (auto& status : statuses)
		{
			if (!status->Tick(DeltaSeconds))
			{
				statusesToRemove.Add(status);
			}
		}

		for (const auto& statusToRemove : statusesToRemove)
		{
			statuses.Remove(statusToRemove);

			statusToRemove->postRemove();
		}

		statusesToRemove.Empty();

		timers.processTimers(DeltaSeconds);

		energyShield->Tick(DeltaSeconds);
	}
}

void ABaseCharacter::takeDamageFromInflictor_Implementation(const TScriptInterface<IDamageInflictor>& inflictor)
{
	this->notifyTakeDamageEvents(this);

	const TObjectPtr<AController>& instigator = inflictor->getDamageInstigator();
	float tem = currentHealth - energyShield->takeDamageFromInflictor(inflictor);

	if (tem < 0.0f)
	{
		this->setCurrentHealth(0.0f);
	}
	else
	{
		this->setCurrentHealth(tem);
	}

	if (TObjectPtr<AController> controller = GetController())
	{
		controller->TakeDamage(inflictor->calculateTotalDamage(), FDamageEvent(), instigator, instigator->GetPawn());
	}

	TakeDamage(inflictor->calculateTotalDamage(), FDamageEvent(), instigator, instigator->GetPawn());
}

void ABaseCharacter::impactAction_Implementation(AAmmo* ammo, const FHitResult& hit)
{
	if (isAlly != ammo->getIsAlly())
	{
		this->notifyHitEvents(ammo->getOwner(), this);

		this->takeDamageFromInflictor(ammo->getAilmentInflictorUtility());

		this->statusInflictorImpactAction(ammo->getAilmentInflictorUtility(), hit);
	}
}

void ABaseCharacter::spawnStatusVFX_Implementation(UNiagaraSystem* statusVFX, const FHitResult& hit)
{
	UNiagaraFunctionLibrary::SpawnSystemAttached
	(
		statusVFX,
		this->getMeshComponent(),
		NAME_None,
		hit.Location,
		FRotator::ZeroRotator,
		EAttachLocation::Type::KeepWorldPosition,
		true,
		true,
		ENCPoolMethod::AutoRelease
	);
}

void ABaseCharacter::addStatus(TObjectPtr<UBaseStatus> status)
{
	statuses.Add(status);
}

void ABaseCharacter::applySwarmAilment(USwarmAilment* swarm)
{
	this->swarm = swarm;
}

void ABaseCharacter::statusInflictorImpactAction(const TScriptInterface<IStatusInflictor>& inflictor, const FHitResult& hit)
{
	TArray<TObjectPtr<UBaseStatus>> statusesToRemove;

	for (auto& status : statuses)
	{
		TObjectPtr<UBaseTriggerStatus> trigger = Cast<UBaseTriggerStatus>(status);

		if (trigger)
		{
			if (trigger->applyEffect(this, hit) && trigger->getIsOnceTriggered())
			{
				statusesToRemove.Add(trigger);
			}
		}
	}

	for (const auto& statusToRemove : statusesToRemove)
	{
		statuses.Remove(statusToRemove);

		statusToRemove->postRemove();
	}

	statusesToRemove.Empty();

	if (TScriptInterface<IAilmentInflictor> ailmentInflictor = Cast<IAilmentInflictor>(inflictor))
	{
		if ((hit.PhysMaterial.IsValid() && UPhysicalMaterial::DetermineSurfaceType(hit.PhysMaterial.Get()) == EPhysicalSurface::SurfaceType1) || ailmentInflictor->getCrushingHitProc())
		{
			TObjectPtr<UBaseStatus> ailment = InitializationUtility::createDefaultAilment(ailmentInflictor->getDamageType(), this);
			
			if (TScriptInterface<IDamageInflictorHolder> damageInflictor = ailment.Get())
			{
				damageInflictor->getDamageInflictorUtility()->setDamageInstigator(inflictor->getDamageInstigator());
			}

			ailment->applyStatus(inflictor, this, hit);
		}
	}
}

void ABaseCharacter::setCurrentHealth_Implementation(float newCurrentHealth)
{
	if (swarm.IsValid())
	{
		float newPercentHealth = Utility::toPercent(newCurrentHealth / health);

		if (newPercentHealth <= swarm->getThreshold())
		{
			FHitResult hit(this, GetMesh(), GetActorLocation(), {});

			swarm->applyEffect(this, hit);

			currentHealth = 0.0f;

			this->onCurrentHealthChange();

			return;
		}
	}

	currentHealth = newCurrentHealth;

	this->onCurrentHealthChange();
}

void ABaseCharacter::setUnderStatusIntVariable_Implementation(const FString& key, int32 value)
{
	underStatusComponent->SetNiagaraVariableInt(key, value);
}

float ABaseCharacter::getCurrentHealth() const
{
	return currentHealth;
}

const TArray<TObjectPtr<UBaseStatus>>& ABaseCharacter::getStatuses() const
{
	return statuses;
}

bool ABaseCharacter::getIsAlly() const
{
	return isAlly;
}

float ABaseCharacter::getFlatDamageReduction_Implementation() const
{
	return 200.0f;
}

float ABaseCharacter::getPercentageDamageReduction_Implementation() const
{
	return 25.0f;
}

float ABaseCharacter::getTotalLifePool() const
{
	return health + energyShield->getCapacity();
}

float ABaseCharacter::getLifePool() const
{
	return health;
}

float ABaseCharacter::getEnergyShieldPool() const
{
	return energyShield->getCapacity();
}

float ABaseCharacter::getTotalLifePercentDealt(const TScriptInterface<IDamageInflictor>& inflictor) const
{
	float pool = this->getTotalLifePool();

	return Utility::toPercent(1.0f - (pool - inflictor->calculateTotalDamage()) / pool);
}

float ABaseCharacter::getLifePercentDealt(const TScriptInterface<IDamageInflictor>& inflictor) const
{
	return Utility::toPercent(1.0f - (health - inflictor->calculateTotalDamage()) / health);
}

float ABaseCharacter::getEnergyShieldPercentDealt(const TScriptInterface<IDamageInflictor>& inflictor) const
{
	float capacity = energyShield->getCapacity();

	return Utility::toPercent(1.0f - (capacity - inflictor->calculateTotalDamage()) / capacity);
}

USkeletalMeshComponent* ABaseCharacter::getMeshComponent()
{
	return GetMesh();
}

UCapsuleComponent* ABaseCharacter::getCapsuleComponent()
{
	return GetCapsuleComponent();
}

void ABaseCharacter::deathTimelineUpdate_Implementation(float value)
{

}

void ABaseCharacter::deathTimelineFinished_Implementation()
{

}

const TArray<UInventoryCell*>& ABaseCharacter::getPersonalEquippedModules() const
{
	if (TObjectPtr<ALostConnectionPlayerState> playerState = Utility::getPlayerState(this))
	{
		return playerState->getPersonalEquippedModules();
	}

	UE_LOG(LogLostConnection, Warning, TEXT("Can't get player state in function: %s"), __FUNCTION__);

	return emptyCells;
}

const TArray<UInventoryCell*>& ABaseCharacter::getPersonalUnequippedModules() const
{
	if (TObjectPtr<ALostConnectionPlayerState> playerState = Utility::getPlayerState(this))
	{
		return playerState->getPersonalUnequippedModules();
	}

	UE_LOG(LogLostConnection, Warning, TEXT("Can't get player state in function: %s"), __FUNCTION__);

	return emptyCells;
}

const TArray<TObjectPtr<UInventoryCell>>& ABaseCharacter::getActivePersonalModules() const
{
	if (TObjectPtr<ALostConnectionPlayerState> playerState = Utility::getPlayerState(this))
	{
		return playerState->getInventory()->getActivePersonalModules();
	}

	UE_LOG(LogLostConnection, Warning, TEXT("Can't get player state in function: %s"), __FUNCTION__);

	return emptyObjectCells;
}

const TArray<UInventoryCell*>& ABaseCharacter::getWeaponModules() const
{
	if (TObjectPtr<ALostConnectionPlayerState> playerState = Utility::getPlayerState(this))
	{
		return playerState->getWeaponModules();
	}

	UE_LOG(LogLostConnection, Warning, TEXT("Can't get player state in function: %s"), __FUNCTION__);

	return emptyCells;
}

const TArray<TObjectPtr<UInventoryCell>>& ABaseCharacter::getActiveWeaponModules() const
{
	if (TObjectPtr<ALostConnectionPlayerState> playerState = Utility::getPlayerState(this))
	{
		return playerState->getInventory()->getActiveWeaponModules();
	}

	UE_LOG(LogLostConnection, Warning, TEXT("Can't get player state in function: %s"), __FUNCTION__);

	return emptyObjectCells;
}
