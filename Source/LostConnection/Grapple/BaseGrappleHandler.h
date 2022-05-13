// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Network/NetworkObject.h"
#include "BaseGrapple.h"
#include "Engine/LostConnectionPlayerController.h"

#include "BaseGrappleHandler.generated.h"

#pragma warning(disable: 4458)

UCLASS(BlueprintType, Blueprintable)
class LOSTCONNECTION_API UBaseGrappleHandler : public UNetworkObject
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Category = Grapple, EditDefaultsOnly, Replicated, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABaseGrapple> grappleClass;

	UPROPERTY(Category = Grapple, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class ABaseDrone> drone;

private:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UBaseGrappleHandler() = default;

	void init(TObjectPtr<class ABaseDrone> drone);

	UFUNCTION(Category = Actions, BlueprintImplementableEvent)
	void grappleActionPress();

	UFUNCTION(Category = Actions, BlueprintImplementableEvent)
	void grappleActionRelease();

	virtual UWorld* GetWorld() const override;

	virtual ~UBaseGrappleHandler() = default;
};
