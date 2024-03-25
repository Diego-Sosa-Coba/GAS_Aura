// Copyright Deggo


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::InitializeNativeGameplayTags()
{
	GameplayTags.Attributes_Role_Tank = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Role.Tank"), FString("Affinity with Tank role"));
}
