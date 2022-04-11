// Copyright (c) 2021 Use-your-imagination

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
#include "BaseBot.h"
#include "BaseDrone.h"
#include "Interfaces/Gameplay/Descriptions/Base/DamageInflictor.h"
#include "Constants/Constants.h"
#include "Utility/Utility.h"
#include "Interfaces/Animations/WeaponUser.h"
#include "EnergyShields/EmptyEnergyShield.h"
#include "Utility/Blueprints/UtilityBlueprintFunctionLibrary.h"

#include "Utility/MultiplayerUtility.h"

#pragma warning(disable: 4458)

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
}

bool ABaseCharacter::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool wroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	if (IsValid(currentWeapon))
	{
		wroteSomething |= Channel->ReplicateSubobject(currentWeapon, *Bunch, *RepFlags);

		wroteSomething |= currentWeapon->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	if (IsValid(energyShield))
	{
		wroteSomething |= Channel->ReplicateSubobject(energyShield, *Bunch, *RepFlags);

		wroteSomething |= energyShield->ReplicateSubobjects(Channel, Bunch, RepFlags);
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
		energyShield = NewObject<UBaseEnergyShield>(this, energyShieldClass);

		energyShield->init(this);
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
	UAnimInstance* animInstance = GetMesh()->GetAnimInstance();

	this->updateWeaponMesh();

	if (currentWeapon)
	{
		currentWeapon->setOwner(this);

		currentWeapon->updateTimeBetweenShots();
	}

	if (animInstance->Implements<UWeaponUser>())
	{
		IWeaponUser::Execute_weaponUpdate(animInstance, currentWeapon);
	}
}

void ABaseCharacter::onEnergyShieldUpdate()
{
	UHealthBarWidget* widget = this->getHealthBarWidget();

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

		ULostConnectionUI* ui = Cast<ULostConnectionUI>(Utility::getPlayerState(this)->getCurrentUI());

		if (ui)
		{
			ui->onEnergyShieldUpdate();
		}
	}

	UUtilityBlueprintFunctionLibrary::setMaterialLinearColorParameter(GetMesh(), "ShieldColor", energyShield->getEnergyShieldColor());
}

void ABaseCharacter::onHealthChange()
{
	UHealthBarWidget* widget = this->getHealthBarWidget();

	if (!widget)
	{
		return;
	}

	UMaterialInstanceDynamic* healthBarMaterial = widget->getImage()->GetDynamicMaterial();

	if (IsValid(healthBarMaterial) && IsValid(energyShield))
	{
		healthBarMaterial->SetScalarParameterValue("LifeToShieldMultiplier", health / energyShield->getCapacity());
	}
}

void ABaseCharacter::onCurrentHealthChange()
{
	if (currentHealth == 0.0f)
	{
		this->setHealthBarVisibility(ESlateVisibility::Hidden);

		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);

		if (HasAuthority() && !isDead)
		{
			Algo::ForEach
			(
				deathEvents,
				[](const TScriptInterface<IOnDeathEvent>& event) { event->deathEventAction(); }
			);

			isDead = true;

			MultiplayerUtility::runOnServerReliableWithMulticast(this, "death");
		}
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

	ALostConnectionPlayerState* playerState = Utility::getPlayerState(this);

	playerState->returnAmmoToSpare(playerState->getPrimaryWeapon());

	playerState->returnAmmoToSpare(playerState->getSecondaryWeapon());
}

void ABaseCharacter::updateCharacterVisual()
{
	if (swarm.IsValid())
	{
		UHealthBarWidget* widget = this->getHealthBarWidget();

		if (!widget)
		{
			return;
		}

		widget->getImage()->GetDynamicMaterial()->SetScalarParameterValue("ThresholdPercent", swarm->getThreshold());
	}
}

