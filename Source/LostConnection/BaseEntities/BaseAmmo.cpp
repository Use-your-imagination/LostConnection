#include "BaseAmmo.h"

#include "UObject/ConstructorHelpers.h"

#include "BaseWeapon.h"
#include "Character/LostConnectionCharacter.h"
#include "Interfaces/PhysicalObjects/ShotThrough.h"

#pragma warning(disable: 4458)

void ABaseAmmo::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseAmmo, isAlly);
}

void ABaseAmmo::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ABaseAmmo::beginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsPendingKill() || Cast<ABaseAmmo>(OtherActor) || Cast<UBaseWeapon>(OtherActor))
	{
		return;
	}

	ALostConnectionCharacter* lostCharacter = Cast<ALostConnectionCharacter>(OtherActor);
	bool shotThrough = OtherActor->Implements<UShotThrough>();

	if (lostCharacter && lastTarget == lostCharacter)
	{
		return;
	}

	if (lostCharacter && isAlly != lostCharacter->getIsAlly())
	{
		lostCharacter->takeDamage(damage);

		lastTarget = lostCharacter;
	}

	if (shotThrough)
	{
		if (lostCharacter && isAlly == lostCharacter->getIsAlly())
		{
			return;
		}

		damage = damage * (1.0f - IShotThrough::Execute_getPercentageDamageReduction(OtherActor) * 0.01f) - IShotThrough::Execute_getFlatDamageReduction(OtherActor);
	}
	else
	{
		mesh->SetStaticMesh(brokenAmmoMesh);

		mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

		tracer->Deactivate();

		MarkPendingKill();

		mesh->SetSimulatePhysics(true);

		movement->ProjectileGravityScale = 1.0f;

		movement->Velocity = FVector(0.0f);

		return;
	}

	if (damage <= 0.0f)
	{
		mesh->SetStaticMesh(brokenAmmoMesh);

		mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

		tracer->Deactivate();

		MarkPendingKill();

		mesh->SetSimulatePhysics(true);

		movement->ProjectileGravityScale = 1.0f;

		movement->Velocity = FVector(0.0f);
	}
}

void ABaseAmmo::endOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IsPendingKill())
	{
		return;
	}


}

UClass* ABaseAmmo::getStaticClass() const
{
	PURE_VIRTUAL(__FUNCTION__);

	return StaticClass();
}

ABaseAmmo::ABaseAmmo()
{
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AmmoMesh"));
	tracer = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Tracer"));
	movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	ammoType = ammoTypes::large;
	ConstructorHelpers::FObjectFinder<UNiagaraSystem> tracerSystemFinder(TEXT("NiagaraSystem'/Game/Assets/Weapons/Ammo/NSPBulletTracer.NSPBulletTracer'"));

	SetRootComponent(mesh);

	mesh->SetGenerateOverlapEvents(false);

	mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	movement->SetUpdatedComponent(mesh);

	movement->ProjectileGravityScale = 0.1f;

	collision->SetupAttachment(mesh);

	collision->InitBoxExtent({ 2.5f, 0.5f, 0.5f });

	collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	collision->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);

	collision->OnComponentBeginOverlap.AddDynamic(this, &ABaseAmmo::beginOverlap);

	collision->OnComponentEndOverlap.AddDynamic(this, &ABaseAmmo::endOverlap);

	if (tracerSystemFinder.Succeeded())
	{
		tracer->SetAsset(tracerSystemFinder.Object);
	}

	tracer->SetupAttachment(mesh);
}

void ABaseAmmo::launch(ACharacter* character)
{
	isAlly = Cast<ALostConnectionCharacter>(character)->getIsAlly();

	movement->Velocity = mesh->GetForwardVector() * movement->InitialSpeed;
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
	// this->speed = speed;
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
	return movement->InitialSpeed;
}

ammoTypes ABaseAmmo::getAmmoType() const
{
	return ammoType;
}
