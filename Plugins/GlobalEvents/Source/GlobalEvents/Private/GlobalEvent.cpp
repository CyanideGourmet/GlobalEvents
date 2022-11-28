// Copyright Bartosz Kliś - Game Development. All Rights Reserved.

#include "GlobalEvent.h"

#include "GlobalEventListenerComponent.h"
#include "GenericPlatform/GenericPlatformMemory.h"
#include "GlobalEventPayload.h"


constexpr FLinearColor DefaultNodeColor{0.3960784314f, 0.f, 0.f, 1.f};

constexpr int32        EventAssetPrefixNum = 2;
constexpr const TCHAR* EventAssetPrefixes[EventAssetPrefixNum]{TEXT("EV_"), TEXT("EVT_")};

UGlobalEvent::UGlobalEvent() : DefaultEventName(ConstructDefaultEventName(GetName()))
{
	PayloadTemplate = UGlobalEventPayload::StaticClass();

	bCustomizeNode = false;
	ResetCustomization();
}

UClass* UGlobalEvent::GetPayloadTemplate() const
{
	return PayloadTemplate;
}

const TArray<UGlobalEventListenerComponent*>& UGlobalEvent::GetListeners() const
{
	return Listeners;
}

void UGlobalEvent::InvokeEvent(UObject* Payload)
{
	// Event invocation logic (UFunction::Invoke ???)
}

FString UGlobalEvent::GetEventName() const
{
	return (bCustomizeNode && !EventName.IsEmpty()) ? EventName : DefaultEventName;
}

#if WITH_EDITOR
const FLinearColor& UGlobalEvent::GetNodeColor() const
{
	return bCustomizeNode ? NodeColor : DefaultNodeColor;
}
#endif

FString UGlobalEvent::ConstructDefaultEventName(FString EventNameBase)
{
	// Remove predefined prefixes
	for (int32 Pref = 0; Pref < EventAssetPrefixNum && EventNameBase.RemoveFromStart(EventAssetPrefixes[Pref]); ++Pref) {}
	return FString::Printf(TEXT("On %s Invoked"), *EventNameBase);
}

void UGlobalEvent::ResetCustomization()
{
	EventName = ConstructDefaultEventName(GetName());

#if WITH_EDITOR
	NodeColor = DefaultNodeColor;
#endif
}
