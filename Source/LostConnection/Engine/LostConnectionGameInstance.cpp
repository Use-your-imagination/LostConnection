// Copyright (c) 2021 Use Your Imagination

#include "LostConnectionGameInstance.h"

#include "Kismet/GameplayStatics.h"

#include "Utility/Utility.h"
#include "Constants/Constants.h"

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

		GetWorld()->ServerTravel(levelName + hostSessionOptions, true);
	}
}

void ULostConnectionGameInstance::onJoinSession(FName sessionName, EOnJoinSessionCompleteResult::Type type, FStandardDelegate onSuccess, FStandardDelegate onFail)
{
	session->OnJoinSessionCompleteDelegates.Clear();

	if (type == EOnJoinSessionCompleteResult::Type::Success)
	{
		TObjectPtr<APlayerController> playerController = GetFirstLocalPlayerController();
		FString connectString;

		if (session->GetResolvedConnectString(NAME_GameSession, connectString) && playerController)
		{
			UE_LOG(LogLostConnection, Warning, TEXT("Join session: traveling to %s"), *connectString);

			onSuccess.ExecuteIfBound();

			playerController->ClientTravel(connectString, ETravelType::TRAVEL_Absolute);

			return;
		}
		else
		{
			UE_LOG(LogLostConnection, Error, TEXT("Connect string: %s, player controller: %d"), *connectString, StaticCast<bool>(playerController));
		}
	}
	else
	{
		using EOnJoinSessionCompleteResult::Type;

		FString error;

		switch (type)
		{
		case Type::AlreadyInSession:
			error = "Already in session";

			break;

		case Type::CouldNotRetrieveAddress:
			error = "Could not retrieve address";

			break;

		case Type::SessionDoesNotExist:
			error = "Session does not exist";

			break;

		case Type::SessionIsFull:
			error = "Session is full";

			break;

		case Type::UnknownError:
			error = "Unknown error";

			break;
		}

		UE_LOG(LogLostConnection, Warning, TEXT("Can't join to session. %s"), *error);
	}

	onFail.ExecuteIfBound();
}

void ULostConnectionGameInstance::onInviteAccept(const bool wasSuccessful, const int32 controllerId, FUniqueNetIdPtr userId, const FOnlineSessionSearchResult& inviteResult)
{
	if (!wasSuccessful || !inviteResult.IsValid())
	{
		UE_LOG(LogLostConnection, Warning, TEXT("onInviteAccepted callback: wasSuccessful: %d, inviteResult.IsValid(): %d"), wasSuccessful);

		return;
	}

	this->onInviteAcceptProcess({ inviteResult });
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

			sessionSettings->bUseLobbiesIfAvailable = true;
			sessionSettings->bUsesPresence = true;
			sessionSettings->bAllowInvites = true;
			sessionSettings->bShouldAdvertise = true;
			sessionSettings->NumPublicConnections = 4;
			sessionSettings->bAllowJoinInProgress = true;
			sessionSettings->bAllowJoinViaPresence = true;

			session->OnSessionUserInviteAcceptedDelegates.AddUObject(this, &ULostConnectionGameInstance::onInviteAccept);
		}
	}
}

void ULostConnectionGameInstance::hostSession(TSharedPtr<const FUniqueNetId> userId, const TSoftObjectPtr<UWorld>& level)
{
	sessionSettings->Set(SETTING_MAPNAME, level.GetAssetName(), EOnlineDataAdvertisementType::Type::ViaOnlineService);

	session->CreateSession(*userId, NAME_GameSession, *sessionSettings);
}

void ULostConnectionGameInstance::createSession(TSoftObjectPtr<UWorld> level)
{
	session->OnCreateSessionCompleteDelegates.AddUObject(this, &ULostConnectionGameInstance::onCreateSession);

	this->hostSession(GetFirstGamePlayer()->GetPreferredUniqueNetId().GetUniqueNetId(), level);
}

void ULostConnectionGameInstance::joinSession(const FBlueprintSessionResult& sessionToJoin, const FStandardDelegate& onSuccess, const FStandardDelegate& onFail)
{
	session->OnJoinSessionCompleteDelegates.AddUObject(this, &ULostConnectionGameInstance::onJoinSession, onSuccess, onFail);

	session->JoinSession(*GetFirstGamePlayer()->GetPreferredUniqueNetId().GetUniqueNetId(), NAME_GameSession, sessionToJoin.OnlineResult);
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
