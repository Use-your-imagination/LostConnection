#include "BaseCharacter.h"

#include <algorithm>

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "NiagaraFunctionLibrary.h"
#include "UObject/ConstructorHelpers.h"

#include "Statuses/BaseTriggerStatus.h"
#include "Statuses/Ailments/SwarmStatus.h"
#include "Utility/InitializationUtility.h"
#include "BaseBot.h"

#include "Utility/MultiplayerUtility.h"

#pragma warning(disable: 4458)

using namespace std;

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	UWorld* world = GetWorld();

	if (world)
	{
		if (HasAuthority())
		{
			timers = NewObject<UTimersUtility>(this);

			timers->setWorld(world);
		}
	}
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!isDead && currentHealth <= 0.0f)
	{
		if (HasAuthority())
		{
			MultiplayerUtility::runOnServerReliableWithMulticast(this, "death");

			isDead = true;
		}
	}

	if (HasAuthority())
	{
		static TArray<UBaseStatus*> statusesToRemove;

		if (defaultWeaponSlot)
		{
			defaultWeaponSlot->Tick(DeltaTime);
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
	}
}

void ABaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseCharacter, health);

	DOREPLIFETIME(ABaseCharacter, currentHealth);

	DOREPLIFETIME(ABaseCharacter, defaultMovementSpeed);

	DOREPLIFETIME(ABaseCharacter, sprintMovementSpeed);

	DOREPLIFETIME(ABaseCharacter, isAlly);

	DOREPLIFETIME(ABaseCharacter, isDead);

	DOREPLIFETIME(ABaseCharacter, spareAmmo);

	DOREPLIFETIME(ABaseCharacter, currentWeapon);

	DOREPLIFETIME(ABaseCharacter, defaultWeaponSlot);

	DOREPLIFETIME(ABaseCharacter, statuses);
}

bool ABaseCharacter::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool wroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	wroteSomething |= Channel->ReplicateSubobject(currentWeapon, *Bunch, *RepFlags);

	wroteSomething |= Channel->ReplicateSubobject(defaultWeaponSlot, *Bunch, *RepFlags);

	return wroteSomething;
}

void ABaseCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	deathMaskRenderTexture = NewObject<UTextureRenderTarget2D>(this);

	deathMaskRenderTexture->InitCustomFormat(256, 256, EPixelFormat::PF_G16, false);
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

	int currentMagazineSize = currentWeapon->getCurrentMagazineSize();
	int magazineSize = currentWeapon->getMagazineSize();

	if (currentMagazineSize == magazineSize)
	{
		return;
	}

	int32& ammoCount = spareAmmo[static_cast<size_t>(currentWeapon->getAmmoType())];

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
		UWorld* world = GetWorld();

		if (world)
		{
			currentWeapon->resetShoot(world, currentWeaponMesh, this);
		}
	}
}

ABaseCharacter::ABaseCharacter() :
	timers(nullptr),
	defaultMovementSpeed(450.0f),
	sprintMovementSpeed(575.0f),
	isDead(false)
{
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> underStatusFinder(TEXT("NiagaraSystem'/Game/Assets/FX/Statuses/Common/NPS_SatusState.NPS_SatusState'"));

	USkeletalMeshComponent* mesh = GetMesh();
	UCharacterMovementComponent* movement = GetCharacterMovement();

	PrimaryActorTick.bCanEverTick = true;
	NetUpdateFrequency = 60;

	spareAmmo.Init(0, 4);

	spareAmmo[static_cast<size_t>(ammoTypes::defaultType)] = 9999;

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
	currentWeapon = defaultWeaponSlot;

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

void ABaseCharacter::takeDamage(float damage)
{
	float tem = this->getCurrentHealth();

	tem -= damage;

	if (tem < 0.0f)
	{
		this->setCurrentHealth(0.0f);
	}
	else
	{
		this->setCurrentHealth(tem);
	}
}

void ABaseCharacter::setHealth_Implementation(float newHealth)
{
	health = newHealth;
}

void ABaseCharacter::setCurrentHealth_Implementation(float newCurrentHealth)
{
	if (swarm.IsValid())
	{
		float newPercentHealth = newCurrentHealth / health * 100.0f;

		if (newPercentHealth <= swarm->getThreshold())
		{
			FHitResult hit;

			hit.Location = GetActorLocation();

			swarm->applyEffect(this, hit);

			currentHealth = 0.0f;

			return;
		}
	}

	currentHealth = newCurrentHealth;
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
	return defaultWeaponSlot;
}

float ABaseCharacter::getHealth() const
{
	return health;
}

float ABaseCharacter::getCurrentHealth() const
{
	return currentHealth;
}

float ABaseCharacter::getDefaultMovementSpeed() const
{
	return defaultMovementSpeed;
}

float ABaseCharacter::getSprintMovementSpeed() const
{
	return sprintMovementSpeed;
}

bool ABaseCharacter::getIsAlly() const
{
	return isAlly;
}

bool ABaseCharacter::getIsDead() const
{
	return isDead;
}

int32 ABaseCharacter::getSpareAmmo(ammoTypes type) const
{
	return spareAmmo[static_cast<size_t>(type)];
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

int ABaseCharacter::getWeaponCount() const
{
	int result = 0;

	result += static_cast<bool>(defaultWeaponSlot);

	return result;
}

float ABaseCharacter::getFlatDamageReduction_Implementation() const
{
	return 200.0f;
}

float ABaseCharacter::getPercentageDamageReduction_Implementation() const
{
	return 25.0f;
}

void ABaseCharacter::impactAction_Implementation(ABaseAmmo* ammo, const FHitResult& hit)
{
	if (isAlly != ammo->getIsAlly())
	{
		this->takeDamage(ammo->getDamage());

		this->inflictorImpactAction(ammo, hit);
	}
}

void ABaseCharacter::spawnApplyStatus_Implementation(UNiagaraSystem* applyStatusVFX, const FHitResult& hit)
{
	UNiagaraFunctionLibrary::SpawnSystemAttached
	(
		applyStatusVFX,
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

void ABaseCharacter::spawnApplyEffect_Implementation(UNiagaraSystem* applyEffectVFX, const FHitResult& hit)
{
	UNiagaraFunctionLibrary::SpawnSystemAttached
	(
		applyEffectVFX,
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

void ABaseCharacter::applySwarmStatus(USwarmStatus* swarm)
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

float ABaseCharacter::getTotalLifePercentDealt(float damage) const
{
	// TODO: add shields
	float pool = health;

	return (1.0f - (pool - damage) / pool) * 100.0f;
}

float ABaseCharacter::getHealthPercentDealt(float damage) const
{
	return (1.0f - (health - damage) / health) * 100.0f;
}

void ABaseCharacter::inflictorImpactAction(const TScriptInterface<IStatusInflictor>& inflictor, const FHitResult& hit)
{
	static TArray<UBaseStatus*> statusesToRemove;

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

	if ((hit.PhysMaterial.IsValid() && UPhysicalMaterial::DetermineSurfaceType(hit.PhysMaterial.Get()) == EPhysicalSurface::SurfaceType1) || inflictor->getCrushingHitProc())
	{
		InitializationUtility::createDefaultStatus(inflictor->getDamageType(), this)->applyStatus(inflictor, this, hit);
	}

	statusesToRemove.Empty();
}

USkeletalMeshComponent* ABaseCharacter::getMeshComponent()
{
	return GetMesh();
}

UCapsuleComponent* ABaseCharacter::getCapsuleComponent()
{
	return GetCapsuleComponent();
}
