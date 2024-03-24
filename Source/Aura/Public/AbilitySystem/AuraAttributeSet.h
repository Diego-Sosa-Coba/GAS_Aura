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

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthDamage, Category = "Secondary Attributes")
	FGameplayAttributeData HealthDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, HealthDamage);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthDamageReduction, Category = "Secondary Attributes")
	FGameplayAttributeData HealthDamageReduction;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, HealthDamageReduction);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaCrystalCost, Category = "Secondary Attributes")
	FGameplayAttributeData ManaCrystalCost;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ManaCrystalCost);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaGeneration, Category = "Secondary Attributes")
	FGameplayAttributeData ManaGeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ManaGeneration);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_StaggerDamage, Category = "Secondary Attributes")
	FGameplayAttributeData StaggerDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, StaggerDamage);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_StaggerDamageReduction, Category = "Secondary Attributes")
	FGameplayAttributeData StaggerDamageReduction;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, StaggerDamageReduction);

	//////////////////////
	// PERKS ATTRIBUTES //
	//////////////////////

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Secondary Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Secondary Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxStagger, Category = "Secondary Attributes")
	FGameplayAttributeData MaxStagger;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxStagger);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Aggro, Category = "Secondary Attributes")
	FGameplayAttributeData Aggro;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Aggro);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Cooldown, Category = "Secondary Attributes")
	FGameplayAttributeData Cooldown;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Cooldown);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Speed, Category = "Secondary Attributes")
	FGameplayAttributeData Speed;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Speed);

	

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
	void OnRep_HealthDamageReduction(const FGameplayAttributeData& OldHealthDamageReduction) const;

	UFUNCTION()
	void OnRep_ManaCrystalCost(const FGameplayAttributeData& OldManaCrystalCost) const;

	UFUNCTION()
	void OnRep_ManaGeneration(const FGameplayAttributeData& OldManaGeneration) const;

	UFUNCTION()
	void OnRep_StaggerDamage(const FGameplayAttributeData& OldStaggerDamage) const;

	UFUNCTION()
	void OnRep_StaggerDamageReduction(const FGameplayAttributeData& OldStaggerDamageReduction) const;

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
	void OnRep_Aggro(const FGameplayAttributeData& OldAggro) const;

	UFUNCTION()
	void OnRep_Cooldown(const FGameplayAttributeData& OldCooldown) const;

	UFUNCTION()
	void OnRep_Speed(const FGameplayAttributeData& OldSpeed) const;




private:

	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props);
};
