#include "SN4K3ThirdAbilityFlag.h"

#include "Kismet/KismetSystemLibrary.h"

#include "Characters/BaseCharacter.h"
#include "Interfaces/Gameplay/Descriptions/Caster.h"

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

			TSet<AActor*> possibleTargets(std::move(tem));
			TSet<AActor*> removeAbilityEffectTargets = targets.Difference(possibleTargets);

			for (auto& i : possibleTargets)
			{
				ABaseCharacter* target = Cast<ABaseCharacter>(i);

				if (targets.Contains(target))
				{
					continue;
				}

				ability->applyAbility(target);
			}

			targets = std::move(possibleTargets);

			for (auto& i : removeAbilityEffectTargets)
			{
				ability->removeAbilityEffect(Cast<ABaseCharacter>(i));
			}
		}

		if (lifetime <= 0.0f)
		{
			for (auto& i : targets)
			{
				ability->removeAbilityEffect(Cast<ABaseCharacter>(Cast<ABaseCharacter>(i)));
			}

			ability->setIsFlagExist(false);

			Destroy();
		}
	}
}

ASN4K3ThirdAbilityFlag::ASN4K3ThirdAbilityFlag()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> flagMeshFinder(TEXT("SkeletalMesh'/Game/Assets/Characters/SN4K3/Abilities/Third/Meshes/Flag.Flag'"));

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
