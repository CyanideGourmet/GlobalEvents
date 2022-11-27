// Copyright Bartosz Kliś - Game Development. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GlobalEventPayload.generated.h"

UCLASS(BlueprintType, Blueprintable)
class GLOBALEVENTS_API UGlobalEventPayload : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Payload, meta=(DisplayPriority="1"))
	AActor* Instigator;
};
