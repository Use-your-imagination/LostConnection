// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Network/NetworkObject.h"
#include "BaseGrapple.h"
#include "Holders/Utility/CooldownableUtility.h"

#include "BaseGrappleHandler.generated.h"

#pragma warning(disable: 4458)

UCLASS(BlueprintType, Blueprintable)
class LOSTCONNECTION_API UBaseGrappleHandler :
	public UNetworkObject,
	public ICooldownable
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Category = Grapple, EditDefaultsOnly, Replicated, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABaseGrapple> grappleClass;

	UPROPERTY(Category = Grapple, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class ABaseDrone> drone;

	UPROPERTY(Category = Cooldown, Instanced, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCooldownableUtility> cooldown;

private:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UBaseGrappleHandler() = default;

	void init(TObjectPtr<class ABaseDrone> drone);

	UFUNCTION(Category = Actions, BlueprintImplementableEvent)
	void grappleActionPress();

	UFUNCTION(Category = Actions, BlueprintImplementableEvent)
	void grappleActionRelease();

	bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	UWorld* GetWorld() const override;

	float getCooldown() const override;

	float& getCurrentCooldownReference() override;

	float getCurrentCooldown() const override;

	virtual ~UBaseGrappleHandler() = default;
};
