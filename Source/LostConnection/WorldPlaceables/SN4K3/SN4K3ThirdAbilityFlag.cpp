#include "SN4K3ThirdAbilityFlag.h"

ASN4K3ThirdAbilityFlag::ASN4K3ThirdAbilityFlag()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> flagMeshFinder(TEXT("StaticMesh'/Game/Assets/Weapons/Ammo/BallBulletBroken.BallBulletBroken'"));

	mesh->SetSkeletalMesh(flagMeshFinder.Object);
}
