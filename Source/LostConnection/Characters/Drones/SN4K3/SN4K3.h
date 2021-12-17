// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Characters/BaseDrone.h"
#include "SN4K3Reservator.h"

#include "SN4K3.generated.h"

#pragma warning(disable: 4458)

UCLASS()
class LOSTCONNECTION_API ASN4K3 : public ABaseDrone
{
	GENERATED_BODY()

private:
	TWeakObjectPtr<class ASN4K3UltimateAbilityPlaceholder> ultimatePlaceholder;

	UPROPERTY(Category = SN4K3, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	UObject* thirdAbilityReservator;

private:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	void BeginPlay() override;

private:
	UFUNCTION()
	void onBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	void deathLogic() override;

public:
	ASN4K3();

	UFUNCTION()
	void playUltimateReturnAnimation();

	void setUltimatePlaceholder(class ASN4K3UltimateAbilityPlaceholder* ultimatePlaceHolder);

	const TWeakObjectPtr<class ASN4K3UltimateAbilityPlaceholder>& getUltimatePlaceholder() const;

	virtual bool checkSecondAbilityCast() const override;

	virtual bool checkThirdAbilityCast() const override;

	virtual bool checkUltimateAbilityCast() const override;

	virtual ~ASN4K3() = default;
};
