// Copyright Bartosz Kliś - Game Development. All Rights Reserved.


#include "GlobalEventNode.h"

// Global Events
#include "GlobalEvent.h"
#include "NodeUtils.h"

// Engine
#include "EdGraphSchema_K2.h"
#include "KismetCompiler.h"
#include "Kismet2/BlueprintEditorUtils.h"


#define LOCTEXT_NAMESPACE "K2Node_GlobalEvent"

UK2Node_GlobalEvent::UK2Node_GlobalEvent()
{
	bIsEditable = true;

	bPinInfoDirty = true;
	NodeFlags     = Null;

#if WITH_EDITOR
	DirtyingPropertyNames =
	{
		GET_MEMBER_NAME_CHECKED(UK2Node_GlobalEvent, Event),
		GET_MEMBER_NAME_CHECKED(UK2Node_GlobalEvent, NodeFlags),
	};
#endif
}

#if WITH_EDITOR
void UK2Node_GlobalEvent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	if (PropertyChangedEvent.Property)
	{
		if (DirtyingPropertyNames.Contains(PropertyChangedEvent.GetPropertyName()))
		{
			GetGraph()->NotifyGraphChanged();
			FBlueprintEditorUtils::MarkBlueprintAsModified(GetBlueprint());

			ReconstructNode();
		}
	}

	Super::PostEditChangeProperty(PropertyChangedEvent);
}

#endif

void UK2Node_GlobalEvent::PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph)
{
	UK2Node_EditablePinBase::PostLoadSubobjects(OuterInstanceGraph);

	if(HasValidBlueprint())
	{
		// Cached Event object might still be loading on original reconstruct
		ReconstructNode();
	}
}

void UK2Node_GlobalEvent::AllocateDefaultPins()
{
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);


	if (!Event.IsNull() && bPinInfoDirty)
	{
		RefreshPinInfos();
	}

	Super::AllocateDefaultPins();
}

FText UK2Node_GlobalEvent::GetNodeTitle(const ENodeTitleType::Type TitleType) const
{
	if (CachedTitle.IsOutOfDate(this) || CachedFullTitle.IsOutOfDate(this))
	{
		const FText EventName = FText::FromString(Event.IsNull() ? TEXT("On Global Event Invoked") : Event.LoadSynchronous()->GetEventName());

		FFormatNamedArguments Args;
		Args.Add(TEXT("EventName"), EventName);

		CachedTitle.SetCachedText(EventName, this);
		CachedFullTitle.SetCachedText(FText::Format(LOCTEXT(LOCTEXT_NAMESPACE, "{EventName}\nGlobal Event"), Args), this);
	}

	return TitleType != ENodeTitleType::FullTitle ? CachedTitle : CachedFullTitle;
}

FLinearColor UK2Node_GlobalEvent::GetNodeTitleColor() const
{
	return
#if WITH_EDITOR
		Event.IsNull() ? Super::GetNodeTitleColor() : Event.LoadSynchronous()->GetNodeHeaderColor();
#else
	Super::GetNodeTitleColor();
#endif
}

FLinearColor UK2Node_GlobalEvent::GetNodeBodyTintColor() const
{
	return
#if WITH_EDITOR
		Event.IsNull() ? Super::GetNodeBodyTintColor() : Event.LoadSynchronous()->GetNodeBodyColor();
#else
	Super::GetNodeBodyTintColor();
#endif
}

FText UK2Node_GlobalEvent::GetTooltipText() const
{
	if (CachedTooltip.IsOutOfDate(this))
	{
		if (Event.IsNull())
		{
			CachedTooltip.SetCachedText(FText::FromString(TEXT("Responds to an Invoked Global Event.\nCan deliver Payload as object, polymorphic pins, both, or not at all.")), this);
		}
		else
		{
			const UClass* PayloadTemplate = Event.LoadSynchronous()->GetPayloadTemplate();

			FStringFormatNamedArguments Args;
			Args.Add(TEXT("PayloadTemplate"), PayloadTemplate ? PayloadTemplate->GetName() : UObject::StaticClass()->GetName());

			CachedTooltip.SetCachedText(
				FText::FromString(FString::Format(Event.LoadSynchronous()->GetNodeDescription().GetCharArray().GetData(), Args)),
				this);
		}
	}

	return CachedTooltip;
}

FSlateIcon UK2Node_GlobalEvent::GetIconAndTint(FLinearColor& OutColor) const
{
	return Super::GetIconAndTint(OutColor);
}

bool UK2Node_GlobalEvent::ShowPaletteIconOnNode() const
{
	return true;
}

void UK2Node_GlobalEvent::ReconstructNode()
{
	UserDefinedPins.Empty();
	CachedTitle.MarkDirty();
	CachedFullTitle.MarkDirty();
	CachedTooltip.MarkDirty();

	if (!Event.IsNull())
	{
		RefreshPinInfos();

		if (NodeFlags & PayloadObject)
		{
			UserDefinedPins.Add(PayloadPinInfo);
		}

		if (NodeFlags & Polymorphic)
		{
			UserDefinedPins.Append(PolymorphicPinInfos);
		}
	}

	Super::ReconstructNode();
}

