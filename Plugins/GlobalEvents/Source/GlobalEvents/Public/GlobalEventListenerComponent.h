// Copyright Bartosz Kliś - Game Development. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GlobalEventListenerComponent.generated.h"

class UGlobalEvent;

/**
 * Used on Actors that want to listen to global events.
 * Events in the array will broadcast their invocation to all registered Listeners.
 * Registration of default values occurs automatically, during Runtime call Register/Unregister Event.
 * Spawn a polymorphic On Global Event Invoked node to handle an incoming Event.
 */
UCLASS(BlueprintType, MinimalAPI, ClassGroup=Utility, HideCategories=ComponentTick, meta=(BlueprintSpawnableComponent))
class UGlobalEventListenerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UGlobalEventListenerComponent();

	/** >>>>>>>>>>>>>>>>> Main Functionality >>>>>>>>>>>>>>>>> */
	/////////////////////////////////////////////////////////////
private:
	/** Currently Registered Events, they will broadcast their invocations to this Listener. */
	UPROPERTY(EditDefaultsOnly, BlueprintGetter=GetEvents, Category = Events, meta=(AllowPrivateAccess="true", NoElementDuplicate))
	TArray<UGlobalEvent*> Events;

public:
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	const TArray<UGlobalEvent*>& GetEvents() const;

	/**
	 * Register a new Event. Its invocation will be broadcast to this listener.
	 * There's no need to check for an Event being already bound. Only unique instances will be added.
	 * @param Event the Event to Register.
	 */
	UFUNCTION(BlueprintCallable, Category = Events)
	GLOBALEVENTS_API void RegisterEvent(UGlobalEvent* Event);
	
	/**
	 * Unregister an Event. Its invocation will not be broadcast to this listener anymore.
	 * There's no need to check for Event being already bound. Only existing instances will be removed.
	 * @param Event the Event to Unregister.
	 */
	UFUNCTION(BlueprintCallable, Category = Events)
	GLOBALEVENTS_API void UnregisterEvent(UGlobalEvent* Event);

	/**
	 * Check if event is currently registered (i.e. can be found in the Events array).
	 * @param Event the Event to be checked.
	 * @return If Event is registered true, false otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category = Events)
	GLOBALEVENTS_API bool IsEventRegistered(UGlobalEvent* Event) const;
	/** <<<<<<<<<<<<<<<<< Main Functionality <<<<<<<<<<<<<<<<< */
	
	/** UActorComponent Interface */
	virtual void BeginPlay() override;
	/** ~UActorComponent Interface */
};