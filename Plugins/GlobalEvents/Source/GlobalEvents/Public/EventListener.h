// Copyright Bartosz Kliś - Game Development. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EventListener.generated.h"

class UGlobalEvent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEventInvoked);

UCLASS(BlueprintType, ClassGroup=Utility, meta=(BlueprintSpawnableComponent))
class GLOBALEVENTS_API UEventListener : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Events, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UGlobalEvent> Event;

public:
	UFUNCTION(BlueprintCallable, Category = Events)
	void SetEvent(UGlobalEvent* NewEvent, bool AutoRegister);

	UGlobalEvent* GetEvent() const;

	
protected:
	UPROPERTY(EditDefaultsOnly, Category = Events)
	bool bAutoRegisterEvent;

	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Events, meta=(AllowPrivateAccess="true"))
	bool bIsEventRegistered;
	
public:
	bool IsEventRegistered() const;
	
public:
	UPROPERTY(BlueprintAssignable, Category = Events)
	FOnEventInvoked OnEventInvoked;
	
	UFUNCTION(BlueprintCallable, Category = Events)
	void RegisterEvent();

	UFUNCTION(BlueprintCallable, Category = Events)
	void UnregisterEvent();


	/** UActorComponent Interface */
	virtual void BeginPlay() override;
	/** ~UActorComponent Interface */
};