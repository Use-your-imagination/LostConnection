// Copyright (c) 2021 Use Your Imagination

#include "SN4K3ThirdAbilityFlag.h"

#include "Kismet/KismetSystemLibrary.h"

#include "Characters/BaseCharacter.h"
#include "Interfaces/Gameplay/Descriptions/Caster.h"
#include "Constants/Constants.h"

#pragma warning(disable: 4458)

void ASN4K3ThirdAbilityFlag::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (HasAuthority())
	{
		lifetime -= DeltaSeconds;

		currentTime += DeltaSeconds;

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
			Destroy();
		}
	}
}

ASN4K3ThirdAbilityFlag::ASN4K3ThirdAbilityFlag()
{
	NetUpdateFrequency = UConstants::minNetUpdateFrequency;

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
