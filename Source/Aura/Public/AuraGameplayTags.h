// Copyright Deggo

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * Aura Gameplay Tags
 * 
 * Singleton containing native Gameplay Tags
 */

struct FAuraGameplayTags
{
public:
	
	static const FAuraGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();

	//////////////////////
	// VITAL ATTRIBUTES //
	//////////////////////
	FGameplayTag Attributes_Vital_Health;
	FGameplayTag Attributes_Vital_Mana;
	FGameplayTag Attributes_Vital_Stagger;

	/////////////////////
	// ROLE ATTRIBUTES //
	/////////////////////
	FGameplayTag Attributes_Role_Tank;
	FGameplayTag Attributes_Role_Support;
	FGameplayTag Attributes_Role_Burst;

	//////////////////////
	// STATS ATTRIBUTES //
	//////////////////////
	FGameplayTag Attributes_Stats_HealthDamage;
	FGameplayTag Attributes_Stats_HealthCost;
	FGameplayTag Attributes_Stats_ManaCrystalCost;
	FGameplayTag Attributes_Stats_ManaGeneration;
	FGameplayTag Attributes_Stats_StaggerDamage;
	FGameplayTag Attributes_Stats_StaggerCost;
	FGameplayTag Attributes_Stats_BarrierHealth;
	FGameplayTag Attributes_Stats_BarrierStagger;
	FGameplayTag Attributes_Stats_AbilityCooldown;
	FGameplayTag Attributes_Stats_AbilityCharges;

	//////////////////////
	// PERKS ATTRIBUTES //
	//////////////////////
	FGameplayTag Attributes_Perks_MaxHealth;
	FGameplayTag Attributes_Perks_MaxMana;
	FGameplayTag Attributes_Perks_MaxStagger;
	FGameplayTag Attributes_Perks_ThreatGeneration;
	FGameplayTag Attributes_Perks_CooldownReduction;
	FGameplayTag Attributes_Perks_EvasionSpeed;

	////////////////
	// INPUT TAGS //
	////////////////
	FGameplayTag InputTag_Movement_MoveUp;
	FGameplayTag InputTag_Movement_MoveDown;
	FGameplayTag InputTag_Movement_MoveLeft;
	FGameplayTag InputTag_Movement_MoveRight;
	FGameplayTag InputTag_Movement_Jump;
	FGameplayTag InputTag_Movement_Dash;
	FGameplayTag InputTag_Movement_Camera;

	FGameplayTag InputTag_UI_Menu;
	FGameplayTag InputTag_UI_Equipment;
	FGameplayTag InputTag_UI_SelectP1;
	FGameplayTag InputTag_UI_SelectP2;
	FGameplayTag InputTag_UI_SelectP3;
	FGameplayTag InputTag_UI_SelectP4;

	FGameplayTag InputTag_Abilities_WeaponAttack1;
	FGameplayTag InputTag_Abilities_WeaponAttack2;
	FGameplayTag InputTag_Abilities_WeaponDefend;
	FGameplayTag InputTag_Abilities_SpiritAttack1;
	FGameplayTag InputTag_Abilities_SpiritAttack2;
	FGameplayTag InputTag_Abilities_SpiritDefend;
	FGameplayTag InputTag_Abilities_SynergyMove;
	FGameplayTag InputTag_Abilities_EnhanceAbility;

	/////////////
	// EFFECTS //
	/////////////
	FGameplayTag Effects_HitReact;

	////////////
	// DAMAGE //
	////////////
	// TODO: Finish incorporating these OR delete...probably delete
	FGameplayTag Damage_Style_Melee;
	FGameplayTag Damage_Style_Ranged;
	FGameplayTag Damage_Style_Arcane;
	FGameplayTag Damage_Style_Summon;

	///////////////
	// ABILITIES //
	///////////////
	FGameplayTag Abilities_Attack;

	////////////////////
	// COMBAT SOCKETS //
	////////////////////
	FGameplayTag CombatSocket_Weapon;
	FGameplayTag CombatSocket_RightHand;
	FGameplayTag CombatSocket_LeftHand;


	//////////////
	// MONTAGES //
	//////////////
	FGameplayTag Montage_Attack_1;
	FGameplayTag Montage_Attack_2;
	FGameplayTag Montage_Attack_3;
	FGameplayTag Montage_Attack_4;


private:

	static FAuraGameplayTags GameplayTags;
};
