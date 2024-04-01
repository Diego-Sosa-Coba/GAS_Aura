// Copyright Deggo

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AuraAttributeSet.generated.h"

/**
* This defines a set of helper functions for accessing and initializing attributes, to avoid having to manually write these functions.
* It would creates the following functions, for attribute Health
*
* static FGameplayAttribute UMyHealthSet::GetHealthAttribute();
*FORCEINLINE float UMyHealthSet::GetHealth() const;
*FORCEINLINE void UMyHealthSet::SetHealth(float NewVal);
*FORCEINLINE void UMyHealthSet::InitHealth(float NewVal);
*/

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()
	
	FEffectProperties() {}

	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;

	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;

	UPROPERTY()
	AController* SourceController = nullptr;

	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;

	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;

	UPROPERTY()
	AController* TargetController = nullptr;

	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};

// typedef is specific to the FGameplayAttribute() signature, but TStaticFunPtr is generic to any signature chosen
//typedef TBaseStaticDelegateInstance<FGameplayAttribute(), FDefaultDelegateUserPolicy>::FFuncPtr FAttributeFuncPtr;
template<class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;

/**
 * 
 */
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UAuraAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;

	//////////////////////
	// VITAL ATTRIBUTES //
	//////////////////////

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Stagger, Category = "Vital Attributes")
	FGameplayAttributeData Stagger;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Stagger);

	/////////////////////
	// META ATTRIBUTES //
	/////////////////////

	// NOTE: These values are NOT replicated, only used for calculations

	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData IncomingHealthDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, IncomingHealthDamage);

	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData IncomingStaggerDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, IncomingStaggerDamage);


	/////////////////////
	// ROLE ATTRIBUTES //
	/////////////////////

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Tank, Category = "Role Attributes")
	FGameplayAttributeData Tank;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Tank);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Support, Category = "Role Attributes")
	FGameplayAttributeData Support;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Support);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Burst, Category = "Role Attributes")
	FGameplayAttributeData Burst;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Burst);


	//////////////////////
	// STATS ATTRIBUTES //
	//////////////////////

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthDamage, Category = "Stats Attributes")
	FGameplayAttributeData HealthDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, HealthDamage);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthCost, Category = "Stats Attributes")
	FGameplayAttributeData HealthCost;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, HealthCost);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaCrystalCost, Category = "Stats Attributes")
	FGameplayAttributeData ManaCrystalCost;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ManaCrystalCost);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaGeneration, Category = "Stats Attributes")
	FGameplayAttributeData ManaGeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ManaGeneration);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_StaggerDamage, Category = "Stats Attributes")
	FGameplayAttributeData StaggerDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, StaggerDamage);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_StaggerCost, Category = "Stats Attributes")
	FGameplayAttributeData StaggerCost;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, StaggerCost);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BarrierHealth, Category = "Stats Attributes")
	FGameplayAttributeData BarrierHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, BarrierHealth);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BarrierStagger, Category = "Stats Attributes")
	FGameplayAttributeData BarrierStagger;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, BarrierStagger);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AbilityCooldown, Category = "Stats Attributes")
	FGameplayAttributeData AbilityCooldown;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, AbilityCooldown);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AbilityCharges, Category = "Stats Attributes")
	FGameplayAttributeData AbilityCharges;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, AbilityCharges);

	//////////////////////
	// PERKS ATTRIBUTES //
	//////////////////////

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Perks Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Perks Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxStagger, Category = "Perks Attributes")
	FGameplayAttributeData MaxStagger;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxStagger);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ThreatGeneration, Category = "Perks Attributes")
	FGameplayAttributeData ThreatGeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ThreatGeneration);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CooldownReduction, Category = "Perks Attributes")
	FGameplayAttributeData CooldownReduction;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CooldownReduction);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_EvasionSpeed, Category = "Perks Attributes")
	FGameplayAttributeData EvasionSpeed;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, EvasionSpeed);

	

	//////////////////////
	// VITAL ATTRIBUTES //
	//////////////////////

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;

	UFUNCTION()
	void OnRep_Stagger(const FGameplayAttributeData& OldStagger) const;


	/////////////////////
	// ROLE ATTRIBUTES //
	/////////////////////

	UFUNCTION()
	void OnRep_Tank(const FGameplayAttributeData& OldTank) const;

	UFUNCTION()
	void OnRep_Support(const FGameplayAttributeData& OldSupport) const;

	UFUNCTION()
	void OnRep_Burst(const FGameplayAttributeData& OldBurst) const;

	//////////////////////
	// STATS ATTRIBUTES //
	//////////////////////

	UFUNCTION()
	void OnRep_HealthDamage(const FGameplayAttributeData& OldHealthDamage) const;

	UFUNCTION()
	void OnRep_HealthCost(const FGameplayAttributeData& OldHealthCost) const;

	UFUNCTION()
	void OnRep_ManaCrystalCost(const FGameplayAttributeData& OldManaCrystalCost) const;

	UFUNCTION()
	void OnRep_ManaGeneration(const FGameplayAttributeData& OldManaGeneration) const;

	UFUNCTION()
	void OnRep_StaggerDamage(const FGameplayAttributeData& OldStaggerDamage) const;

	UFUNCTION()
	void OnRep_StaggerCost(const FGameplayAttributeData& OldStaggerCost) const;

	UFUNCTION()
	void OnRep_BarrierHealth(const FGameplayAttributeData& OldBarrierHealth) const;

	UFUNCTION()
	void OnRep_BarrierStagger(const FGameplayAttributeData& OldBarrierStagger) const;

	UFUNCTION()
	void OnRep_AbilityCooldown(const FGameplayAttributeData& OldAbilityCooldown) const;

	UFUNCTION()
	void OnRep_AbilityCharges(const FGameplayAttributeData& OldAbilityCharges) const;

	//////////////////////
	// PERKS ATTRIBUTES //
	//////////////////////

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

	UFUNCTION()
	void OnRep_MaxStagger(const FGameplayAttributeData& OldMaxStagger) const;

	UFUNCTION()
	void OnRep_ThreatGeneration(const FGameplayAttributeData& OldThreatGeneration) const;

	UFUNCTION()
	void OnRep_CooldownReduction(const FGameplayAttributeData& OldCooldownReduction) const;

	UFUNCTION()
	void OnRep_EvasionSpeed(const FGameplayAttributeData& OldEvasionSpeed) const;




private:

	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props);
	void ShowFloatingText(const FEffectProperties& Props, float HealthDamageVal, float StaggerDamageVal, bool bHealthHeal, bool bStaggerHeal, bool bBlockedHit, bool bParriedHit) const;
};
