// Copyright Bartosz Kliś - Game Development. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "K2Node_CustomEvent.h"
#include "GlobalEventNode.generated.h"

class UGlobalEvent;


UCLASS()
class GLOBALEVENTSUNCOOKED_API UK2Node_GlobalEvent : public UK2Node_Event
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = GlobalEvent)
	TObjectPtr<UGlobalEvent> Event;

public:
	UK2Node_GlobalEvent();

	/** UEdGraphNode Interface */
	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
	virtual FText GetMenuCategory() const override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FText GetTooltipText() const override;
	/** ~UEdGraphNode Interface */

	/** UK2Node Interface */
	virtual bool ShouldShowNodeProperties() const override;
	/** ~UK2Node Interface */

	/** IK2Node_EventNodeInterface */
	/** ~IK2Node_EventNodeInterface */
};
