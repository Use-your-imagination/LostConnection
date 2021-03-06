// Copyright (c) 2022 Semyon Gritsenko

#pragma once

#include "CoreMinimal.h"

#include "UObject/NoExportTypes.h"

#include "ToolchainAction.generated.h"

/**
 * Provides method to execute toolchain of routines
 */
UCLASS(Category = "AutomationToolchain|Actions", Abstract, BlueprintType, Blueprintable)
class AUTOMATIONTOOLCHAIN_API UToolchainAction : public UObject
{
	GENERATED_BODY()
	
protected:
	/**
	* Set this variable to false to prevent executing next action in toolchain
	*/
	UPROPERTY(Category = Actions, BlueprintReadWrite)
	bool continueToolchain;

public:
	UToolchainAction();

	/**
	* Method is called in separate thread
	* Some states can be modified only from main thread
	* If so you can use Run On Main Thread function
	*/
	UFUNCTION(Category = Initialization, BlueprintImplementableEvent, Meta = (DevelopmentOnly))
	void initialization();

	/**
	* Method is called in separate thread
	* Some states can be modified only from main thread
	* If so you can use Run On Main Thread function
	*/
	UFUNCTION(Category = Actions, BlueprintImplementableEvent, Meta = (DevelopmentOnly))
	void execute();

	bool getContinueToolchain() const;

	virtual ~UToolchainAction() = default;
};
