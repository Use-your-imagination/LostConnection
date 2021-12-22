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
#include "Interfaces/Gameplay/Descriptions/Base/DamageInflictor.h"
#include "Constants/Constants.h"
#include "Utility/Utility.h"

#include "Utility/MultiplayerUtility.h"

#pragma warning(disable: 4458)

FAmmoData::FAmmoData(ammoTypes ammoType, int32 ammoCount) :
	ammoType(ammoType),
	ammoCount(ammoCount)
{

}

void ABaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseCharacter, health);

	DOREPLIFETIME(ABaseCharacter, currentHealth);

	DOREPLIFETIME(ABaseCharacter, reservedHealth);

	DOREPLIFETIME(ABaseCharacter, defaultMovementSpeed);

	DOREPLIFETIME(ABaseCharacter, sprintMovementSpeed);

	DOREPLIFETIME(ABaseCharacter, isAlly);

	DOREPLIFETIME(ABaseCharacter, isDead);

	DOREPLIFETIME(ABaseCharacter, currentWeapon);

	DOREPLIFETIME(ABaseCharacter, statuses);

	DOREPLIFETIME(ABaseCharacter, maxSmallAmmoCount);

	DOREPLIFETIME(ABaseCharacter, maxLargeAmmoCount);

	DOREPLIFETIME(ABaseCharacter, maxEnergyAmmoCount);
}

bool ABaseCharacter::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool wroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	wroteSomething |= Channel->ReplicateSubobject(currentWeapon, *Bunch, *RepFlags);

	return wroteSomething;
}

void ABaseCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	deathMaskRenderTexture = NewObject<UTextureRenderTarget2D>(this);

	deathMaskRenderTexture->InitCustomFormat(256, 256, EPixelFormat::PF_G16, false);
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		TArray<FAmmoData>& spareAmmo = Utility::getPlayerState(this)->getSpareAmmoArray();

		if (!spareAmmo.Num())
		{
			spareAmmo =
			{
				FAmmoData(ammoTypes::small, defaultSmallAmmoCount),
				FAmmoData(ammoTypes::large, defaultLargeAmmoCount),
				FAmmoData(ammoTypes::energy, defaultEnergyAmmoCount),
				FAmmoData(ammoTypes::defaultType, 9999)
			};
		}
	}
}

void ABaseCharacter::deathMaterialTimerUpdate_Implementation()
{

}

void ABaseCharacter::shootTimerUpdate_Implementation()
{

}

void ABaseCharacter::onCurrentWeaponChange()
{
	this->updateWeaponMesh();
}

void ABaseCharacter::onCurrentHealthChanged()
{

}

