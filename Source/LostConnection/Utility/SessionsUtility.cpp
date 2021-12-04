// Copyright (c) 2021 Use-your-imagination

#include "SessionsUtility.h"

void USessionsUtility::getFindedSessionName(const FBlueprintSessionResult& sessionResult, FString& sessionName, EExecutionOutputs& branches)
{
	auto it = sessionResult.OnlineResult.Session.SessionSettings.Settings.Find("ServerName");

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
