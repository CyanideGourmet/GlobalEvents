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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Events)
	UClass* PayloadTemplate;

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

protected:
	/**
	 * Used internally to fetch all relevant properties from the given function.
	 * @param Func the Function that will be searched.
	 * @param OutPayloadParam optional Payload out argument. Will contain the function's Payload property (if it has one).
	 * @return The array of all normal function parameters (with CPF_Param).
	 */
	static TArray<FProperty*> GetFunctionParams(const UFunction* Func, FProperty** OutPayloadParam = nullptr);

private:
	/**
	 * Used internally when no Payload is supplied.
	 */
	void InvokeNoPayload();

	/**
	 * Used internally when payload is supplied.
	 */
	void InvokeWithPayload(UObject* Payload);

public:
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
	/** The color this Event Node's Header will be displayed in. */
	UPROPERTY(EditDefaultsOnly, Category = "Events|Customization", meta=(EditCondition="bCustomizeNode", EditConditionHides))
	FLinearColor NodeHeaderColor;

	/** The color this Event Node's Body will be displayed in. */
	UPROPERTY(EditDefaultsOnly, Category = "Events|Customization", meta=(EditCondition="bCustomizeNode", EditConditionHides))
	FLinearColor NodeBodyColor;

	/** The color this Event Node's Comment will be displayed in. */
	UPROPERTY(EditDefaultsOnly, Category = "Events|Customization", meta=(EditCondition="bCustomizeNode", EditConditionHides))
	FLinearColor NodeCommentColor;

	/** The custom Node Tooltip/Description used for this Event. */
	UPROPERTY(EditDefaultsOnly, Category = "Events|Customization", meta=(EditCondition="bCustomizeNode", EditConditionHides))
	FText NodeDescription;

#endif

#if WITH_EDITOR

public:
	const FLinearColor& GetNodeHeaderColor() const;
	const FLinearColor& GetNodeBodyColor() const;
	FString             GetNodeDescription() const;
#endif


	/** Resets all values from the 'Customization' subcategory to their defaults. */
	UFUNCTION(CallInEditor, Category = "Events")
	void ResetCustomization();
	/** <<<<<<<<<<<<<<<<< Node Customization <<<<<<<<<<<<<<<<< */


	friend void UGlobalEventListenerComponent::RegisterEvent(UGlobalEvent*);
	friend void UGlobalEventListenerComponent::UnregisterEvent(UGlobalEvent*);
};
