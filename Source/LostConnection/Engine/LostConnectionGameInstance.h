// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "Core.h"

#include "Engine/GameInstance.h"
#include "Online.h"
#include "Net/UnrealNetwork.h"
#include "FindSessionsCallbackProxy.h"

#include "Interfaces/Multiplayer/InitSessions.h"
#include "Utility/UtilityStructures.h"

#include "LostConnectionGameInstance.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDestroySessionCompleteCallback, FName, sessionName, bool, wasSuccessful);

UCLASS()
class LOSTCONNECTION_API ULostConnectionGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:
	void onCreateSession(FName sesisonName, bool wasSuccessful);

	void onStartSession(FName sessionName, bool wasSuccessful);

	void onFindSessions(bool wasSuccessful, TArray<FBlueprintSessionResult>* sessionsData, TScriptInterface<IInitSessions> widget);

	void onJoinSession(FName sessionName, EOnJoinSessionCompleteResult::Type type, FStandardDelegate onSuccess, FStandardDelegate onFail);

	void onJoinSessionWithInvite(FName sessionName, EOnJoinSessionCompleteResult::Type type);

	void onInviteAccept(const bool wasSuccessful, const int32 controllerId, FUniqueNetIdPtr userId, const FOnlineSessionSearchResult& inviteResult);

private:
	UPROPERTY(Category = Options, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	FString hostSessionOptions;

public:
	static const FName serverNameKey;

private:
	TObjectPtr<IOnlineSubsystem> subsystem;
	IOnlineSessionPtr session;
	TSharedPtr<FOnlineSessionSettings> sessionSettings;
	TSharedPtr<FOnlineSessionSearch> searchSession;

private:
	FOnDestroySessionCompleteDelegate onDestroyDelegate;

private:
	void Init() override;

	void initSearchSession();

protected:
	UFUNCTION(Category = Join, BlueprintImplementableEvent)
	void onInviteAcceptProcess(const FBlueprintSessionResult& inviteResult);

public:
	ULostConnectionGameInstance() = default;

	void hostSession(TSharedPtr<const FUniqueNetId> userId, const FString& serverName, const TSoftObjectPtr<UWorld>& level);

	void findOnlineSessions(TSharedPtr<const FUniqueNetId> userId, TArray<FBlueprintSessionResult>& sessionsData, TScriptInterface<IInitSessions> widget);

	UFUNCTION(Category = Sessions, BlueprintCallable)
	void createSession(const FString& serverName, TSoftObjectPtr<UWorld> level);

	UFUNCTION(Category = Sessions, BlueprintCallable)
	void findSessions(UPARAM(ref) TArray<FBlueprintSessionResult>& sessionsData, TScriptInterface<IInitSessions> widget);

	UFUNCTION(Category = Sessions, BlueprintCallable, Meta = (AutoCreateRefTerm = "onSuccess, onFail"))
	void joinSession(const FBlueprintSessionResult& sessionToJoin, const FStandardDelegate& onSuccess, const FStandardDelegate& onFail);

	UFUNCTION(Category = Sessions, BlueprintCallable)
	void destroySession(TSoftObjectPtr<UWorld> selfLevelToTravel, TSoftObjectPtr<UWorld> clientsLevelToTravel);

	UFUNCTION(Category = LevelLoading, BlueprintCallable)
	void loadNextLevel(TSoftObjectPtr<UWorld> nextLevel);
};
