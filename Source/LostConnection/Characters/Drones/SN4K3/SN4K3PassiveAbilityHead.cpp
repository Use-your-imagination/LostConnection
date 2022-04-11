// Copyright (c) 2021 Use-your-imagination

#include "SN4K3PassiveAbilityHead.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/CapsuleComponent.h"

#include "Constants/Constants.h"
#include "Characters/BaseCharacter.h"
#include "Utility/InitializationUtility.h"
#include "Projectiles/Ammo.h"
#include "Utility/MultiplayerUtility.h"
#include "SN4K3ResurrectDeathEvent.h"
#include "WorldPlaceables/DeathPlaceholder.h"
#include "AssetLoading/LostConnectionAssetManager.h"
#include "Statuses/Ailments/SwarmAilment.h"

void ASN4K3PassiveAbilityHead::BeginPlay()
{
	Super::BeginPlay();

	Utility::executeOnOwningClient(this, [this]()
		{
			const USN4K3DataAsset* data = Utility::findDroneAsset<USN4K3DataAsset>(ULostConnectionAssetManager::get().getDrones());

			Utility::setCurrentUI(data->getHeadUI(), this);
		});
}

void ASN4K3PassiveAbilityHead::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
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

	DOREPLIFETIME(ASN4K3PassiveAbilityHead, explosionRadius);

	DOREPLIFETIME(ASN4K3PassiveAbilityHead, ailmentInflictorUtility);
}

bool ASN4K3PassiveAbilityHead::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool wroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	// wroteSomething |= Channel->ReplicateSubobject(ailmentInflictorUtility, *Bunch, *RepFlags);
	// 
	// wroteSomething |= ailmentInflictorUtility->ReplicateSubobjects(Channel, Bunch, RepFlags);

	return wroteSomething;
}

void ASN4K3PassiveAbilityHead::explode()
{
	static TArray<TEnumAsByte<EObjectTypeQuery>> traceObjectTypes = { UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn) };
	TArray<AActor*> enemies;
	ALostConnectionPlayerController* controller = Utility::getPlayerController(this);
	FTransform respawnTransform = GetActorTransform();
	ALostConnectionGameState* gameState = Utility::getGameState(this);
	gameState->spawnVFXAtLocation(GetMesh()->GetComponentLocation(), explosionParticles);

	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetMesh()->GetComponentLocation(), explosionRadius, traceObjectTypes, ABaseCharacter::StaticClass(), {}, enemies);

	for (AActor* enemy : enemies)
	{
		ABaseCharacter* character = Cast<ABaseCharacter>(enemy);

		if (!character->getIsAlly())
		{
			FHitResult characterHit(character, character->GetMesh(), character->GetActorLocation(), {});

			USN4K3ResurrectDeathEvent* resurrect = NewObject<USN4K3ResurrectDeathEvent>(character);

			resurrect->initDeathEvent(character);

			resurrect->init(controller, respawnTransform);

			character->statusInflictorImpactAction(ailmentInflictorUtility, characterHit);

			character->takeDamageFromInflictor(ailmentInflictorUtility);

			character->getTimers().addTimer
			(
				[character, resurrect]() { character->detachDeathEvent(resurrect); },
				0.0f,
				false,
				character->getSwarm()->getRemainingDuration()
			);
		}
	}

	isExploded = true;
}

void ASN4K3PassiveAbilityHead::destroyHead()
{
	ULostConnectionAssetManager& manager = ULostConnectionAssetManager::get();

	ADeathPlaceholder* placeholder = Utility::getGameState(this)->spawn<ADeathPlaceholder>(manager.getDefaults().getDeathPlaceholder(), {});

	GetController()->Possess(placeholder);

	placeholder->FinishSpawning({ FRotator::ZeroRotator, GetActorLocation() });

	Destroy();
}

ASN4K3PassiveAbilityHead::ASN4K3PassiveAbilityHead() :
	isExploded(false)
{
	PrimaryActorTick.bCanEverTick = true;
	NetUpdateFrequency = UConstants::actorNetUpdateFrequency;

	UCapsuleComponent* capsule = GetCapsuleComponent();
	USkeletalMeshComponent* mesh = GetMesh();

	capsule->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	
	capsule->SetCollisionResponseToChannel(UConstants::shotThroughChannel, ECollisionResponse::ECR_Ignore);

	mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	mesh->SetCollisionResponseToChannel(UConstants::shotThroughChannel, ECollisionResponse::ECR_Ignore);

	mesh->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);

	mesh->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
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

void ASN4K3PassiveAbilityHead::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		if (isExploded && IsValid(GetController()))
		{
			this->destroyHead();

			return;
		}
	}
}

UAilmentInflictorUtility* ASN4K3PassiveAbilityHead::getAilmentInflictorUtility() const
{
	return nullptr;

	// return ailmentInflictorUtility;
}
