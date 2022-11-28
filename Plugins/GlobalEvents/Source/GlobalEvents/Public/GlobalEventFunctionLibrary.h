// Copyright Bartosz Kliś - Game Development. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GlobalEventFunctionLibrary.generated.h"

class UGlobalEvent;

/**
 * A helper library for static Global Event System calls
 */
UCLASS()
class GLOBALEVENTS_API UGlobalEventFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Invokes the given Event with (Optionally) supplied Payload.
	 * @param Event the Event to be Invoked.
	 * @param Payload (optional) data to be passed to Listeners.
	 */
	UFUNCTION(BlueprintCallable, Category = Events, meta=(AdvancedDisplay="Payload"))
	static void InvokeEvent(UGlobalEvent* Event, UObject* Payload = nullptr);
};
