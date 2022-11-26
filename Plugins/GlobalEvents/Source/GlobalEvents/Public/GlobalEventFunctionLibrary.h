// Copyright Bartosz Kliś - Game Development. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GlobalEventFunctionLibrary.generated.h"

class UGlobalEvent;

UCLASS()
class GLOBALEVENTS_API UGlobalEventFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Events)
	static void InvokeEvent(UGlobalEvent* Event);
};
