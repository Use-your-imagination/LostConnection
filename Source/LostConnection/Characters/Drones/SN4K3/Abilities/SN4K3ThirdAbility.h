// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Abilities/BaseAbility.h"
#include "Interfaces/Gameplay/Descriptions/Sockets/Socketed.h"
#include "Interfaces/Gameplay/Descriptions/Sockets/Reservator.h"

#include "SN4K3ThirdAbility.generated.h"

UCLASS()
class LOSTCONNECTION_API USN4K3ThirdAbility :
	public UBaseAbility,
	public ISocketed
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = SN4K3, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float lifetime;

	UPROPERTY(Category = SN4K3, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float radius;

	UPROPERTY(Category = SN4K3, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float period;

	TWeakInterfacePtr<ISocketItem> reservator;

	bool isFlagExist;

private:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
public:
	USN4K3ThirdAbility();

	void setIsFlagExist(bool isFlagExist);

	bool getIsFlagExist() const;

	void applyAbility(class ABaseCharacter* target) override;

	void useAbility() override;

	void insert(const TScriptInterface<ISocketItem>& socketItem) override;

	void extract() override;

	ISocketItem* getSocketItem() const override;

	~USN4K3ThirdAbility() = default;
};
