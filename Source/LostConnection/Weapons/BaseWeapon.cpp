// Copyright (c) 2021 Use Your Imagination

#include "BaseWeapon.h"

#include "UObject/ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Utility/MultiplayerUtility.h"
#include "Engine/LostConnectionPlayerState.h"
#include "Engine/LostConnectionGameState.h"
#include "Characters/BaseDrone.h"
#include "Characters/AI/BaseBot.h"
#include "Constants/Constants.h"

#pragma warning(disable: 4458)

FTransform UBaseWeapon::calculateAmmoTransform(TObjectPtr<ABaseDrone> drone, const FTransform& weaponBarrelTransform)
{
	if (IsValid(drone))
	{
		TObjectPtr<UCameraComponent> camera = drone->GetFollowCamera();

		return FTransform
		(
			camera->GetForwardVector().ToOrientationRotator(),
			camera->GetComponentLocation() + camera->GetForwardVector() * (drone->GetCameraOffset()->TargetArmLength + length)
		);
	}
	else
	{
		// TODO: change target to AITargeted

		TObjectPtr<ABaseBot> bot = Cast<ABaseBot>(owner);
		TObjectPtr<AAIController> controller = bot->GetController<AAIController>();
		TObjectPtr<ABaseDrone> target = Cast<ABaseDrone>(controller->GetBlackboardComponent()->GetValueAsObject(ULostConnectionAssetManager::get().getAI().getTargetKey()));

		if (IsValid(target))
		{
			return FTransform
			(
				(target->GetActorLocation() - bot->GetActorLocation()).ToOrientationRotator(),
				weaponBarrelTransform.GetLocation()
			);
		}
	}

	return {};
}

FTransform UBaseWeapon::calculateVisibleAmmoTransform(TObjectPtr<ABaseDrone> drone, const FTransform& weaponBarrelTransform, const FTransform& ammoTransform)
{
	if (!IsValid(drone))
	{
		return {};
	}

	return weaponBarrelTransform.GetRelativeTransform(ammoTransform);
}

void UBaseWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UBaseWeapon, ammoType);

	DOREPLIFETIME(UBaseWeapon, damageType);

	DOREPLIFETIME(UBaseWeapon, damage);

	DOREPLIFETIME(UBaseWeapon, addedDamage);

	DOREPLIFETIME(UBaseWeapon, additionalDamage);

	DOREPLIFETIME(UBaseWeapon, increaseDamageCoefficients);

	DOREPLIFETIME(UBaseWeapon, moreDamageCoefficients);

	DOREPLIFETIME(UBaseWeapon, currentMagazineSize);

	DOREPLIFETIME(UBaseWeapon, magazineSize);

	DOREPLIFETIME(UBaseWeapon, ammoCost);

	DOREPLIFETIME(UBaseWeapon, roundsPerSecond);

	DOREPLIFETIME(UBaseWeapon, weaponType);

	DOREPLIFETIME(UBaseWeapon, spreadDistance);

	DOREPLIFETIME(UBaseWeapon, crushingHitChance);

	DOREPLIFETIME(UBaseWeapon, additionalCrushingHitChance);

	DOREPLIFETIME(UBaseWeapon, length);

	DOREPLIFETIME(UBaseWeapon, currentAccuracyMultiplier);

	DOREPLIFETIME(UBaseWeapon, weaponModules);

	DOREPLIFETIME(UBaseWeapon, rarity);
}

