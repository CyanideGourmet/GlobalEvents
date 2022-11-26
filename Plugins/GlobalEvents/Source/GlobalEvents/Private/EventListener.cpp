// Copyright Bartosz Kliś - Game Development. All Rights Reserved.


#include "EventListener.h"

#include "GlobalEvent.h"

void UEventListener::SetEvent(UGlobalEvent* NewEvent, const bool AutoRegister)
{
	UnregisterEvent();

	Event = NewEvent;

	if(AutoRegister)
	{
		RegisterEvent();
	}
}

UGlobalEvent* UEventListener::GetEvent() const
{
	return Event;
}

bool UEventListener::IsEventRegistered() const
{
	return bIsEventRegistered;
}

void UEventListener::RegisterEvent()
{
	UnregisterEvent();
	
	if(Event.IsNull())
	{
		return;
	}

	Event->RegisterListener(this);
	bIsEventRegistered = true;
}

void UEventListener::UnregisterEvent()
{
	if(!Event.IsNull())
	{
		Event->UnregisterListener(this);
	}

	bIsEventRegistered = false;
}

void UEventListener::BeginPlay()
{
	UActorComponent::BeginPlay();

	if(bAutoRegisterEvent)
	{
		RegisterEvent();
	}
}
