// Copyright Bartosz Kliś - Game Development. All Rights Reserved.

#include "GlobalEvent.h"

#include "EventListener.h"
#include "GlobalEventPayload.h"

UGlobalEvent::UGlobalEvent()
{
	Payload = UGlobalEventPayload::StaticClass();
}

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

TSubclassOf<UGlobalEventPayload> UGlobalEvent::GetPayloadClass() const
{
	return Payload;
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
