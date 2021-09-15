#include "SessionsUtility.h"

void USessionsUtility::getFindedSessionName(const FBlueprintSessionResult& sessionResult, FString& sessionName, TEnumAsByte<executionOutputs>& branches)
{
	auto it = sessionResult.OnlineResult.Session.SessionSettings.Settings.Find("ServerName");

	if (it)
	{
		branches = executionOutputs::Success;

		sessionName = it->Data.ToString();
	}
	else
	{
		branches = executionOutputs::Fail;
	}
}
