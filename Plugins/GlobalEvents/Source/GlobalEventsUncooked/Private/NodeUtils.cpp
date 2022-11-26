// Copyright Bartosz Kliś - Game Development. All Rights Reserved.

#include "NodeUtils.h"

#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"

void FNodeUtils::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar, UClass* ActionKey)
{
	if(ActionRegistrar.IsOpenForRegistration(ActionKey))
	{
		UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(ActionKey);
		check(NodeSpawner != nullptr);

		ActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner);
	}
}
