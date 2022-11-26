// Copyright Bartosz Kliś - Game Development. All Rights Reserved.

#include "GlobalEvent.h"

#include "EventListener.h"

void UGlobalEvent::RegisterListener(UEventListener* Listener)
{
	if(Listener)
	{
		Listeners.AddUnique(Listener);
	}
}

void UGlobalEvent::UnregisterListener(UEventListener* Listener)
{
	if(Listener)
	{
		Listeners.Remove(Listener);
	}
}

void UGlobalEvent::InvokeEvent()
{
	for (int32 ListenerID = Listeners.Num() - 1; ListenerID >= 0; --ListenerID)
	{
		const UEventListener* Listener = Listeners[ListenerID];
		if(!Listener)
		{
			Listeners.RemoveAt(ListenerID);
			continue;
		}

		Listener->OnEventInvoked.Broadcast();
	}
}
