#include "BaseAmmo.h"

#include "UObject/ConstructorHelpers.h"

#include "Character/LostConnectionCharacter.h"
#include "BaseWeapon.h"

#pragma warning(disable: 4458)

void ABaseAmmo::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ABaseAmmo::beginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsPendingKill() || Cast<ABaseAmmo>(OtherActor) || Cast<ABaseWeapon>(OtherActor))
	{
		return;
	}
	
	ALostConnectionCharacter* lostCharacter = Cast<ALostConnectionCharacter>(OtherActor);
	IShotThrough* shotThrough = Cast<IShotThrough>(OtherActor);

	if (lastTarget == lostCharacter)
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
		if (lostCharacter->getIsAlly())
		{
			return;
		}

		damage = damage * shotThrough->getPercentageDamageReduction_Implementation() - shotThrough->getFlatDamageReduction_Implementation();
	}
	else
	{
		mesh->SetStaticMesh(brokenAmmoMesh);

		mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

		tracer->Deactivate();

		MarkPendingKill();

		return;
	}

	if (damage <= 0.0f)
	{
		MarkPendingKill();
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
	ammoType = ammoTypes::large;
	ConstructorHelpers::FObjectFinder<UNiagaraSystem> tracerSystemFinder(TEXT("NiagaraSystem'/Game/Assets/Weapons/Ammo/NSPBulletTracer.NSPBulletTracer'"));

	SetRootComponent(mesh);

	mesh->SetSimulatePhysics(true);
	mesh->SetEnableGravity(true);
	mesh->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);

	mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	mesh->OnComponentBeginOverlap.AddDynamic(this, &ABaseAmmo::beginOverlap);

	mesh->OnComponentEndOverlap.AddDynamic(this, &ABaseAmmo::endOverlap);

	if (tracerSystemFinder.Succeeded())
	{
		tracer->SetAsset(tracerSystemFinder.Object);
	}

	tracer->SetAutoAttachmentParameters(mesh, "Tracer", EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative);

	tracer->SetUseAutoManageAttachment(true);
}

void ABaseAmmo::launch(ACharacter* character)
{
	UWorld* world = GetWorld();
	length = mesh->GetStaticMesh()->GetBounds().GetBox().GetSize().X;

	if (world)
	{
		FTimerDelegate delegate;
		isAlly = Cast<ALostConnectionCharacter>(character)->getIsAlly();

		delegate.BindLambda([this]()
			{
				if (!IsPendingKill())
				{
					AddActorLocalOffset({ length, 0.0f, 0.0f });
				}
			});

		world->GetTimerManager().SetTimer(launchHandle, delegate, 1.0f / (speed / length), true, 0.0f);
	}
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
	this->speed = speed;
}

UStaticMeshComponent* ABaseAmmo::getAmmoMesh() const
{
	return mesh;
}

float ABaseAmmo::getDamage() const
{
	return damage;
}

float ABaseAmmo::getSpeed() const
{
	return speed;
}

ammoTypes ABaseAmmo::getAmmoType() const
{
	return ammoType;
}

float ABaseAmmo::getFlatDamageReduction_Implementation() const
{
	return 0.0;
}

float ABaseAmmo::getPercentageDamageReduction_Implementation() const
{
	return 1.0;
}

ABaseAmmo::~ABaseAmmo()
{
	UWorld* world = GetWorld();

	if (world)
	{
		world->GetTimerManager().ClearTimer(launchHandle);
	}
}
