// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GlobalEventAssetActions.h"
#include "Modules/ModuleManager.h"

class FGlobalEventsEditorModule : public IModuleInterface
{
	TSharedPtr<FAssetTypeActions_GameEvent> GlobalEventAssetTypeActions;
	
public:
	/** IModuleInterface */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	/** ~IModuleInterface */
};