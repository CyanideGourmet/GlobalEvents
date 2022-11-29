// Copyright Bartosz Kliś - Game Development. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "K2Node.h"
#include "Chaos/AABB.h"
#include "Chaos/AABB.h"
#include "Chaos/AABB.h"
#include "Chaos/AABB.h"

class FNodeUtils
{
public:
	static void                             GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar, UClass* ActionKey);
	static TSharedPtr<FEdGraphSchemaAction> GetEventNodeAction(UK2Node* Node, const FText& ActionCategory);
};
