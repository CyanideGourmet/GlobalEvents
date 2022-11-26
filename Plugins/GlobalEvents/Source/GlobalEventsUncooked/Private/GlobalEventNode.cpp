// Copyright Bartosz Kliś - Game Development. All Rights Reserved.


#include "GlobalEventNode.h"

#include "NodeUtils.h"

#define LOCTEXT_NAMESPACE "K2Node_GlobalEvent"


struct FEdGraphSchemaAction_K2Event;

UK2Node_GlobalEvent::UK2Node_GlobalEvent()
{
	bInternalEvent = true;
	bOverrideFunction = false;
	bIsEditable = true;
	bCanRenameNode = false;
	
	CustomFunctionName = NAME_None;
}

void UK2Node_GlobalEvent::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	FNodeUtils::GetMenuActions(ActionRegistrar, GetClass());
}

FText UK2Node_GlobalEvent::GetMenuCategory() const
{
	return LOCTEXT(LOCTEXT_NAMESPACE, "Events");
}

FText UK2Node_GlobalEvent::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return LOCTEXT(LOCTEXT_NAMESPACE, "Event Invoked");
}

FText UK2Node_GlobalEvent::GetTooltipText() const
{
	return LOCTEXT(LOCTEXT_NAMESPACE, "Called when associated event is invoked");
}

bool UK2Node_GlobalEvent::ShouldShowNodeProperties() const
{
	return true;
}


#undef LOCTEXT_NAMESPACE
