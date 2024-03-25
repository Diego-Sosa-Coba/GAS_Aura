// Copyright Deggo


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::InitializeNativeGameplayTags()
{
	//////////////////////
	// VITAL ATTRIBUTES //
	//////////////////////
	GameplayTags.Attributes_Vital_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Health"), FString("Damage that can be taken before death"));
	GameplayTags.Attributes_Vital_Mana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Mana"), FString("Resource for enhanced abilities"));
	GameplayTags.Attributes_Vital_Stagger = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Stagger"), FString("Resource for defending/evading against attacks"));

	/////////////////////
	// ROLE ATTRIBUTES //
	/////////////////////
	GameplayTags.Attributes_Role_Tank = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Role.Tank"), FString("Affinity with Tank role"));
	GameplayTags.Attributes_Role_Support = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Role.Support"), FString("Affinity with Support role"));
	GameplayTags.Attributes_Role_Burst = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Role.Burst"), FString("Affinity with Burst role"));

	//////////////////////
	// STATS ATTRIBUTES //
	//////////////////////

	GameplayTags.Attributes_Stats_HealthDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Stats.HealthDamage"), FString("Damage done to Health"));
	GameplayTags.Attributes_Stats_HealthCost = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Stats.HealthCost"), FString("Cost to Health"));
	GameplayTags.Attributes_Stats_ManaCrystalCost = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Stats.ManaCrystalCost"), FString("Mana cost to use enhanced ability"));
	GameplayTags.Attributes_Stats_ManaGeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Stats.ManaGeneration"), FString("Mana generated from using ability"));
	GameplayTags.Attributes_Stats_StaggerDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Stats.StaggerDamage"), FString("Damage done to Stagger"));
	GameplayTags.Attributes_Stats_StaggerCost = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Stats.StaggerCost"), FString("Stagger cost to evade/defend"));

	//////////////////////
	// PERKS ATTRIBUTES //
	//////////////////////
	GameplayTags.Attributes_Perks_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Perks.MaxHealth"), FString("Maximum health"));
	GameplayTags.Attributes_Perks_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Perks.MaxMana"), FString("Maximum mana crystals"));
	GameplayTags.Attributes_Perks_MaxStagger = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Perks.MaxStagger"), FString("Maximum stagger"));
	GameplayTags.Attributes_Perks_ThreatGeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Perks.ThreatGeneration"), FString("Enemy threat generation"));
	GameplayTags.Attributes_Perks_CooldownReduction = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Perks.CooldownReduction"), FString("Ability cooldowns and mana generation"));
	GameplayTags.Attributes_Perks_EvasionSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Perks.EvasionSpeed"), FString("Movement speed, dodge distance, parry window"));
}
