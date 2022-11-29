// Copyright Bartosz Kliś - Game Development. All Rights Reserved.

#include "GlobalEvent.h"

#include "GlobalEventListenerComponent.h"
#include "GlobalEventPayload.h"

constexpr FLinearColor DefaultNodeHeaderColor{0.3960784314f, 0.f, 0.f, 1.f};
constexpr FLinearColor DefaultNodeBodyColor{0.937663f, 0.f, 0.979167f, 1.f};

static FString DefaultNodeDescription{TEXT("Responds to an Invoked Global Event.\nCan deliver Payload as object, polymorphic pins, both, or not at all.\nPayload Template: {PayloadTemplate}")};

constexpr int32        EventAssetPrefixNum = 2;
constexpr const TCHAR* EventAssetPrefixes[EventAssetPrefixNum]{TEXT("EV_"), TEXT("EVT_")};

static FName PayloadPropertyName{TEXT("Payload")};

UGlobalEvent::UGlobalEvent() : DefaultEventName(ConstructDefaultEventName(GetName()))
{
	bCustomizeNode = false;
	ResetCustomization();
}

UClass* UGlobalEvent::GetPayloadTemplate() const
{
	return PayloadTemplate;
}

const TArray<UGlobalEventListenerComponent*>& UGlobalEvent::GetListeners() const
{
	return Listeners;
}

TArray<FProperty*> UGlobalEvent::GetFunctionParams(const UFunction* Func, FProperty** OutPayloadParam)
{
	TArray<FProperty*> Params;
	for (TFieldIterator<FProperty> It(Func); It && It->HasAnyPropertyFlags(CPF_Parm); ++It)
	{
		if (OutPayloadParam && It->GetFName() == PayloadPropertyName && CastField<FProperty>(*It))
		{
			*OutPayloadParam = *It;
		}
		else
		{
			Params.Add(*It);
		}
	}

	return Params;
}

void UGlobalEvent::InvokeNoPayload()
{
	for (const UGlobalEventListenerComponent* Listener : Listeners)
	{
		if (!Listener)
		{
			continue;
		}

		UFunction* EventFunction = Listener->GetOwner()->FindFunction(FName(GetEventName()));
		if (!EventFunction)
		{
			continue;
		}

		TArray<FProperty*> FunctionParamProperties = GetFunctionParams(EventFunction);

		TArray<uint8> Params;
		Params.Reserve(FunctionParamProperties.Num());
		for (const FProperty* Property : FunctionParamProperties)
		{
			TArray<uint8> Buffer;
			Buffer.AddUninitialized(Property->ElementSize);
			Property->InitializeValue(Buffer.GetData());

			Params.Append(Buffer);
		}

		Listener->GetOwner()->ProcessEvent(EventFunction, Params.GetData());
	}
}

void UGlobalEvent::InvokeWithPayload(UObject* Payload)
{
	for (const UGlobalEventListenerComponent* Listener : Listeners)
	{
		if (!Listener)
		{
			continue;
		}

		UFunction* EventFunction = Listener->GetOwner()->FindFunction(FName(GetEventName()));
		if (!EventFunction)
		{
			continue;
		}

		FProperty*         PayloadParam = nullptr;
		TArray<FProperty*> FunctionParamProperties = GetFunctionParams(EventFunction, &PayloadParam);

		TArray<uint8> Params;
		Params.Reserve(FunctionParamProperties.Num() + (PayloadParam != nullptr));

		if (PayloadParam)
		{
			TArray<uint8> Buffer;
			Buffer.AddUninitialized(PayloadParam->ElementSize);
			FMemory::Memcpy(Buffer.GetData(), &Payload, PayloadParam->ElementSize);
			Params.Append(Buffer);
		}

		for (const FProperty* FunctionProperty : FunctionParamProperties)
		{
			TArray<uint8> Buffer;
			if (
				const FProperty* PayloadProperty = Payload->GetClass()->FindPropertyByName(FunctionProperty->GetFName());
				PayloadProperty && PayloadProperty->ElementSize == FunctionProperty->ElementSize)
			{
				Buffer.AddUninitialized(PayloadProperty->ElementSize);
				PayloadProperty->CopyCompleteValue(Buffer.GetData(), PayloadProperty->ContainerPtrToValuePtr<uint8>(Payload));
			}
			else
			{
				Buffer.AddUninitialized(FunctionProperty->ElementSize);
				FunctionProperty->InitializeValue(Buffer.GetData());
			}

			Params.Append(Buffer);
		}

		Listener->GetOwner()->ProcessEvent(EventFunction, Params.GetData());
	}
}

void UGlobalEvent::InvokeEvent(UObject* Payload)
{
	return Payload ? InvokeWithPayload(Payload) : InvokeNoPayload();
}

FString UGlobalEvent::GetEventName() const
{
	return (bCustomizeNode && !EventName.IsEmpty()) ? EventName : DefaultEventName;
}

#if WITH_EDITOR
const FLinearColor& UGlobalEvent::GetNodeHeaderColor() const
{
	return bCustomizeNode ? NodeHeaderColor : DefaultNodeHeaderColor;
}

const FLinearColor& UGlobalEvent::GetNodeBodyColor() const
{
	return bCustomizeNode ? NodeBodyColor : DefaultNodeBodyColor;
}

FString UGlobalEvent::GetNodeDescription() const
{
	return bCustomizeNode ? (NodeDescription.IsEmpty() ? DefaultNodeDescription : NodeDescription.ToString()) : DefaultNodeDescription;
}

#endif

FString UGlobalEvent::ConstructDefaultEventName(FString EventNameBase)
{
	// Remove predefined prefixes
	for (int32 Pref = 0; Pref < EventAssetPrefixNum && EventNameBase.RemoveFromStart(EventAssetPrefixes[Pref]); ++Pref) {}
	return FString::Printf(TEXT("On %s Invoked"), *EventNameBase);
}

void UGlobalEvent::ResetCustomization()
{
	EventName = ConstructDefaultEventName(GetName());

#if WITH_EDITOR
	NodeHeaderColor = DefaultNodeHeaderColor;
	NodeBodyColor = DefaultNodeBodyColor;

	NodeDescription = FText();
#endif
}
