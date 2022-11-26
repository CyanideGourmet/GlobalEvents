// Copyright Bartosz Kliś - Game Development. All Rights Reserved.


#include "GlobalEventAssetActions.h"

#include "GlobalEvent.h"

UClass* FAssetTypeActions_GameEvent::GetSupportedClass() const
{
	return UGlobalEvent::StaticClass();
}

FText FAssetTypeActions_GameEvent::GetName() const
{
	return INVTEXT("Global Event");
}
FColor FAssetTypeActions_GameEvent::GetTypeColor() const
{
	return FColor::Red;
}

uint32 FAssetTypeActions_GameEvent::GetCategories()
{
	return EAssetTypeCategories::Blueprint;
}
