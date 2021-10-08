#include "SN4K3ThirdAbilityFlag.h"

void ASN4K3ThirdAbilityFlag::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		lifeTime -= DeltaTime;

		if (lifeTime <= 0.0f)
		{
			Destroy();
		}
	}
}

ASN4K3ThirdAbilityFlag::ASN4K3ThirdAbilityFlag() :
	lifeTime(10.0f)
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> flagMeshFinder(TEXT("SkeletalMesh'/Game/Assets/Characters/Drone/Drone.Drone'"));

	mesh->SetSkeletalMesh(flagMeshFinder.Object);
}