bool UK2Node_GlobalEvent::ShouldShowNodeProperties() const
{
	return true;
}

bool UK2Node_GlobalEvent::NodeCausesStructuralBlueprintChange() const
{
	return true;
}

bool UK2Node_GlobalEvent::DrawNodeAsEntry() const
{
	return true;
}

FText UK2Node_GlobalEvent::GetMenuCategory() const
{
	return LOCTEXT(LOCTEXT_NAMESPACE, "Events");
}

void UK2Node_GlobalEvent::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	FNodeUtils::GetMenuActions(ActionRegistrar, GetClass());
}

void UK2Node_GlobalEvent::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	Super::ExpandNode(CompilerContext, SourceGraph);

	auto* Schema = GetDefault<UEdGraphSchema_K2>();

	if (!CheckForErrors() || Event.IsNull())
	{
		BreakAllNodeLinks();
		return;
	}


	UK2Node_CustomEvent* CustomEvent = CompilerContext.SpawnIntermediateNode<UK2Node_CustomEvent>(this, SourceGraph);
	CustomEvent->bCallInEditor       = false;
	CustomEvent->bOverrideFunction   = false;
	CustomEvent->bInternalEvent      = true;
	CustomEvent->CustomFunctionName  = FName(Event.LoadSynchronous()->GetEventName());
	CustomEvent->UserDefinedPins     = UserDefinedPins;
	CustomEvent->FunctionFlags       = EFunctionFlags::FUNC_Event | EFunctionFlags::FUNC_Private;
	CustomEvent->bIsEditable         = false;
	CustomEvent->AllocateDefaultPins();

	for (UEdGraphPin* Pin : CustomEvent->Pins)
	{
		if (UEdGraphPin* LocalPin = FindPin(Pin->GetFName()))
		{
			CompilerContext.MovePinLinksToIntermediate(*LocalPin, *Pin);
		}
	}

	BreakAllNodeLinks();
}

FNodeHandlingFunctor* UK2Node_GlobalEvent::CreateNodeHandler(FKismetCompilerContext& CompilerContext) const
{
	return Super::CreateNodeHandler(CompilerContext);
}

bool UK2Node_GlobalEvent::CanCreateUserDefinedPin(const FEdGraphPinType& InPinType, EEdGraphPinDirection InDesiredDirection, FText& OutErrorMessage)
{
	return !Event.IsNull();
}

UEdGraphPin* UK2Node_GlobalEvent::CreatePinFromUserDefinition(const TSharedPtr<FUserPinInfo> NewPinInfo)
{
	UEdGraphPin*             NewPin   = CreatePin(EGPD_Output, NewPinInfo->PinType, NewPinInfo->PinName);
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
	K2Schema->SetPinAutogeneratedDefaultValue(NewPin, NewPinInfo->PinDefaultValue);
	return NewPin;
}

TSharedPtr<FEdGraphSchemaAction> UK2Node_GlobalEvent::GetEventNodeAction(const FText& ActionCategory)
{
	return FNodeUtils::GetEventNodeAction(this, ActionCategory);
}

bool UK2Node_GlobalEvent::CheckForErrors() const
{
	return true;
}

void UK2Node_GlobalEvent::RefreshPinInfos()
{
	auto* Schema = GetDefault<UEdGraphSchema_K2>();

	PayloadPinInfo                               = MakeShared<FUserPinInfo>();
	PayloadPinInfo->DesiredPinDirection          = EGPD_Output;
	PayloadPinInfo->PinName                      = "Payload";
	PayloadPinInfo->PinType.PinCategory          = UEdGraphSchema_K2::PC_Object;
	PayloadPinInfo->PinType.PinSubCategoryObject = UObject::StaticClass();

	PolymorphicPinInfos.Empty();
	if (
		const UClass* PayloadTemplate = Event.LoadSynchronous()->GetPayloadTemplate();
		PayloadTemplate && PayloadTemplate != UObject::StaticClass())
	{
		TArray<FProperty*> Properties;
		for (TFieldIterator<FProperty> It(PayloadTemplate); It; ++It)
		{
			Properties.Add(*It);
		}

		for (int32 PropId = Properties.Num() - 1; PropId >= 0; --PropId)
		{
			const FProperty* Property = Properties[PropId];

			FEdGraphPinType PinType;
			Schema->ConvertPropertyToPinType(Property, PinType);

			const auto PropertyPin           = MakeShared<FUserPinInfo>();
			PropertyPin->DesiredPinDirection = EGPD_Output;
			PropertyPin->PinName             = Property->GetFName();
			PropertyPin->PinType             = PinType;

			PolymorphicPinInfos.Add(PropertyPin);
		}
	}

	bPinInfoDirty = false;
}

#undef LOCTEXT_NAMESPACE
