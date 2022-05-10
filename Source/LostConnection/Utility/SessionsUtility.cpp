// Copyright (c) 2021 Use Your Imagination

#include "SessionsUtility.h"

#include "Engine/LostConnectionGameInstance.h"

void USessionsUtility::getFindedSessionName(const FBlueprintSessionResult& sessionResult, FString& sessionName, EExecutionOutputs& branches)
{
	auto it = sessionResult.OnlineResult.Session.SessionSettings.Settings.Find(ULostConnectionGameInstance::serverNameKey);

	if (it)
	{
		branches = EExecutionOutputs::Success;

		sessionName = it->Data.ToString();
	}
	else
	{
		branches = EExecutionOutputs::Fail;
	}
}
