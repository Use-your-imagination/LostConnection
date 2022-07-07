// Copyright (c) 2021 Use Your Imagination

#include "LostConnectionGameInstance.h"

#include "Kismet/GameplayStatics.h"

#include "LostConnectionPlayerController.h"
#include "LostConnectionGameState.h"
#include "LostConnectionPlayerState.h"
#include "Constants/Constants.h"


const FString ULostConnectionGameInstance::options = "?listen?bIsLanMatch=1";
const FName ULostConnectionGameInstance::serverNameKey = "ServerName";

void ULostConnectionGameInstance::onCreateSession(FName sessionName, bool wasSuccessful)
{
	session->OnCreateSessionCompleteDelegates.Clear();

	if (wasSuccessful)
	{
		session->OnStartSessionCompleteDelegates.AddUObject(this, &ULostConnectionGameInstance::onStartSession);

		session->StartSession(sessionName);
	}
}

void ULostConnectionGameInstance::onStartSession(FName sessionName, bool wasSuccessful)
{
	session->OnStartSessionCompleteDelegates.Clear();

	if (wasSuccessful)
	{
		TObjectPtr<APlayerController> controller = GetFirstLocalPlayerController();
		FString levelName;

		controller->SetInputMode(FInputModeGameOnly());

		controller->SetShowMouseCursor(false);

		sessionSettings->Get(SETTING_MAPNAME, levelName);

		GetWorld()->ServerTravel(levelName + options, true);
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

			for (const FOnlineSessionSearchResult& result : searchSession->SearchResults)
			{
				sessionsData->Add({ result });
			}
		}

		if (IsValid(widget.GetObject()))
		{
			IInitSessions::Execute_initSessionList(widget.GetObject());
		}
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
			sessionSettings = MakeShareable(new FOnlineSessionSettings());

			// sessionSettings->bUseLobbiesIfAvailable = true;
			sessionSettings->bUsesPresence = true;
			sessionSettings->bIsLANMatch = true;
			sessionSettings->bShouldAdvertise = true;
			sessionSettings->NumPublicConnections = 4;
			sessionSettings->bAllowJoinInProgress = true;
			sessionSettings->bAllowJoinViaPresence = true;
		}
	}
}

void ULostConnectionGameInstance::initSearchSession()
{
	searchSession = MakeShareable(new FOnlineSessionSearch());

	searchSession->bIsLanQuery = true;
	searchSession->MaxSearchResults = std::numeric_limits<int32>::max();
	searchSession->PingBucketSize = 1000;

	searchSession->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Type::Equals);
}

void ULostConnectionGameInstance::hostSession(TSharedPtr<const FUniqueNetId> userId, const FString& serverName, const TSoftObjectPtr<UWorld>& level)
{
	sessionSettings->Set(ULostConnectionGameInstance::serverNameKey, serverName, EOnlineDataAdvertisementType::Type::ViaOnlineService);

	sessionSettings->Set(SETTING_MAPNAME, level.GetAssetName(), EOnlineDataAdvertisementType::Type::ViaOnlineService);

	session->CreateSession(*userId, NAME_GameSession, *sessionSettings);
}

void ULostConnectionGameInstance::findLocalSessions(TSharedPtr<const FUniqueNetId> userId, TArray<FBlueprintSessionResult>& sessionsData, TScriptInterface<IInitSessions> widget)
{
	this->initSearchSession();

	session->FindSessions(*userId, searchSession.ToSharedRef());
}

void ULostConnectionGameInstance::createSession(const FString& serverName, TSoftObjectPtr<UWorld> level)
{
	session->OnCreateSessionCompleteDelegates.AddUObject(this, &ULostConnectionGameInstance::onCreateSession);

	this->hostSession(GetFirstGamePlayer()->GetPreferredUniqueNetId().GetUniqueNetId(), serverName, level);
}

void ULostConnectionGameInstance::findSessions(TArray<FBlueprintSessionResult>& sessionsData, TScriptInterface<IInitSessions> widget)
{
	session->OnFindSessionsCompleteDelegates.AddUObject(this, &ULostConnectionGameInstance::onFindSessions, &sessionsData, widget);

	this->findLocalSessions(GetFirstGamePlayer()->GetPreferredUniqueNetId().GetUniqueNetId(), sessionsData, widget);
}

void ULostConnectionGameInstance::destroySession(TSoftObjectPtr<UWorld> selfLevelToTravel, TSoftObjectPtr<UWorld> clientsLevelToTravel)
{
	TObjectPtr<ALostConnectionPlayerController> controller = GetWorld()->GetFirstPlayerController<ALostConnectionPlayerController>();
	auto exitPlayer = [selfLevelToTravel, clientsLevelToTravel, controller](TObjectPtr<ALostConnectionPlayerController> player)
	{
		TSoftObjectPtr<UWorld> levelToTravel = nullptr;

		if (player == controller)
		{
			levelToTravel = selfLevelToTravel;
		}
		else
		{
			levelToTravel = clientsLevelToTravel;
		}

		player->save();

		if (levelToTravel.IsNull())
		{
			UKismetSystemLibrary::QuitGame(player, player, EQuitPreference::Type::Quit, false);
		}
		else
		{
			player->ClientTravel(levelToTravel.GetAssetName(), ETravelType::TRAVEL_Absolute);
		}
	};

	if (controller->HasAuthority())
	{
		onDestroyDelegate.BindLambda([this, controller, exitPlayer](FName sessionName, bool wasSuccessful)
			{
				for (TObjectPtr<APlayerState> state : GetWorld()->GetGameState<ALostConnectionGameState>()->PlayerArray)
				{
					TObjectPtr<ALostConnectionPlayerController> kickedPlayer = state->GetOwner<ALostConnectionPlayerController>();

					if (IsValid(kickedPlayer) && controller != kickedPlayer)
					{
						exitPlayer(kickedPlayer);
					}
				}

				exitPlayer(controller);
			});
	}
	else
	{
		onDestroyDelegate.BindLambda([controller, exitPlayer](FName sessionName, bool wasSuccessful)
			{
				exitPlayer(controller);
			});
	}

	session->DestroySession(NAME_GameSession, onDestroyDelegate);
}

void ULostConnectionGameInstance::loadNextLevel(TSoftObjectPtr<UWorld> nextLevel)
{
	TObjectPtr<UWorld> world = GetWorld();

	world->ServerTravel(nextLevel.GetAssetName() + world->GetAuthGameMode()->OptionsString, true);
}
