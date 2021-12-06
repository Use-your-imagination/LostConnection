// Copyright (c) 2021 Use-your-imagination

#include "LostConnectionGameInstance.h"

#include "Kismet/GameplayStatics.h"

const FString ULostConnectionGameInstance::options = "?listen?bIsLanMatch=1";

void ULostConnectionGameInstance::onCreateSession(FName sessionName, bool wasSuccessful)
{
	if (wasSuccessful)
	{
		session->StartSession(sessionName);
	}
}

void ULostConnectionGameInstance::onStartSession(FName sessionName, bool wasSuccessful)
{
	if (wasSuccessful)
	{
		APlayerController* controller = GetFirstLocalPlayerController();
		FString levelName;

		controller->SetInputMode(FInputModeGameOnly());

		controller->SetShowMouseCursor(false);

		sessionSettings->Get(SETTING_MAPNAME, levelName);

		UWorld* world = GetWorld();

		if (world)
		{
			world->ServerTravel(levelName + options, true);
		}
	}
}

void ULostConnectionGameInstance::onFindSessions(bool wasSuccessful, TArray<FBlueprintSessionResult>* sessionsData, TScriptInterface<IInitSessions> widget)
{
	session->OnFindSessionsCompleteDelegates.Clear();

	if (wasSuccessful)
	{
		if (searchSession.IsValid())
		{
			sessionsData->Empty();

			for (const auto& i : searchSession->SearchResults)
			{
				sessionsData->Add({ i });
			}
		}

		IInitSessions::Execute_initSessionList(widget.GetObject());
	}
}

void ULostConnectionGameInstance::Init()
{
	subsystem = IOnlineSubsystem::Get();

	if (subsystem)
	{
		session = subsystem->GetSessionInterface();

		if (session.IsValid())
		{
			session->OnCreateSessionCompleteDelegates.AddUObject(this, &ULostConnectionGameInstance::onCreateSession);

			session->OnStartSessionCompleteDelegates.AddUObject(this, &ULostConnectionGameInstance::onStartSession);

			sessionSettings = MakeShareable(new FOnlineSessionSettings());
			
			sessionSettings->bIsLANMatch = true;
			sessionSettings->bUsesPresence = true;
			sessionSettings->bShouldAdvertise = true;
			sessionSettings->NumPublicConnections = 4;
			sessionSettings->NumPrivateConnections = 0;
			sessionSettings->bAllowJoinInProgress = true;
			sessionSettings->bAllowJoinViaPresence = true;
		}
	}
}

void ULostConnectionGameInstance::initSearchSession()
{
	searchSession = MakeShareable(new FOnlineSessionSearch());

	searchSession->bIsLanQuery = true;
	searchSession->MaxSearchResults = 5;
	searchSession->PingBucketSize = 50;

	searchSession->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Type::Equals);
}

void ULostConnectionGameInstance::hostSession(TSharedPtr<const FUniqueNetId> userId, FName sessionName, const FString& levelName)
{
	sessionSettings->Set("ServerName", sessionName.ToString(), EOnlineDataAdvertisementType::Type::ViaOnlineService);
	
	sessionSettings->Set(SETTING_MAPNAME, levelName, EOnlineDataAdvertisementType::Type::ViaOnlineService);

	session->CreateSession(*userId, sessionName, *sessionSettings);
}

void ULostConnectionGameInstance::findLocalSessions(TSharedPtr<const FUniqueNetId> userId, TArray<FBlueprintSessionResult>& sessionsData, TScriptInterface<IInitSessions> widget)
{
	session->OnFindSessionsCompleteDelegates.AddUObject(this, &ULostConnectionGameInstance::onFindSessions, &sessionsData, widget);

	this->initSearchSession();

	session->FindSessions(*userId, searchSession.ToSharedRef());
}

void ULostConnectionGameInstance::createSession(FName sessionName, const FString& levelName)
{
	this->hostSession(GetFirstGamePlayer()->GetPreferredUniqueNetId().GetUniqueNetId(), sessionName, levelName);
}

void ULostConnectionGameInstance::findSessions(TArray<FBlueprintSessionResult>& sessionsData, TScriptInterface<IInitSessions> widget)
{
	this->findLocalSessions(GetFirstGamePlayer()->GetPreferredUniqueNetId().GetUniqueNetId(), sessionsData, widget);
}

void ULostConnectionGameInstance::loadNextAct(const FString& levelName)
{
	UWorld* world = GetWorld();

	if (world)
	{
		world->ServerTravel(levelName + options, true);
	}
}

void ULostConnectionGameInstance::setNextLevelName(const FString& newNextLevelName)
{
	nextLevelName = newNextLevelName;
}

const FString& ULostConnectionGameInstance::getNextLevelName() const
{
	return nextLevelName;
}
