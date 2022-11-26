// Copyright Bartosz Kliś - Game Development. All Rights Reserved.


#include "GlobalEventFactory.h"

#include "GlobalEvent.h"

UGlobalEventFactory::UGlobalEventFactory()
{
	bCreateNew = true;
	bEditAfterNew = false;
	SupportedClass = UGlobalEvent::StaticClass();
}

UObject* UGlobalEventFactory::FactoryCreateNew(UClass* Class, UObject* InParent, const FName Name, const EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UGlobalEvent>(InParent, Class, Name, Flags);
}
