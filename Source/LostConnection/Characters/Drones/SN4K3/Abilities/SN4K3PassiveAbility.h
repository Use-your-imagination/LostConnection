#pragma once

#include "CoreMinimal.h"

#include "Abilities/BasePassiveAbility.h"

#include "SN4K3PassiveAbility.generated.h"

UCLASS()
class LOSTCONNECTION_API ASN4K3PassiveAbility : public ABasePassiveAbility
{
	GENERATED_BODY()

private:
	enum class directionTypes
	{
		up,
		down
	};

private:
	UPROPERTY(Category = SN4K3, VisibleAnywhere, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	int naniteMeter;

	float lastTimeAbilityUsed;

	directionTypes type;

private:
	void Tick(float DeltaTime) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
public:
	ASN4K3PassiveAbility();

	virtual void applyAbility(class ABaseCharacter* target) final override;

	virtual void useAbility() final override;

	void resetLastTimeAbilityUsed();

	~ASN4K3PassiveAbility() = default;
};
