// Copyright (c) 2021 Use-your-imagination

#include "SN4K3ThirdAbilityFlag.h"

#include "Kismet/KismetSystemLibrary.h"

#include "Characters/BaseCharacter.h"
#include "Interfaces/Gameplay/Descriptions/Caster.h"
#include "Constants/Constants.h"

#pragma warning(disable: 4458)

void ASN4K3ThirdAbilityFlag::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		lifetime -= DeltaTime;

		currentTime += DeltaTime;

		if (currentTime >= period)
		{
			currentTime -= period;
			TArray<AActor*> tem;

			UKismetSystemLibrary::SphereOverlapActors(GetWorld(), mesh->GetComponentLocation(), radius, traceObjectTypes, ABaseCharacter::StaticClass(), {}, tem);

			for (auto& i : tem)
			{
				ABaseCharacter* character = Cast<ABaseCharacter>(i);

				if (character->getIsAlly())
				{
					ability->applyAbility(character);
				}
			}
		}

		if (lifetime <= 0.0f)
		{
			ability->setIsFlagExist(false);

			Destroy();
		}
	}
}

ASN4K3ThirdAbilityFlag::ASN4K3ThirdAbilityFlag()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> flagMeshFinder(TEXT("SkeletalMesh'/Game/Assets/Characters/SN4K3/Abilities/Third/Meshes/Flag.Flag'"));

	NetUpdateFrequency = UConstants::minNetUpdateFrequency;

	mesh->SetSkeletalMesh(flagMeshFinder.Object);

	mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	traceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

	mesh->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
}

void ASN4K3ThirdAbilityFlag::setLifetime(float lifetime)
{
	this->lifetime = lifetime;
}

void ASN4K3ThirdAbilityFlag::setAbility(USN4K3ThirdAbility* ability)
{
	this->ability = ability;
}

void ASN4K3ThirdAbilityFlag::setPeriod(float period)
{
	this->period = period;

	currentTime = period;
}

void ASN4K3ThirdAbilityFlag::setRadius(float radius)
{
	this->radius = radius;
}
