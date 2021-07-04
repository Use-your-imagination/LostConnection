#include "BaseAmmo.h"

#include "../Character/LostConnectionCharacter.h"
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

	if (lostCharacter && !lostCharacter->getIsAlly())
	{
		lostCharacter->takeDamage(damage);
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
		mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

		MarkPendingKill();

		return;
	}

	if (damage <= 0.0f)
	{
		MarkPendingKill();
	}
}

void ABaseAmmo::endOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
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
	ammoType = ammoTypes::large;

	SetRootComponent(mesh);

	mesh->SetSimulatePhysics(true);
	mesh->SetEnableGravity(true);
	mesh->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);

	mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	mesh->OnComponentBeginOverlap.AddDynamic(this, &ABaseAmmo::beginOverlap);

	mesh->OnComponentEndOverlap.AddDynamic(this, &ABaseAmmo::endOverlap);
}

void ABaseAmmo::launch()
{
	UWorld* world = GetWorld();
	length = mesh->GetStaticMesh()->GetBounds().GetBox().GetSize().Y;

	if (world)
	{
		FTimerDelegate delegate;

		delegate.BindLambda([this]()
			{
				if (!IsPendingKill())
				{
					AddActorLocalOffset({ 0.0f, length, 0.0f });
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
