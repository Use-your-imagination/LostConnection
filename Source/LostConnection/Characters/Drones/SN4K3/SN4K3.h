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
	UPROPERTY(Category = SN4K3, VisibleAnywhere, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	int32 naniteMeter;

	UPROPERTY(Category = SN4K3, VisibleAnywhere, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	bool isUltimateAbilityPressed;

	class ASN4K3UltimateAbilityPlaceholder* ultimatePlaceholder;

private:
	void PostInitializeComponents() override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

private:
	UFUNCTION()
	void onBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	ASN4K3();

	void setUltimatePlaceholder(class ASN4K3UltimateAbilityPlaceholder* ultimatePlaceHolder);

	int32& getNaniteMeter();

	bool& getIsUltimateAbilityUsed();

	class ASN4K3UltimateAbilityPlaceholder* getUltimatePlaceholder();
	
	void castFirstAbilityVisual() override;

	void castSecondAbilityVisual() override;

	void castThirdAbilityVisual() override;

	void castUltimateAbilityVisual() override;

	~ASN4K3() = default;
};

inline int32& ASN4K3::getNaniteMeter()
{
	return naniteMeter;
}
