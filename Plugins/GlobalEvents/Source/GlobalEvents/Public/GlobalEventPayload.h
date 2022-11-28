// Copyright Bartosz Kliś - Game Development. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GlobalEventPayload.generated.h"

/**
 * This is a proposed base class for Global Event Payloads.
 * Using it is completely voluntary. Any UObject can be used instead.
 * The object properties can be exposed to the Event Node (through a setting on the node itself).
 */
UCLASS(BlueprintType, Blueprintable, MinimalAPI)
class UGlobalEventPayload : public UObject
{
	GENERATED_BODY()

public:
	/** The Actor that Invoked this Event. Can be null. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	AActor* Instigator;
};
