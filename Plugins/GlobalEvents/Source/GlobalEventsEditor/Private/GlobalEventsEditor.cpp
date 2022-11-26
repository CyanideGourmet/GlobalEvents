// Copyright Epic Games, Inc. All Rights Reserved.

#include "GlobalEventsEditor.h"

#define LOCTEXT_NAMESPACE "FGlobalEventsEditorModule"

void FGlobalEventsEditorModule::StartupModule()
{
	GlobalEventAssetTypeActions = MakeShared<FAssetTypeActions_GameEvent>();
	FAssetToolsModule::GetModule().Get().RegisterAssetTypeActions(GlobalEventAssetTypeActions.ToSharedRef());
}

void FGlobalEventsEditorModule::ShutdownModule()
{
	if(FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		FAssetToolsModule::GetModule().Get().UnregisterAssetTypeActions(GlobalEventAssetTypeActions.ToSharedRef());
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGlobalEventsEditorModule, GlobalEventsEditor)