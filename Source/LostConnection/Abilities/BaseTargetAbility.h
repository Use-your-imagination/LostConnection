// Copyright (c) 2021 Use Your Imagination

#include "CoreMinimal.h"

#include "Abilities/BaseAbility.h"
#include "Interfaces/Gameplay/Descriptions/Target.h"

#include "BaseTargetAbility.generated.h"

UCLASS()
class LOSTCONNECTION_API UBaseTargetAbility : public UBaseAbility
{
	GENERATED_BODY()

protected:
	TWeakInterfacePtr<ITarget> target;
	
public:
	UBaseTargetAbility() = default;

	virtual void setTarget(const TWeakInterfacePtr<ITarget>& target) final;

	virtual void applyAbility(class ABaseCharacter* target) override;

	virtual void useAbility() override;
};