void ABaseCharacter::updateWeaponMesh()
{
	if (currentWeapon)
	{
		currentWeaponMesh->SetSkeletalMesh(currentWeapon->getWeaponMesh());

		currentWeaponMesh->SetAnimClass(currentWeapon->getAnimationBlueprint());

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

#pragma region Reload
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
	ammoTypes ammoType = currentWeapon->getAmmoType();

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

void ABaseCharacter::runReloadLogic_Implementation()
{
	this->reloadLogic();

	IReload::Execute_reloadEventLogic(this);
}
#pragma endregion

#pragma region Shoot
void ABaseCharacter::shootVisual()
{

}

void ABaseCharacter::shootLogic()
{
	if (this->isWeaponEquipped())
	{
		currentWeapon->startShoot();
	}
}

void ABaseCharacter::runShootLogic_Implementation()
{
	this->shootLogic();

	IShoot::Execute_shootEventLogic(this);
}
#pragma endregion

#pragma region Death
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

	this->returnAmmoToSpare(playerState->getPrimaryWeapon());

	this->returnAmmoToSpare(playerState->getSecondaryWeapon());
}

void ABaseCharacter::runDeathLogic_Implementation()
{
	this->deathLogic();

	IDeath::Execute_deathEventLogic(this);
}
#pragma endregion

void ABaseCharacter::resetShootLogic()
{
	if (currentWeapon)
	{
		currentWeapon->resetShoot(currentWeaponMesh, this);
	}
}

ABaseCharacter::ABaseCharacter() :
	defaultMovementSpeed(450.0f),
	sprintMovementSpeed(575.0f),
	isDead(false),
	maxSmallAmmoCount(UConstants::defaultSmallAmmoMaxCount),
	maxLargeAmmoCount(UConstants::defaultLargeAmmoMaxCount),
	maxEnergyAmmoCount(UConstants::defaultEnergyAmmoMaxCount),
	defaultSmallAmmoCount(maxSmallAmmoCount* UConstants::conversionAmmoCoefficient),
	defaultLargeAmmoCount(maxLargeAmmoCount* UConstants::conversionAmmoCoefficient),
	defaultEnergyAmmoCount(maxEnergyAmmoCount* UConstants::conversionAmmoCoefficient)
{
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> underStatusFinder(TEXT("NiagaraSystem'/Game/Assets/FX/Statuses/Common/NPS_SatusState.NPS_SatusState'"));

	PrimaryActorTick.bCanEverTick = true;

	NetUpdateFrequency = UConstants::actorNetUpdateFrequency;

	USkeletalMeshComponent* mesh = GetMesh();
	UCharacterMovementComponent* movement = GetCharacterMovement();

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	mesh->SetGenerateOverlapEvents(true);
	mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);
	mesh->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);

	movement->bOrientRotationToMovement = true;
	movement->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	movement->JumpZVelocity = 600.f;
	movement->AirControl = 1.0f;
	movement->GetNavAgentPropertiesRef().bCanCrouch = true;
	movement->MaxWalkSpeed = defaultMovementSpeed;
	movement->MaxWalkSpeedCrouched = defaultMovementSpeed / 3;
	movement->bCanWalkOffLedgesWhenCrouching = true;

	currentWeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CurrentWeaponMesh"));
	currentWeaponMesh->SetupAttachment(mesh, "Hand_WeaponSocket_R");
	currentWeaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	magazine = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Magazine"));
	magazine->SetupAttachment(currentWeaponMesh);
	magazine->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	underStatusComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("UnderStatus"));
	underStatusComponent->SetupAttachment(mesh);
	underStatusComponent->AddLocalOffset(FVector(0.0f, 0.0f, this->getCapsuleComponent()->GetUnscaledCapsuleHalfHeight()));
	underStatusComponent->SetAsset(underStatusFinder.Object);

#pragma region BlueprintFunctionLibrary
	isReloading = false;

	jumpHold = false;

	sprintHold = false;

	crouchHold = false;

	primaryHold = false;

	characterMaterial = nullptr;
#pragma endregion
}

void ABaseCharacter::shoot()
{
	this->shootVisual();

	IShoot::Execute_shootEventVisual(this);
}

void ABaseCharacter::resetShoot()
{
	MultiplayerUtility::runOnServerReliable(this, "resetShootLogic");
}

