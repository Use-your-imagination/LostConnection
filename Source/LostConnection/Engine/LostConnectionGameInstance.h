#pragma once

#include "Core.h"

#include "Engine/GameInstance.h"
#include "Online.h"
#include "Net/UnrealNetwork.h"
#include "FindSessionsCallbackProxy.h"

#include "Interfaces/Multiplayer/InitSessions.h"

#include "LostConnectionGameInstance.generated.h"

UCLASS()
class LOSTCONNECTION_API ULostConnectionGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:
	void onCreateSession(FName sesisonName, bool wasSuccessful);

	void onStartSession(FName sessionName, bool wasSuccessful);

	void onFindSessions(bool wasSuccessful, TArray<FBlueprintSessionResult>* sessionsData, TScriptInterface<IInitSessions> widget);

private:
	IOnlineSubsystem* subsystem;
	IOnlineSessionPtr session;
	TSharedPtr<FOnlineSessionSettings> sessionSettings;
	TSharedPtr<FOnlineSessionSearch> searchSession;

private:
	void Init() override;

	void initSearchSession();

public:
	ULostConnectionGameInstance(const FObjectInitializer& objectInitializer);

	void hostSession(TSharedPtr<const FUniqueNetId> userId, FName sessionName);

	void findLocalSessions(TSharedPtr<const FUniqueNetId> userId, TArray<FBlueprintSessionResult>& sessionsData, TScriptInterface<IInitSessions> widget);

	UFUNCTION(BlueprintCallable)
	void createSession(FName sessionName);

	UFUNCTION(BlueprintCallable)
	void findSessions(UPARAM(ref) TArray<FBlueprintSessionResult>& sessionsData, TScriptInterface<IInitSessions> widget);
};
