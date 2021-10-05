#pragma once

#include "CoreMinimal.h"

#include "Characters/BaseDrone.h"

#include "SN4K3.generated.h"

UCLASS()
class LOSTCONNECTION_API ASN4K3 : public ABaseDrone
{
	GENERATED_BODY()

private:
	UFUNCTION()
	void onBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
public:
	ASN4K3();

	~ASN4K3() = default;
};
