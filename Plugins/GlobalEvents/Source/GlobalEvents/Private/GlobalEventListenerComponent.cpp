// Copyright Bartosz Kliś - Game Development. All Rights Reserved.


#include "GlobalEventListenerComponent.h"

#include "GlobalEvent.h"


UGlobalEventListenerComponent::UGlobalEventListenerComponent()
{
	PrimaryComponentTick.bCanEverTick          = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

const TArray<UGlobalEvent*>& UGlobalEventListenerComponent::GetEvents() const
{
	return Events;
}

void UGlobalEventListenerComponent::RegisterEvent(UGlobalEvent* Event)
{
	// No duplicates
	if (Event)
	{
		Events.AddUnique(Event);
		Event->Listeners.AddUnique(this);
	}
}

void UGlobalEventListenerComponent::UnregisterEvent(UGlobalEvent* Event)
{
	if (Event)
	{
		Events.Remove(Event);
		Event->Listeners.Remove(this);
	}
}

bool UGlobalEventListenerComponent::IsEventRegistered(UGlobalEvent* Event) const
{
	return Event ? Events.Contains(Event) : nullptr;
}

void UGlobalEventListenerComponent::BeginPlay()
{
	Super::BeginPlay();

	// Cleanup possible nullptr values from editing in editor
	Events.Remove(nullptr);

	// Get rid of duplicates
	Events = TSet<UGlobalEvent*>{Events}.Array();

	for (UGlobalEvent* Event : Events)
	{
		RegisterEvent(Event);
	}
}
