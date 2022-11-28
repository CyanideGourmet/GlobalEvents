// Copyright Bartosz Kliś - Game Development. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GlobalEventListenerComponent.h"
#include "UObject/Object.h"
#include "GlobalEvent.generated.h"

class UGlobalEventListenerComponent;
class UGlobalEventPayload;

/**
 * Asset describing a single Global Event.
 * Holds references to all listeners and invokes events on their owners.
 * Allows for some node customization including node color and the name of the Event Node.
 */
UCLASS(BlueprintType)
class GLOBALEVENTS_API UGlobalEvent : public UObject
{
	GENERATED_BODY()

public:
	UGlobalEvent();


	/** >>>>>>>>>>>>>>>>> Payload >>>>>>>>>>>>>>>>> */
	//////////////////////////////////////////////////
protected:
	/**
	 * Supplied class will be used as the template for exposed pins on the Event Node.
	 * Can be left as null, Event Node allows for passing the entire payload object.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Events, meta=(GetByRef))
	TSubclassOf<UObject> PayloadTemplate;

public:
	UClass* GetPayloadTemplate() const;
	/** <<<<<<<<<<<<<<<<< Payload <<<<<<<<<<<<<<<<< */


	/** =========================================---------========================================= */


	/** >>>>>>>>>>>>>>>>> Main Functionality >>>>>>>>>>>>>>>>> */
	/////////////////////////////////////////////////////////////
private:
	/**
	 * The components currently listening to this Event.
	 * This array is modified by Listeners themselves and shouldn't be modified manually.
	 */
	UPROPERTY(Transient, BlueprintGetter=GetListeners, Category = Events)
	TArray<UGlobalEventListenerComponent*> Listeners;

public:
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	const TArray<UGlobalEventListenerComponent*>& GetListeners() const;

	/**
	 * Invokes the Event, sending it to all registered Listeners.
	 * Optionally a Payload with Event Data can be sent through and received by the Listener.
	 * This function is most useful for calling events from C++, in blueprints prefer UGlobalEventFunctionLibrary::InvokeEvent or the polymorphic Invoke Event node.
	 * @param Payload Object containing event data sent over to the listeners, can be any object. A default Payload Template has been supplied (UGlobalEventPayload).
	 */
	UFUNCTION(BlueprintCallable, Category = Events, meta=(AdvancedDisplay="Payload"))
	void InvokeEvent(UObject* Payload);
	/** <<<<<<<<<<<<<<<<< Main Functionality <<<<<<<<<<<<<<<<< */


	/** =========================================---------========================================= */


	/** >>>>>>>>>>>>>>>>> Node Customization >>>>>>>>>>>>>>>>> */
	/////////////////////////////////////////////////////////////
protected:
	/** Allows for Node customization. */
	UPROPERTY(EditDefaultsOnly, Category = Events)
	bool bCustomizeNode;

private:
	/** The default name of the Event. */
	const FString DefaultEventName;

protected:
	/** The custom name of the Event, visible on the Event Node. */
	UPROPERTY(EditDefaultsOnly, Category = "Events|Customization", meta=(EditCondition="bCustomizeNode", EditConditionHides))
	FString EventName;

public:
	FString GetEventName() const;

	/** Constructs the default name using supplied string as base. Usually called with GetName(). */
	static FString ConstructDefaultEventName(FString EventNameBase);

#if WITH_EDITORONLY_DATA

protected:
	/** The color this Event's Node will be displayed in. */
	UPROPERTY(EditDefaultsOnly, Category = "Events|Customization", meta=(EditCondition="bCustomizeNode", EditConditionHides))
	FLinearColor NodeColor;
#endif

#if WITH_EDITOR

public:
	const FLinearColor& GetNodeColor() const;
#endif


	/** Resets all values from the 'Customization' subcategory to their defaults. */
	UFUNCTION(CallInEditor, Category = "Events")
	void ResetCustomization();
	/** <<<<<<<<<<<<<<<<< Node Customization <<<<<<<<<<<<<<<<< */


	friend void UGlobalEventListenerComponent::RegisterEvent(UGlobalEvent*);
	friend void UGlobalEventListenerComponent::UnregisterEvent(UGlobalEvent*);
};
