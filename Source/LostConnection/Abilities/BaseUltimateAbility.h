#pragma once

#include "CoreMinimal.h"

#include "BaseAbility.h"

#include "BaseUltimateAbility.generated.h"

UCLASS()
class LOSTCONNECTION_API UBaseUltimateAbility : public UBaseAbility
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(Category = Abilities, VisibleAnywhere, Replicated, BlueprintReadOnly)
	float cooldown;

	UPROPERTY(Category = Abilities, VisibleAnywhere, Replicated, BlueprintReadOnly)
	float currentCooldown;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UBaseUltimateAbility();

	virtual float getCooldown() const final;

	virtual float getCurrentCooldown() const final;

	virtual void applyAbility(class ABaseCharacter* target) override;

	virtual void useAbility() override;

	virtual void Tick(float DeltaTime) override;

	virtual ~UBaseUltimateAbility() = default;
};
