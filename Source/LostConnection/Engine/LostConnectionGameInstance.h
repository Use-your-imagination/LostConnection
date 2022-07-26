// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "Core.h"

#include "Engine/GameInstance.h"
#include "Online.h"
#include "Net/UnrealNetwork.h"
#include "FindSessionsCallbackProxy.h"

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

	void onJoinSession(FName sessionName, EOnJoinSessionCompleteResult::Type type, FStandardDelegate onSuccess, FStandardDelegate onFail);

	void onInviteAccept(const bool wasSuccessful, const int32 controllerId, FUniqueNetIdPtr userId, const FOnlineSessionSearchResult& inviteResult);

private:
	UPROPERTY(Category = Options, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	FString hostSessionOptions;

private:
	TObjectPtr<IOnlineSubsystem> subsystem;
	IOnlineSessionPtr session;
	TSharedPtr<FOnlineSessionSettings> sessionSettings;

private:
	FOnDestroySessionCompleteDelegate onDestroyDelegate;

private:
	void Init() override;

protected:
	UFUNCTION(Category = Join, BlueprintImplementableEvent)
	void onInviteAcceptProcess(const FBlueprintSessionResult& inviteResult);

public:
	ULostConnectionGameInstance() = default;

	void hostSession(TSharedPtr<const FUniqueNetId> userId, const TSoftObjectPtr<UWorld>& level);

	UFUNCTION(Category = Sessions, BlueprintCallable)
	void createSession(TSoftObjectPtr<UWorld> level);

	UFUNCTION(Category = Sessions, BlueprintCallable, Meta = (AutoCreateRefTerm = "onSuccess, onFail"))
	void joinSession(const FBlueprintSessionResult& sessionToJoin, const FStandardDelegate& onSuccess, const FStandardDelegate& onFail);

	UFUNCTION(Category = Sessions, BlueprintCallable)
	void destroySession(TSoftObjectPtr<UWorld> selfLevelToTravel, TSoftObjectPtr<UWorld> clientsLevelToTravel);

	UFUNCTION(Category = LevelLoading, BlueprintCallable)
	void loadNextLevel(TSoftObjectPtr<UWorld> nextLevel);
};
