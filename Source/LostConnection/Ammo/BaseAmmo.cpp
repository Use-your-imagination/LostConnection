#include "BaseAmmo.h"

#include "UObject/ConstructorHelpers.h"
#include "NiagaraFunctionLibrary.h"

#include "Weapons/BaseWeapon.h"
#include "Characters/BaseDrone.h"
#include "Interfaces/Gameplay/Descriptions/ShotThrough.h"

#pragma warning(disable: 4458)

void ABaseAmmo::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseAmmo, isAlly);

	DOREPLIFETIME(ABaseAmmo, movement);
	
	DOREPLIFETIME(ABaseAmmo, damage);

	DOREPLIFETIME(ABaseAmmo, ammoType);
}

void ABaseAmmo::onBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsPendingKill() || Cast<ABaseAmmo>(OtherActor) || Cast<UBaseWeapon>(OtherActor))
	{
		return;
	}

	ABaseCharacter* character = Cast<ABaseCharacter>(OtherActor);
	bool shotThrough = OtherActor->Implements<UShotThrough>();

	if (character && lastTarget == character)
	{
		return;
	}

	if (character && isAlly != character->getIsAlly())
	{
		character->takeDamage(damage);

		lastTarget = character;
	}

	if (shotThrough)
	{
		if (character && isAlly == character->getIsAlly())
		{
			return;
		}

		damage = damage * (1.0f - IShotThrough::Execute_getPercentageDamageReduction(OtherActor) * 0.01f) - IShotThrough::Execute_getFlatDamageReduction(OtherActor);

		if (damage > 0.0f)
		{
			UNiagaraComponent* onHit = UNiagaraFunctionLibrary::SpawnSystemAtLocation
			(
				GetWorld(),
				onHitAsset,
				GetActorLocation(),
				GetActorRotation(),
				FVector(1.0f),
				true,
				true,
				ENCPoolMethod::AutoRelease
			);

			onHit->SetNiagaraVariableBool("DeathState", false);
		}
	}
	else
	{
		damage = 0.0f;
	}

	if (damage <= 0.0f)
	{
		mesh->SetStaticMesh(brokenAmmoMesh);

		mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

		mesh->SetSimulatePhysics(true);

		movement->ProjectileGravityScale = 1.0f;

		movement->Velocity = FVector(0.0f);

		tracer->Deactivate();

		UNiagaraComponent* onHit = UNiagaraFunctionLibrary::SpawnSystemAtLocation
		(
			GetWorld(),
			onHitAsset,
			GetActorLocation(),
			GetActorRotation(),
			FVector(1.0f),
			true,
			true,
			ENCPoolMethod::AutoRelease
		);

		onHit->SetNiagaraVariableBool("DeathState", true);

		MarkPendingKill();
	}
}

UClass* ABaseAmmo::getStaticClass() const
{
	PURE_VIRTUAL(__FUNCTION__);

	return StaticClass();
}

ABaseAmmo::ABaseAmmo()
{
	PrimaryActorTick.bCanEverTick = false;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AmmoMesh"));
	tracer = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Tracer"));
	movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	ammoType = ammoTypes::large;
	NetUpdateFrequency = 60;
	ConstructorHelpers::FObjectFinder<UNiagaraSystem> tracerFinder(TEXT("NiagaraSystem'/Game/Assets/Weapons/Ammo/NPSBulletTracer.NPSBulletTracer'"));
	ConstructorHelpers::FObjectFinder<UNiagaraSystem> onHitFinder(TEXT("NiagaraSystem'/Game/Assets/Weapons/Ammo/NPSBulletOnHit.NPSBulletOnHit'"));

	SetRootComponent(mesh);

	mesh->SetGenerateOverlapEvents(true);

	mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	mesh->OnComponentBeginOverlap.AddDynamic(this, &ABaseAmmo::onBeginOverlap);

	movement->SetUpdatedComponent(mesh);

	movement->ProjectileGravityScale = 0.0f;

	movement->SetIsReplicated(true);

	if (tracerFinder.Succeeded())
	{
		tracer->SetAsset(tracerFinder.Object);
	}

	if (onHitFinder.Succeeded())
	{
		onHitAsset = onHitFinder.Object;
	}

	tracer->SetupAttachment(mesh);
}

void ABaseAmmo::launch(ACharacter* character)
{
	isAlly = Cast<ABaseDrone>(character)->getIsAlly();

	FinishSpawning({}, true);

	movement->Velocity = mesh->GetForwardVector() * movement->InitialSpeed;
}

void ABaseAmmo::copyProperties(ABaseAmmo* other)
{

}

void ABaseAmmo::setAmmoMesh(UStaticMesh* mesh)
{
	this->mesh->SetStaticMesh(mesh);
}

void ABaseAmmo::setDamage(float damage)
{
	this->damage = damage;
}

void ABaseAmmo::setAmmoSpeed(float speed)
{
	movement->Velocity = mesh->GetForwardVector() * speed;
}

void ABaseAmmo::setAmmoType(ammoTypes ammoType)
{
	this->ammoType = ammoType;
}

UStaticMeshComponent* ABaseAmmo::getAmmoMeshComponent() const
{
	return mesh;
}

float ABaseAmmo::getDamage() const
{
	return damage;
}

float ABaseAmmo::getSpeed() const
{
	return movement->Velocity.Size();
}

ammoTypes ABaseAmmo::getAmmoType() const
{
	return ammoType;
}
