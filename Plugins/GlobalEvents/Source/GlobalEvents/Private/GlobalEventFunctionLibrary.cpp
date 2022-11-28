// Copyright Bartosz Kliś - Game Development. All Rights Reserved.


#include "GlobalEventFunctionLibrary.h"

#include "GlobalEvent.h"

void UGlobalEventFunctionLibrary::InvokeEvent(UGlobalEvent* Event, UObject* Payload)
{
	if(Event)
	{
		Event->InvokeEvent(Payload);
	}
}
