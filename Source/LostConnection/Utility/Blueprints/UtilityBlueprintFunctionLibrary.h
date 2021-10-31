#pragma once

#include "CoreMinimal.h"

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Misc/MessageDialog.h"
#include "Components/ListView.h"

#include "UtilityBlueprintFunctionLibrary.generated.h"

UCLASS()
class LOSTCONNECTION_API UUtilityBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(Category = Utility, BlueprintCallable, BlueprintPure)
	static FString firstSymbolToUpperCase(const FString& string);

	UFUNCTION(Category = Utility, BlueprintCallable)
	static void rebindHotkeys(const TMap<FName, FString>& newHotkeys);

	UFUNCTION(Category = Utility, BlueprintCallable)
	static void cancelCurrentAbilityAnimation(TScriptInterface<class ICaster> caster);

	UFUNCTION(Category = Utility, BlueprintCallable, BlueprintPure)
	static UObject* getSelectedItem(UListView* listView);
};
