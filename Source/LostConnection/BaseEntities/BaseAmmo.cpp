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

	DOREPLIFETIME(ABaseAmmo, movement);
}

void ABaseAmmo::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (HasAuthority())
	{
		
	}
}

bool ABaseAmmo::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool WroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	if (movement)
	{
		WroteSomething |= Channel->ReplicateSubobject(movement, *Bunch, *RepFlags);
	}

	return WroteSomething;
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
	ammoType = ammoTypes::large;
	ConstructorHelpers::FObjectFinder<UNiagaraSystem> tracerSystemFinder(TEXT("NiagaraSystem'/Game/Assets/Weapons/Ammo/NSPBulletTracer.NSPBulletTracer'"));
	NetUpdateFrequency = 60;

	SetRootComponent(mesh);

	mesh->SetGenerateOverlapEvents(true);

	mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	mesh->OnComponentBeginOverlap.AddDynamic(this, &ABaseAmmo::beginOverlap);

	movement->SetUpdatedComponent(mesh);

	movement->ProjectileGravityScale = 0.0f;

	movement->SetIsReplicated(true);

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
	movement->Velocity = mesh->GetForwardVector() * speed;
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
