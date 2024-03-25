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

	//////////////////////
	// PERKS ATTRIBUTES //
	//////////////////////
	FGameplayTag Attributes_Perks_MaxHealth;
	FGameplayTag Attributes_Perks_MaxMana;
	FGameplayTag Attributes_Perks_MaxStagger;
	FGameplayTag Attributes_Perks_ThreatGeneration;
	FGameplayTag Attributes_Perks_CooldownReduction;
	FGameplayTag Attributes_Perks_EvasionSpeed;

protected:

private:

	static FAuraGameplayTags GameplayTags;
};
