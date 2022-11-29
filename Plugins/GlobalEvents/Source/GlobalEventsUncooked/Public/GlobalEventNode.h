// Copyright Bartosz Kliś - Game Development. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "K2Node_CustomEvent.h"
#include "GlobalEventNode.generated.h"

class UGlobalEvent;

UENUM(BlueprintType, meta=(Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum EGlobalEventNodeFlags
{
	Null = 0b00 UMETA(Hidden),
	Polymorphic = 0b01 UMETA(DisplayName="Polymorphic Pins"),
	PayloadObject = 0b10 UMETA(DisplayName="Payload Object"),
};

ENUM_CLASS_FLAGS(EGlobalEventNodeFlags);

UCLASS()
class GLOBALEVENTSUNCOOKED_API UK2Node_GlobalEvent : public UK2Node_EditablePinBase, public IK2Node_EventNodeInterface
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Export)
	TSoftObjectPtr<UGlobalEvent> Event;

	UPROPERTY(EditDefaultsOnly, meta=(Bitmask, BitmaskEnum = "EGlobalEventNodeFlags"))
	uint8 NodeFlags;

public:
	UK2Node_GlobalEvent();

	/** UObject Interface */
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	virtual void PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph) override;
	/** UObject Interface */

	/** UEdGraphNode Interface */
	virtual void         AllocateDefaultPins() override;
	virtual FText        GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual FLinearColor GetNodeBodyTintColor() const override;
	virtual FText        GetTooltipText() const override;
	virtual FSlateIcon   GetIconAndTint(FLinearColor& OutColor) const override;
	virtual bool         ShowPaletteIconOnNode() const override;
	virtual void         ReconstructNode() override;
	/** ~UEdGraphNode Interface */

	/** UK2Node Interface */
	virtual bool                  NodeCausesStructuralBlueprintChange() const override;
	virtual bool                  DrawNodeAsEntry() const override;
	virtual FText                 GetMenuCategory() const override;
	virtual void                  GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
	virtual void                  ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
	virtual FNodeHandlingFunctor* CreateNodeHandler(FKismetCompilerContext& CompilerContext) const override;
	virtual bool                  ShouldShowNodeProperties() const override;
	/** ~UK2Node Interface */

	/** UK2Node_EditablePinBase Interface */
	virtual bool         CanCreateUserDefinedPin(const FEdGraphPinType& InPinType, EEdGraphPinDirection InDesiredDirection, FText& OutErrorMessage) override;
	virtual UEdGraphPin* CreatePinFromUserDefinition(const TSharedPtr<FUserPinInfo> NewPinInfo) override;
	/** ~UK2Node_EditablePinBase Interface */

	/** IK2Node_EventNodeInterface */
	virtual TSharedPtr<FEdGraphSchemaAction> GetEventNodeAction(const FText& ActionCategory) override;
	/** ~IK2Node_EventNodeInterface */

	virtual void RefreshPinInfos();

protected:
	virtual bool CheckForErrors() const;

	/** Text Caches */
	FNodeTextCache CachedTitle;
	FNodeTextCache CachedFullTitle;
	FNodeTextCache CachedTooltip;

	/** Pin Infos */
	bool bPinInfoDirty;

	TSharedPtr<FUserPinInfo>         PayloadPinInfo;
	TArray<TSharedPtr<FUserPinInfo>> PolymorphicPinInfos;

#if WITH_EDITORONLY_DATA
	TArray<FName> DirtyingPropertyNames;
#endif
};