void UBaseWeapon::shoot()
{
	if (!owner.IsValid() || owner->getIsReloading())
	{
		return;
	}

	if (weaponType == EWeaponType::semiAutomatic || weaponType == EWeaponType::single)
	{
		MultiplayerUtility::runOnServerReliable(owner.Get(), "resetShoot");
	}
	else if (weaponType == EWeaponType::delay)
	{
		return;
	}

	TObjectPtr<ABaseDrone> drone = Cast<ABaseDrone>(owner);
	int32 shotsCount = currentTimeBetweenShots ? FMath::FloorToInt(FMath::Abs(currentTimeBetweenShots / timeBetweenShots)) : 1;
	int32 boneIndex = owner->getCurrentWeaponMeshComponent()->GetBoneIndex("barrel");
	FTransform weaponBarrelTransform = owner->getCurrentWeaponMeshComponent()->GetBoneTransform(boneIndex);
	FTransform ammoTransform = this->calculateAmmoTransform(drone, weaponBarrelTransform);
	FTransform visibleAmmoTransform = this->calculateVisibleAmmoTransform(drone, weaponBarrelTransform, ammoTransform);
	TObjectPtr<ALostConnectionGameState> gameState = Utility::getGameState(owner.Get());
	bool isAnyShot = false;

	for (int32 i = 0; i < shotsCount; i++)
	{
		if (currentMagazineSize >= ammoCost)
		{
			owner->notifyShotEvents(owner);

			float currentSpreadDistance = this->calculateSpreadDistance();
			float pitch = FMath::RandRange(-currentSpreadDistance, currentSpreadDistance);
			float yaw = FMath::Tan(FMath::Acos(pitch / currentSpreadDistance)) * pitch;
			TObjectPtr<AAmmo> launchedAmmo = gameState->spawn<AAmmo>(ammoClass, ammoTransform);
			
			launchedAmmo->copyProperties(this);

			launchedAmmo->launch(owner, visibleAmmoTransform, { pitch, FMath::RandRange(-yaw, yaw), 0.0f });

			currentMagazineSize -= ammoCost;

			currentAccuracyMultiplier += drawback;

			isAnyShot = true;
		}
		else if (owner->getSpareAmmo(ammoType) != 0)
		{
			MultiplayerUtility::runOnServerReliableWithMulticast(owner.Get(), "reload");

			return;
		}
	}

	if (isAnyShot)
	{
		currentTimeBetweenShots += timeBetweenShots;
	}

	if (shotsCount && isAnyShot)
	{
		TObjectPtr<UAnimMontage> shootAnimation = nullptr;

		if (IsValid(drone))
		{
			shootAnimation = drone->getZooming() ?
				adsShootAnimation :
				hipShootAnimation;
		}
		else
		{
			shootAnimation = hipShootAnimation;
		}

		owner->playAnimation(shootAnimation);

		IShoot::Execute_onShoot(owner.Get());
	}
}

const FText& UBaseWeapon::getItemDescription() const
{
	return weaponDescription;
}

UBaseWeapon::UBaseWeapon() :
	currentMagazineSize(0),
	ammoCost(1),
	length(100.0f)
{
	
}

void UBaseWeapon::startShoot()
{
	isShooting = true;
}

void UBaseWeapon::resetShoot(TObjectPtr<USkeletalMeshComponent> currentVisibleWeaponMesh)
{
	isShooting = false;

	if (weaponType == EWeaponType::delay)
	{
		weaponType = EWeaponType::single;

		this->shoot();

		weaponType = EWeaponType::delay;
	}
}

void UBaseWeapon::alternativeMode()
{

}

void UBaseWeapon::updateTimeBetweenShots_Implementation()
{
	timeBetweenShots = 1.0f / StaticCast<float>(roundsPerSecond);
}

void UBaseWeapon::Tick(float DeltaSeconds)
{
	static constexpr float decreaseAccuracyMultiplier = 0.95f;
	bool isReloading = owner.IsValid() && owner->getIsReloading();

	if (isReloading)
	{
		currentTimeBetweenShots = 0.0f;
	}
	else if (isShooting && currentTimeBetweenShots)
	{
		currentTimeBetweenShots -= DeltaSeconds;
	}
	else if (currentTimeBetweenShots)
	{
		currentTimeBetweenShots = FMath::Max(0.0f, currentTimeBetweenShots - DeltaSeconds);
	}

	currentAccuracyMultiplier = FMath::Max(1.0f, currentAccuracyMultiplier * decreaseAccuracyMultiplier);

	if (!isReloading && isShooting && currentTimeBetweenShots <= 0.0f)
	{
		this->shoot();
	}
}

void UBaseWeapon::appendIncreaseDamageCoefficient(float coefficient)
{
	increaseDamageCoefficients.Add(coefficient);
}

void UBaseWeapon::removeIncreaseDamageCoefficient(float coefficient)
{
	increaseDamageCoefficients.Remove(coefficient);
}

void UBaseWeapon::appendMoreDamageCoefficient(float coefficient)
{
	moreDamageCoefficients.Add(coefficient);
}

