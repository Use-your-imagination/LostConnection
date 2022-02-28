// Copyright (c) 2021 Use-your-imagination

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

			for (const auto& i : searchSession->SearchResults)
			{
				sessionsData->Add({ i });
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

void ULostConnectionGameInstance::hostSession(TSharedPtr<const FUniqueNetId> userId, FName sessionName, const TSoftObjectPtr<UWorld>& level)
{
	sessionSettings->Set(ULostConnectionGameInstance::serverNameKey, sessionName.ToString(), EOnlineDataAdvertisementType::Type::ViaOnlineService);

	sessionSettings->Set(SETTING_MAPNAME, level.GetAssetName(), EOnlineDataAdvertisementType::Type::ViaOnlineService);

	session->CreateSession(*userId, sessionName, *sessionSettings);
}

void ULostConnectionGameInstance::findLocalSessions(TSharedPtr<const FUniqueNetId> userId, TArray<FBlueprintSessionResult>& sessionsData, TScriptInterface<IInitSessions> widget)
{
	session->OnFindSessionsCompleteDelegates.AddUObject(this, &ULostConnectionGameInstance::onFindSessions, &sessionsData, widget);

	this->initSearchSession();

	session->FindSessions(*userId, searchSession.ToSharedRef());
}

void ULostConnectionGameInstance::createSession(FName sessionName, TSoftObjectPtr<UWorld> level)
{
	this->hostSession(GetFirstGamePlayer()->GetPreferredUniqueNetId().GetUniqueNetId(), sessionName, level);
}

void ULostConnectionGameInstance::destroySession(TSoftObjectPtr<UWorld> selfLevelToTravel, TSoftObjectPtr<UWorld> clientsLevelToTravel)
{
	ALostConnectionPlayerController* controller = GetWorld()->GetFirstPlayerController<ALostConnectionPlayerController>();
	auto exitPlayer = [selfLevelToTravel, clientsLevelToTravel, controller](ALostConnectionPlayerController* player)
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
			UKismetSystemLibrary::QuitGame(player->GetWorld(), player, EQuitPreference::Type::Quit, false);
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
				TArray<APlayerState*>& states = GetWorld()->GetGameState<ALostConnectionGameState>()->PlayerArray;

				for (APlayerState* state : states)
				{
					ALostConnectionPlayerController* kickedPlayer = state->GetOwner<ALostConnectionPlayerController>();

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

	session->DestroySession(FName(NAME_GameSession), onDestroyDelegate);
}

void ULostConnectionGameInstance::findSessions(TArray<FBlueprintSessionResult>& sessionsData, TScriptInterface<IInitSessions> widget)
{
	this->findLocalSessions(GetFirstGamePlayer()->GetPreferredUniqueNetId().GetUniqueNetId(), sessionsData, widget);
}

void ULostConnectionGameInstance::loadNextLevel(TSoftObjectPtr<UWorld> nextLevel)
{
	GetWorld()->ServerTravel(nextLevel.GetAssetName() + options);
}
