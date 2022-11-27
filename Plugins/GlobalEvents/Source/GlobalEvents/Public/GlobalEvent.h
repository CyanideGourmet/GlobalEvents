// Copyright Bartosz Kliś - Game Development. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EventListener.h"
#include "UObject/Object.h"
#include "UObject/Object.h"
#include "GlobalEvent.generated.h"

class UEventListener;
class UGlobalEventPayload;

UCLASS(BlueprintType)
class GLOBALEVENTS_API UGlobalEvent : public UObject
{
	GENERATED_BODY()

public:
	UGlobalEvent();
	
private:
	UPROPERTY(VisibleAnywhere, Category = Events)
	TArray<TObjectPtr<UEventListener>> Listeners;
	
	void RegisterListener(UEventListener* Listener);
	void UnregisterListener(UEventListener* Listener);
	
	friend void UEventListener::RegisterEvent();
	friend void UEventListener::UnregisterEvent();


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Events, meta=(AllowPrivateAccess="true"))
	TSubclassOf<UGlobalEventPayload> Payload;
	
public:
	TSubclassOf<UGlobalEventPayload> GetPayloadClass() const;
	
	UFUNCTION(BlueprintCallable, Category = Events)
	void InvokeEvent();
};
