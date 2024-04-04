// Copyright Deggo

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Interaction/CombatInterface.h"
#include "AuraGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor* TargetActor);

	// TODO: Link to ability map, currently the key used to execute this ability
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	FGameplayTag StartupInputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UFUNCTION(BlueprintPure)
	FTaggedMontage GetRandomTaggedMontageFromArray(const TArray<FTaggedMontage>& TaggedMontages) const;
	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float HealthDamage = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float HealthCost = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float ManaCrystalCost = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float ManaGeneration = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float StaggerDamage = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float StaggerCost = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float BarrierHealth = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float BarrierStagger = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float AbilityCooldown = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float AbilityCharges = 1;
};
