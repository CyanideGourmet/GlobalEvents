// Copyright Bartosz Kliś - Game Development. All Rights Reserved.

#include "NodeUtils.h"

#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "EdGraphSchema_K2_Actions.h"

void FNodeUtils::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar, UClass* ActionKey)
{
	if(ActionRegistrar.IsOpenForRegistration(ActionKey))
	{
		UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(ActionKey);
		check(NodeSpawner != nullptr);

		ActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner);
	}
}

TSharedPtr<FEdGraphSchemaAction> FNodeUtils::GetEventNodeAction(UK2Node* Node, const FText& ActionCategory)
{
	TSharedPtr<FEdGraphSchemaAction_K2Event> EventNodeAction = MakeShareable(new FEdGraphSchemaAction_K2Event(ActionCategory, Node->GetNodeTitle(ENodeTitleType::EditableTitle), Node->GetTooltipText(), 0));
	EventNodeAction->NodeTemplate = Node;
	return EventNodeAction;
}
