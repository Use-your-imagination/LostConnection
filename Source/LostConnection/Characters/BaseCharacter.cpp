#include "BaseCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"

#include "Utility/MultiplayerUtility.h"

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (currentHealth <= 0.0f)
	{
		if (HasAuthority())
		{
			Destroy();
		}
	}

	if (defaultWeaponSlot)
	{
		if (HasAuthority())
		{
			defaultWeaponSlot->reduceShootRemainigTime(DeltaSeconds);
		}
	}
}

void ABaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseCharacter, health);

	DOREPLIFETIME(ABaseCharacter, currentHealth);

	DOREPLIFETIME(ABaseCharacter, isAlly);

	DOREPLIFETIME(ABaseCharacter, currentWeapon);

	DOREPLIFETIME(ABaseCharacter, defaultWeaponSlot);
}

bool ABaseCharacter::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool wroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	wroteSomething |= Channel->ReplicateSubobject(defaultWeaponSlot, *Bunch, *RepFlags);

	return wroteSomething;
}

void ABaseCharacter::onCurrentWeaponChange()
{
	this->updateWeaponMesh();
}

void ABaseCharacter::updateWeaponMesh()
{
	if (currentWeapon)
	{
		currentWeaponMesh->SetSkeletalMesh(currentWeapon->getWeaponMesh());

		magazine->AttachToComponent(currentWeaponMesh, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false), "magazine");

		magazine->SetStaticMesh(currentWeapon->getMagazineMesh());
	}
	else
	{
		magazine->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepRelative, false));

		magazine->SetStaticMesh(nullptr);

		currentWeaponMesh->SetSkeletalMesh(nullptr);
	}
}

void ABaseCharacter::sprint()
{
	this->setMaxSpeed(575.0f);
}

void ABaseCharacter::run()
{
	this->setMaxSpeed(450.0f);
}

void ABaseCharacter::setMaxSpeed_Implementation(float speed)
{
	GetCharacterMovement()->MaxWalkSpeed = speed;
}

void ABaseCharacter::reloadVisual()
{

}

void ABaseCharacter::reloadLogic()
{
	PURE_VIRTUAL(__FUNCTION__)
}

void ABaseCharacter::runReloadLogic_Implementation()
{
	this->reloadLogic();

	IReload::Execute_reloadEventLogic(this);
}

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	USkeletalMeshComponent* mesh = ACharacter::GetMesh();
	NetUpdateFrequency = 60;

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	mesh->SetGenerateOverlapEvents(true);
	mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	currentWeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CurrentWeaponMesh"));
	currentWeaponMesh->SetupAttachment(mesh, "Hand_WeaponSocket_R");

	magazine = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Magazine"));
	magazine->SetupAttachment(currentWeaponMesh);
}
