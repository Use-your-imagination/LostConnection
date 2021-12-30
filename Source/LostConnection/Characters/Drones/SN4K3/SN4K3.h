// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Characters/BaseDrone.h"

#include "SN4K3.generated.h"

#pragma warning(disable: 4458)

UCLASS()
class LOSTCONNECTION_API ASN4K3 : public ABaseDrone
{
	GENERATED_BODY()

private:
	UFUNCTION()
	void onBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	void deathLogic() override;

public:
	ASN4K3();

	UFUNCTION()
	void playUltimateReturnAnimation();

	virtual bool checkPassiveAbilityCast() const override;

	virtual bool checkSecondAbilityCast() const override;

	virtual bool checkThirdAbilityCast() const override;

	virtual bool checkUltimateAbilityCast() const override;

	virtual ~ASN4K3() = default;
};