UHealthBarWidget* ABaseCharacter::getHealthBarWidget() const
{
	return Cast<UHealthBarWidget>(healthBarWidget->GetWidget());
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
	defaultSmallAmmoCount(UConstants::defaultSmallAmmoMaxCount),
	defaultLargeAmmoCount(UConstants::defaultLargeAmmoMaxCount),
	defaultEnergyAmmoCount(UConstants::defaultEnergyAmmoMaxCount)
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

USkeletalMeshComponent* ABaseCharacter::getCurrentWeaponMeshComponent() const
{
	return currentWeaponMesh;
}

UBaseWeapon* ABaseCharacter::getCurrentWeapon() const
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
		currentWeapon->resetShoot(currentWeaponMesh, this);
	}
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	timelines->Tick(DeltaTime);

	if (HasAuthority() && !isDead)
	{
		TArray<UBaseStatus*> statusesToRemove;
		UBaseWeapon* defaultWeapon = Utility::getPlayerState(this)->getDefaultWeapon();

		if (defaultWeapon)
		{
			defaultWeapon->Tick(DeltaTime);
		}

		for (auto& status : statuses)
		{
			if (!status->Tick(DeltaTime))
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

		timers.processTimers(DeltaTime);

		energyShield->Tick(DeltaTime);
	}
}

void ABaseCharacter::takeDamageFromInflictor(const TScriptInterface<IDamageInflictor>& inflictor)
{
	check(HasAuthority());

	float tem = currentHealth - energyShield->takeDamageFromInflictor(inflictor);

	if (tem < 0.0f)
	{
		this->setCurrentHealth(0.0f);
	}
	else
	{
		this->setCurrentHealth(tem);
	}
}

void ABaseCharacter::impactAction_Implementation(AAmmo* ammo, const FHitResult& hit)
{
	if (isAlly != ammo->getIsAlly())
	{
		takeDamageFromInflictor(ammo->getAilmentInflictorUtility());

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

void ABaseCharacter::addStatus(UBaseStatus* status)
{
	statuses.Add(status);
}

void ABaseCharacter::applySwarmAilment(USwarmAilment* swarm)
{
	this->swarm = swarm;
}

void ABaseCharacter::attachDeathEvent(const TScriptInterface<IOnDeathEvent>& event)
{
	deathEvents.Add(event);
}

void ABaseCharacter::detachDeathEvent(const TScriptInterface<IOnDeathEvent>& event)
{
	deathEvents.Remove(event);
}

void ABaseCharacter::statusInflictorImpactAction(const TScriptInterface<IStatusInflictor>& inflictor, const FHitResult& hit)
{
	TArray<UBaseStatus*> statusesToRemove;

	for (auto& status : statuses)
	{
		UBaseTriggerStatus* trigger = Cast<UBaseTriggerStatus>(status);

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

	if (inflictor->_getUObject()->Implements<UAilmentInflictor>())
	{
		IAilmentInflictor* ailmentInflictor = StaticCast<IAilmentInflictor*>(inflictor.GetInterface());

		if ((hit.PhysMaterial.IsValid() && UPhysicalMaterial::DetermineSurfaceType(hit.PhysMaterial.Get()) == EPhysicalSurface::SurfaceType1) || ailmentInflictor->getCrushingHitProc())
		{
			InitializationUtility::createDefaultAilment(ailmentInflictor->getDamageType(), this)->applyStatus(inflictor, this, hit);
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

const TArray<UBaseStatus*>& ABaseCharacter::getStatuses() const
{
	return statuses;
}

bool ABaseCharacter::getIsAlly() const
{
	return isAlly;
}

bool ABaseCharacter::getIsDead() const
{
	return isDead;
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

float ABaseCharacter::getTotalLifePercentDealt(IDamageInflictor* inflictor) const
{
	float pool = this->getTotalLifePool();

	return Utility::toPercent(1.0f - (pool - inflictor->calculateTotalDamage()) / pool);
}

float ABaseCharacter::getLifePercentDealt(class IDamageInflictor* inflictor) const
{
	return Utility::toPercent(1.0f - (health - inflictor->calculateTotalDamage()) / health);
}

float ABaseCharacter::getEnergyShieldPercentDealt(class IDamageInflictor* inflictor) const
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

const TArray<TScriptInterface<IOnDeathEvent>>& ABaseCharacter::getDeathEvents() const
{
	return deathEvents;
}

void ABaseCharacter::deathTimelineUpdate_Implementation(float value)
{

}

void ABaseCharacter::deathTimelineFinished_Implementation()
{

}
