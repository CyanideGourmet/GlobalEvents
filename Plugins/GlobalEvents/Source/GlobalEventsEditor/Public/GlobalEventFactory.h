// Copyright Bartosz Kliś - Game Development. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "GlobalEventFactory.generated.h"

UCLASS()
class GLOBALEVENTSEDITOR_API UGlobalEventFactory : public UFactory
{
	GENERATED_BODY()

public:
	UGlobalEventFactory();

	/** UFactory Interface */
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	/** ~UFactory Interface */
	
};
