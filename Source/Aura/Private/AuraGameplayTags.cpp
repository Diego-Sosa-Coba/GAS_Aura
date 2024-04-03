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
	GameplayTags.Attributes_Stats_BarrierHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Stats.BarrierHealth"), FString("Reduces incoming Enemy Health damage by percent"));
	GameplayTags.Attributes_Stats_BarrierStagger = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Stats.BarrierStagger"), FString("Reduces incoming Enemy Stagger damage by percent"));
	GameplayTags.Attributes_Stats_AbilityCooldown = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Stats.AbilityCooldown"), FString("Time before next ability can be cast"));
	GameplayTags.Attributes_Stats_AbilityCharges = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Stats.AbilityCharges"), FString("Number of times ability can be cast (separate cooldowns)"));


	//////////////////////
	// PERKS ATTRIBUTES //
	//////////////////////
	GameplayTags.Attributes_Perks_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Perks.MaxHealth"), FString("Maximum health"));
	GameplayTags.Attributes_Perks_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Perks.MaxMana"), FString("Maximum mana crystals"));
	GameplayTags.Attributes_Perks_MaxStagger = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Perks.MaxStagger"), FString("Maximum stagger"));
	GameplayTags.Attributes_Perks_ThreatGeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Perks.ThreatGeneration"), FString("Enemy threat generation"));
	GameplayTags.Attributes_Perks_CooldownReduction = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Perks.CooldownReduction"), FString("Ability cooldowns and mana generation"));
	GameplayTags.Attributes_Perks_EvasionSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Perks.EvasionSpeed"), FString("Movement speed, dodge distance, parry window"));

	////////////////
	// INPUT TAGS //
	////////////////
	GameplayTags.InputTag_Movement_MoveUp = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Movement.MoveUp"), FString("Moving character north (up)"));
	GameplayTags.InputTag_Movement_MoveDown = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Movement.MoveDown"), FString("Moving character south (down)"));
	GameplayTags.InputTag_Movement_MoveLeft = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Movement.MoveLeft"), FString("Moving character left (west)"));
	GameplayTags.InputTag_Movement_MoveRight = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Movement.MoveRight"), FString("Moving character right (east)"));
	GameplayTags.InputTag_Movement_Jump = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Movement.Jump"), FString("Jumping off the ground"));
	GameplayTags.InputTag_Movement_Dash = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Movement.Dash"), FString("Increasing movement speed"));
	GameplayTags.InputTag_Movement_Camera = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Movement.Camera"), FString("Moving character camera"));
	
	GameplayTags.InputTag_UI_Menu = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.UI.Menu"), FString("Open settings menu"));
	GameplayTags.InputTag_UI_Equipment = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.UI.Equipment"), FString("Open character equipment"));
	GameplayTags.InputTag_UI_SelectP1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.UI.SelectP1"), FString("Select character in Player 1 slot"));
	GameplayTags.InputTag_UI_SelectP2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.UI.SelectP2"), FString("Select character in Player 2 slot"));
	GameplayTags.InputTag_UI_SelectP3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.UI.SelectP3"), FString("Select character in Player 3 slot"));
	GameplayTags.InputTag_UI_SelectP4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.UI.SelectP4"), FString("Select character in Player 4 slot"));

	GameplayTags.InputTag_Abilities_WeaponAttack1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Abilities.WeaponAttack1"), FString("Weapon attack (light)"));
	GameplayTags.InputTag_Abilities_WeaponAttack2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Abilities.WeaponAttack2"), FString("Weapon attack (heavy)"));
	GameplayTags.InputTag_Abilities_WeaponDefend = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Abilities.WeaponDefend"), FString("Weapon defensive ability"));
	GameplayTags.InputTag_Abilities_SpiritAttack1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Abilities.SpiritAttack1"), FString("Spirit attack (light)"));
	GameplayTags.InputTag_Abilities_SpiritAttack2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Abilities.SpiritAttack2"), FString("Spirit attack (heavy)"));
	GameplayTags.InputTag_Abilities_SpiritDefend = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Abilities.SpiritDefend"), FString("Spirit defensive ability"));
	GameplayTags.InputTag_Abilities_SynergyMove = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Abilities.SynergyMove"), FString("Weapon and spirit combined move"));
	GameplayTags.InputTag_Abilities_EnhanceAbility = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Abilities.EnhanceAbility"), FString("Enhances weapon and/or spirit abilities"));

	/////////////
	// EFFECTS //
	/////////////
	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Effects.HitReact"), FString("Tag granted when reacting to hit"));

	////////////
	// DAMAGE //
	////////////

	// TODO: Finish incorporating these
	GameplayTags.Damage_Style_Melee = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Style.Melee"), FString("Damage Type: Melee"));
	GameplayTags.Damage_Style_Ranged = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Style.Ranged"), FString("Damage Type: Ranged"));
	GameplayTags.Damage_Style_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Style.Arcane"), FString("Damage Type: Arcane"));
	GameplayTags.Damage_Style_Summon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Style.Summon"), FString("Damage Type: Summon"));

	///////////////
	// ABILITIES //
	///////////////
	GameplayTags.Abilities_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Attack"), FString("Attack Ability Tag"));

}