void UBaseWeapon::removeMoreDamageCoefficient(float coefficient)
{
	moreDamageCoefficients.Remove(coefficient);
}

void UBaseWeapon::setOwner_Implementation(ABaseCharacter* owner)
{
	this->owner = owner;
}

void UBaseWeapon::setAmmoType_Implementation(EAmmoType newAmmoType)
{
	ammoType = newAmmoType;
}

void UBaseWeapon::setBaseDamage_Implementation(float newDamage)
{
	damage = newDamage;
}

void UBaseWeapon::setAddedDamage_Implementation(float newAddedDamage)
{
	addedDamage = newAddedDamage;
}

void UBaseWeapon::setAdditionalDamage_Implementation(float newAdditionalDamage)
{
	additionalDamage = newAdditionalDamage;
}

void UBaseWeapon::setCurrentMagazineSize_Implementation(int32 newCurrentMagazineSize)
{
	currentMagazineSize = newCurrentMagazineSize;
}

void UBaseWeapon::setRateOfFire_Implementation(int32 newRoundsPerSecond)
{
	roundsPerSecond = newRoundsPerSecond;
}

void UBaseWeapon::setWeaponType_Implementation(EWeaponType newWeaponType)
{
	weaponType = newWeaponType;
}

void UBaseWeapon::setRarity_Implementation(EWeaponRarity newRarity)
{
	rarity = newRarity;

	int32 newSize = UConstants::getWeaponModulesSize(rarity);
	TObjectPtr<AInventory> inventory = Cast<AInventory>(GetOuter());

	if (newSize > weaponModules.Num())
	{
		while (newSize != weaponModules.Num())
		{
			weaponModules.Add(NewObject<UInventoryCell>(inventory));
		}
	}
	else
	{
		weaponModules.SetNum(newSize);
	}
}

TObjectPtr<USkeletalMesh> UBaseWeapon::getWeaponMesh() const
{
	return mesh;
}

TObjectPtr<UStaticMesh> UBaseWeapon::getMagazineMesh() const
{
	return magazineMesh;
}

EAmmoType UBaseWeapon::getAmmoType() const
{
	return ammoType;
}

ETypeOfDamage UBaseWeapon::getDamageType() const
{
	return damageType;
}

float UBaseWeapon::getBaseDamage() const
{
	return damage;
}

float UBaseWeapon::getAddedDamage() const
{
	return addedDamage;
}

float UBaseWeapon::getAdditionalDamage() const
{
	return additionalDamage;
}

int32 UBaseWeapon::getCurrentMagazineSize() const
{
	return currentMagazineSize;
}

int32 UBaseWeapon::getMagazineSize() const
{
	return magazineSize;
}

int32 UBaseWeapon::getRoundsPerSecond() const
{
	return roundsPerSecond;
}

EWeaponType UBaseWeapon::getWeaponType() const
{
	return weaponType;
}

const TWeakObjectPtr<ABaseCharacter>& UBaseWeapon::getOwner() const
{
	return owner;
}

float UBaseWeapon::getBaseCrushingHitChance() const
{
	return crushingHitChance;
}

float UBaseWeapon::getAdditionalCrushingHitChance() const
{
	return additionalCrushingHitChance;
}

float UBaseWeapon::getLength() const
{
	return length;
}

const TArray<TObjectPtr<UInventoryCell>>& UBaseWeapon::getWeaponModules() const
{
	return weaponModules;
}

TArray<TObjectPtr<UInventoryCell>>& UBaseWeapon::getWeaponModules()
{
	return weaponModules;
}

bool UBaseWeapon::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool wroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	for (TObjectPtr<UInventoryCell> weaponModule : weaponModules)
	{
		if (IsValid(weaponModule))
		{
			wroteSomething = Channel->ReplicateSubobject(weaponModule, *Bunch, *RepFlags);

			wroteSomething = weaponModule->ReplicateSubobjects(Channel, Bunch, RepFlags);
		}
	}

	return wroteSomething;
}

const FText& UBaseWeapon::getItemName() const
{
	return weaponName;
}

const UTexture2D* UBaseWeapon::getCellIcon() const
{
	return weaponCellIcon;
}

const FLinearColor& UBaseWeapon::getBorderColor() const
{
	return ULostConnectionAssetManager::get().getDefaults()[rarity];
}
