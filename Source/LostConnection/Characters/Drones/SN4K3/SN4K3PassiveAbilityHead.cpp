// Copyright (c) 2021 Use-your-imagination

#include "SN4K3PassiveAbilityHead.h"

#include "Kismet/KismetSystemLibrary.h"
#include "NiagaraFunctionLibrary.h"

#include "Constants/Constants.h"
#include "Characters/BaseCharacter.h"
#include "Utility/InitializationUtility.h"
#include "Ammo/BaseAmmo.h"
#include "Utility/MultiplayerUtility.h"
#include "SN4K3ResurrectDeathEvent.h"
#include "WorldPlaceables/DeathPlaceholder.h"
#include "AssetLoading/LostConnectionAssetManager.h"

void ASN4K3PassiveAbilityHead::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	FInputActionBinding pressExplosion("Shoot", IE_Pressed);
	FInputActionBinding pressSprint("Zoom", IE_Pressed);

	pressExplosion.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() 
		{
			if (!this->checkExplode())
			{
				return;
			}

			MultiplayerUtility::runOnServerReliable(this, "explode");
		});

	pressSprint.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() 
		{
			if (!this->checkSpeedup())
			{
				return;
			}

			MultiplayerUtility::runOnServerReliable(this, "speedup");
		});

	PlayerInputComponent->AddActionBinding(pressExplosion);
	PlayerInputComponent->AddActionBinding(pressSprint);
}

void ASN4K3PassiveAbilityHead::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASN4K3PassiveAbilityHead, naniteExplosionDamage);

	DOREPLIFETIME(ASN4K3PassiveAbilityHead, explosionRadius);

	DOREPLIFETIME(ASN4K3PassiveAbilityHead, addedDamage);

	DOREPLIFETIME(ASN4K3PassiveAbilityHead, additionalDamage);

	DOREPLIFETIME(ASN4K3PassiveAbilityHead, increasedDamageCoefficients);

	DOREPLIFETIME(ASN4K3PassiveAbilityHead, moreDamageCoefficients);
}

void ASN4K3PassiveAbilityHead::explode()
{
	static TArray<TEnumAsByte<EObjectTypeQuery>> traceObjectTypes = { UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn) };
	TArray<AActor*> tem;

	this->explodeVFX();

	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), mesh->GetComponentLocation(), explosionRadius, traceObjectTypes, ABaseCharacter::StaticClass(), {}, tem);

	for (auto& i : tem)
	{
		ABaseCharacter* character = Cast<ABaseCharacter>(i);

		if (!character->getIsAlly())
		{
			FHitResult characterHit;

			characterHit.Actor = character;
			characterHit.Component = character->GetMesh();
			characterHit.Location = character->GetActorLocation();

			// TODO: Expire event

			USN4K3ResurrectDeathEvent* resurrect = NewObject<USN4K3ResurrectDeathEvent>(character);

			resurrect->initDeathEvent(character);

			resurrect->initHead(this);

			character->takeDamage(this);

			character->statusInflictorImpactAction(this, characterHit);
		}
	}

	isExploded = true;
}

void ASN4K3PassiveAbilityHead::explodeVFX()
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation
	(
		GetWorld(),
		explosionParticles,
		mesh->GetComponentLocation(),
		FRotator::ZeroRotator,
		FVector::OneVector,
		true,
		true,
		ENCPoolMethod::AutoRelease
	);
}

void ASN4K3PassiveAbilityHead::destroyHead()
{
	Utility::getPlayerState(this)->getCurrentUI()->RemoveFromViewport();

	ADeathPlaceholder* placeholder = Utility::getGameState(this)->spawn<ADeathPlaceholder>(ULostConnectionAssetManager::get().getDefaults().getDeathPlaceholder(), {});

	GetController()->Possess(placeholder);

	placeholder->FinishSpawning({ FRotator::ZeroRotator, GetActorLocation() });

	Destroy();
}

ASN4K3PassiveAbilityHead::ASN4K3PassiveAbilityHead() :
	isExploded(false)
{
	PrimaryActorTick.bCanEverTick = true;

	NetUpdateFrequency = UConstants::actorNetUpdateFrequency;

	sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));

	SetRootComponent(sphere);

	mesh->SetupAttachment(sphere);

	mesh->SetGenerateOverlapEvents(true);

	mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Ignore);

	mesh->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);

	mesh->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);

	movement->SetUpdatedComponent(sphere);

	movement->SetIsReplicated(true);
}

void ASN4K3PassiveAbilityHead::speedup_Implementation()
{

}

bool ASN4K3PassiveAbilityHead::checkExplode_Implementation()
{
	return true;
}

bool ASN4K3PassiveAbilityHead::checkSpeedup_Implementation()
{
	return true;
}

UPawnMovementComponent* ASN4K3PassiveAbilityHead::GetMovementComponent() const
{
	return movement;
}

void ASN4K3PassiveAbilityHead::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		if (isExploded)
		{
			this->destroyHead();

			return;
		}
	}
}

typeOfDamage ASN4K3PassiveAbilityHead::getDamageType() const
{
	return typeOfDamage::nanite;
}

float ASN4K3PassiveAbilityHead::getCrushingHitChance() const
{
	return 100.0f;
}

float ASN4K3PassiveAbilityHead::getAdditionalCrushingHitChance() const
{
	return 0.0f;
}

void ASN4K3PassiveAbilityHead::appendIncreasedDamageCoefficient(float coefficient)
{
	increasedDamageCoefficients.Add(coefficient);
}

void ASN4K3PassiveAbilityHead::removeIncreasedDamageCoefficient(float coefficient)
{
	increasedDamageCoefficients.Remove(coefficient);
}

void ASN4K3PassiveAbilityHead::appendMoreDamageCoefficient(float coefficient)
{
	moreDamageCoefficients.Add(coefficient);
}

void ASN4K3PassiveAbilityHead::removeMoreDamageCoefficient(float coefficient)
{
	moreDamageCoefficients.Remove(coefficient);
}

void ASN4K3PassiveAbilityHead::setBaseDamage(float damage)
{
	naniteExplosionDamage = damage;
}

void ASN4K3PassiveAbilityHead::setAddedDamage(float addedDamage)
{
	this->addedDamage = addedDamage;
}

void ASN4K3PassiveAbilityHead::setAdditionalDamage(float additionalDamage)
{
	this->additionalDamage = additionalDamage;
}

float ASN4K3PassiveAbilityHead::getBaseDamage() const
{
	return naniteExplosionDamage;
}

float ASN4K3PassiveAbilityHead::getAddedDamage() const
{
	return addedDamage;
}

float ASN4K3PassiveAbilityHead::getAdditionalDamage() const
{
	return additionalDamage;
}

TArray<float> ASN4K3PassiveAbilityHead::getIncreasedDamageCoefficients() const
{
	return increasedDamageCoefficients;
}

TArray<float> ASN4K3PassiveAbilityHead::getMoreDamageCoefficients() const
{
	return moreDamageCoefficients;
}
