// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "Base/DamageInflictor.h"
#include "Base/DamageReceiver.h"

#include "DamageAffecter.generated.h"

enum class EDamageAffecterType : uint8
{
	none,
	increaser,
	decreaser
};

UINTERFACE(MinimalAPI, Meta = (CannotImplementInterfaceInBlueprint))
class UDamageAffecter : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IDamageAffecter
{
	GENERATED_BODY()

public:
	IDamageAffecter() = default;

	virtual bool affectCondition(const TScriptInterface<IDamageInflictor>& inflictor, const TScriptInterface<IDamageReceiver>& receiver) const = 0;

	virtual void affect(FDamageStructure& damage) = 0;

	virtual EDamageAffecterType getDamageAffecterType() const;
};
