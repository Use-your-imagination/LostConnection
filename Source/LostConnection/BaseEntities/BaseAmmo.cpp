#include "BaseAmmo.h"

#include "../Character/LostConnectionCharacter.h"

#pragma warning(disable: 4458)

void ABaseAmmo::Tick(float deltaSeconds)
{
	if (!IsPendingKill())
	{
		AddActorLocalOffset({ speed, 0.0f, 0.0f });
	}
}

void ABaseAmmo::beginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsPendingKill())
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
	damage = 0.0f;
	speed = 50.0f;

	SetRootComponent(mesh);

	mesh->SetSimulatePhysics(true);
	mesh->SetEnableGravity(true);
	mesh->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);

	mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	mesh->OnComponentBeginOverlap.AddDynamic(this, &ABaseAmmo::beginOverlap);

	mesh->OnComponentEndOverlap.AddDynamic(this, &ABaseAmmo::endOverlap);
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

float ABaseAmmo::getFlatDamageReduction_Implementation() const
{
	return 0.0;
}

float ABaseAmmo::getPercentageDamageReduction_Implementation() const
{
	return 1.0;
}
