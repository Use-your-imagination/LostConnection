#include "BaseAmmo.h"

#pragma warning(disable: 4458)

void ABaseAmmo::Tick(float deltaSeconds)
{
	AddActorLocalOffset({ 0.0f, 0.0f, speed });
}

void ABaseAmmo::beginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void ABaseAmmo::endOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

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
	speed = 5.0f;

	mesh->SetSimulatePhysics(true);
	mesh->SetEnableGravity(true);
	mesh->SetCollisionEnabled(ECollisionEnabled::Type::PhysicsOnly);

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
