// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "Core.h"

#include "Engine/GameInstance.h"
#include "Online.h"
#include "Net/UnrealNetwork.h"
#include "FindSessionsCallbackProxy.h"

#include "Interfaces/Multiplayer/InitSessions.h"

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

private:
	static const FString options;

public:
	static const FName serverNameKey;

private:
	IOnlineSubsystem* subsystem;
	IOnlineSessionPtr session;
	TSharedPtr<FOnlineSessionSettings> sessionSettings;
	TSharedPtr<FOnlineSessionSearch> searchSession;

private:
	FOnDestroySessionCompleteDelegate onDestroyDelegate;

private:
	void Init() override;

	void initSearchSession();

public:
	ULostConnectionGameInstance() = default;

	void hostSession(TSharedPtr<const FUniqueNetId> userId, FName sessionName, const TSoftObjectPtr<UWorld>& level);

	void findLocalSessions(TSharedPtr<const FUniqueNetId> userId, TArray<FBlueprintSessionResult>& sessionsData, TScriptInterface<IInitSessions> widget);

	UFUNCTION(Category = Sessions, BlueprintCallable)
	void createSession(FName sessionName, TSoftObjectPtr<UWorld> level);

	UFUNCTION(Category = Sessions, BlueprintCallable)
	void destroySession(TSoftObjectPtr<UWorld> selfLevelToTravel, TSoftObjectPtr<UWorld> clientsLevelToTravel);

	UFUNCTION(Category = Sessions, BlueprintCallable)
	void findSessions(UPARAM(ref) TArray<FBlueprintSessionResult>& sessionsData, TScriptInterface<IInitSessions> widget);

	UFUNCTION(Category = LevelLoading, BlueprintCallable)
	void loadNextLevel(TSoftObjectPtr<UWorld> nextLevel);
};
