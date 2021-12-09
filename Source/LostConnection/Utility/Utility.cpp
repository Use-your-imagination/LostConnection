// Copyright (c) 2021 Use-your-imagination

#include "Utility.h"

#include "Algo/Count.h"
#include "Kismet/KismetMathLibrary.h"

#include "Interfaces/Gameplay/Statuses/Base/StatusReceiver.h"
#include "Statuses/BaseStatus.h"

ALostConnectionGameState* Utility::getGameState(APawn* pawn)
{
	return pawn->GetWorld()->GetGameState<ALostConnectionGameState>();
}

ALostConnectionPlayerState* Utility::getPlayerState(APawn* pawn)
{
	return pawn->GetController()->GetPlayerState<ALostConnectionPlayerState>();
}

SIZE_T Utility::countStatuses(const IStatusReceiver* target, const TSubclassOf<UBaseStatus>& statusClass)
{
	const TArray<UBaseStatus*>& statuses = target->getStatuses();

	return Algo::CountIf(statuses, [&statusClass](const UBaseStatus* status) { return UKismetMathLibrary::ClassIsChildOf(statusClass, status->StaticClass()); });
}

FText Utility::getFTextFromFloat(float value)
{
	static constexpr size_t digits = 3;

	FString stringValue = FString::Printf(TEXT("%.0f"), value);
	FString thousandSymbol = FText::FromStringTable("/Game/Text/Common.Common", "ThousandSymbol").ToString();
	
	if (!(stringValue.Len() >= digits * 2 || stringValue.Len() <= digits))
	{
		stringValue.InsertAt(stringValue.Len() % digits, '.');

		while (true)
		{
			stringValue.MidInline(0, stringValue.Len() - 1);

			TCHAR last = stringValue[stringValue.Len() - 1];

			if (last == TCHAR('0') || last == TCHAR('.'))
			{
				continue;
			}

			if (stringValue.Len() <= digits + 1)
			{
				break;
			}
		}

		stringValue += thousandSymbol;
	}
	else if (stringValue.Len() >= digits * 2)
	{
		stringValue.MidInline(0, digits);

		stringValue += thousandSymbol;
	}
	
	return FText::FromString(MoveTemp(stringValue));
}