void ABaseCharacter::changeToDefaultWeapon_Implementation()
{
	currentWeapon = Utility::getPlayerState(this)->getDefaultWeapon();

	this->updateWeaponMesh();
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

void ABaseCharacter::returnAmmoToSpare(UBaseWeapon* weapon)
{
	if (!weapon || !GetController())
	{
		return;
	}

	ammoTypes ammoType = weapon->getAmmoType();

	if (ammoType == ammoTypes::defaultType)
	{
		return;
	}

	TArray<FAmmoData>& spareAmmo = Utility::getPlayerState(this)->getSpareAmmoArray();
	int32& currentWeaponSpareAmmo = Algo::FindByPredicate(spareAmmo, [&ammoType](FAmmoData& data) { return data.ammoType == ammoType; })->ammoCount;
	int32 maxCount = 0;

	switch (ammoType)
	{
	case ammoTypes::small:
		maxCount = maxSmallAmmoCount;

		break;

	case ammoTypes::large:
		maxCount = maxLargeAmmoCount;

		break;

	case ammoTypes::energy:
		maxCount = maxEnergyAmmoCount;

		break;
	}

	int32 tem = FMath::Min(maxCount, currentWeaponSpareAmmo + weapon->getCurrentMagazineSize());

	if (tem == maxCount)
	{
		weapon->setCurrentMagazineSize(currentWeaponSpareAmmo + weapon->getCurrentMagazineSize() - maxCount);
	}
	else
	{
		weapon->setCurrentMagazineSize(0);
	}

	currentWeaponSpareAmmo = tem;
}

void ABaseCharacter::setDefaultWeapon_Implementation(TSubclassOf<UBaseWeapon> defaultWeapon)
{
	if (!defaultWeapon)
	{
		UE_LOG(LogTemp, Warning, L"Default weapon is null");

		return;
	}

	ALostConnectionPlayerState* playerState = Utility::getPlayerState(this);
	UBaseWeapon* weapon = NewObject<UBaseWeapon>(playerState, defaultWeapon);

	weapon->setOwner(this);

	weapon->updateTimeBetweenShots();

	playerState->setDefaultWeapon(weapon);
}

void ABaseCharacter::setHealth_Implementation(float newHealth)
{
	health = newHealth;
}

void ABaseCharacter::setCurrentHealth_Implementation(float newCurrentHealth)
{
	if (swarm.IsValid())
	{
		float newPercentHealth = Utility::toPercent(newCurrentHealth / health);

		if (newPercentHealth <= swarm->getThreshold())
		{
			FHitResult hit;

			hit.Actor = this;
			hit.Component = GetMesh();
			hit.Location = GetActorLocation();

			swarm->applyEffect(this, hit);

			currentHealth = 0.0f;

			return;
		}
	}

	currentHealth = newCurrentHealth;

	this->onCurrentHealthChanged();
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

float ABaseCharacter::getCurrentHealth() const
{
	return currentHealth;
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

bool ABaseCharacter::getIsReloading() const
{
	return isReloading;
}

USkeletalMeshComponent* ABaseCharacter::getCurrentWeaponMeshComponent() const
{
	return currentWeaponMesh;
}

UBaseWeapon* ABaseCharacter::getCurrentWeapon()
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

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!isDead && currentHealth == 0.0f)
	{
		if (HasAuthority())
		{
			Algo::ForEachIf
			(
				deathEvents,
				[](const TWeakInterfacePtr<IOnDeathEvent>& event) { return event.IsValid(); },
				[](const TWeakInterfacePtr<IOnDeathEvent>& event) { event->deathEventAction(); }
			);

			MultiplayerUtility::runOnServerReliableWithMulticast(this, "death");

			isDead = true;
		}
	}

	if (HasAuthority() && GetController())
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
	}
}

void ABaseCharacter::takeDamage(const TScriptInterface<IDamageInflictor>& inflictor)
{
	float tem = currentHealth - inflictor->calculateTotalDamage();

	if (tem < 0.0f)
	{
		this->setCurrentHealth(0.0f);
	}
	else
	{
		this->setCurrentHealth(tem);
	}
}

void ABaseCharacter::impactAction_Implementation(ABaseAmmo* ammo, const FHitResult& hit)
{
	if (isAlly != ammo->getIsAlly())
	{
		this->takeDamage(ammo);

		this->statusInflictorImpactAction(ammo, hit);
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

void ABaseCharacter::setUnderStatusIntVariable_Implementation(const FString& key, int32 value)
{
	underStatusComponent->SetNiagaraVariableInt(key, value);
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

float ABaseCharacter::getTotalLifePercentDealt(IDamageInflictor* inflictor) const
{
	// TODO: Add shields
	float pool = health;

	return Utility::toPercent(1.0f - (pool - inflictor->calculateTotalDamage()) / pool);
}

float ABaseCharacter::getHealthPercentDealt(IDamageInflictor* inflictor) const
{
	return Utility::toPercent(1.0f - (health - inflictor->calculateTotalDamage()) / health);
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

USkeletalMeshComponent* ABaseCharacter::getMeshComponent()
{
	return GetMesh();
}

UCapsuleComponent* ABaseCharacter::getCapsuleComponent()
{
	return GetCapsuleComponent();
}

void ABaseCharacter::attachDeathEvent(IOnDeathEvent* event)
{
	deathEvents.Add(event);
}

void ABaseCharacter::detachDeathEvent(IOnDeathEvent* event)
{
	deathEvents.Remove(event);
}

const TArray<TWeakInterfacePtr<IOnDeathEvent>>& ABaseCharacter::getDeathEvents() const
{
	return deathEvents;
}
