// Copyright Deggo


#include "AbilitySystem/ExecCalc/ExecCalc_HealthDamage.h"

#include "AbilitySystemComponent.h"
#include "AuraAbilityTypes.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/BossClassInfo.h"
#include "Interaction/CombatInterface.h"


struct AuraHealthDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(BarrierHealth);

	AuraHealthDamageStatics()
	{
		// NOTE: Can choose "Source" or "Target" depending on what the calculation is doing
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, BarrierHealth, Target, false);
	}
};

static const AuraHealthDamageStatics& HealthDamageStatics()
{
	static AuraHealthDamageStatics HDStatics;
	return HDStatics;
}

UExecCalc_HealthDamage::UExecCalc_HealthDamage()
{
	RelevantAttributesToCapture.Add(HealthDamageStatics().BarrierHealthDef);
}

void UExecCalc_HealthDamage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;
	// Used to get character levels
	ICombatInterface* SourceCombatInterface = Cast<ICombatInterface>(SourceAvatar);
	ICombatInterface* TargetCombatInterface = Cast<ICombatInterface>(TargetAvatar);

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();


	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	// Get Damage Set by Caller Magnitude
	float HealthDamage = Spec.GetSetByCallerMagnitude(FAuraGameplayTags::Get().Attributes_Stats_HealthDamage);

	// This barrier is the % damage reduction done to Health. This value behaves as follows
	//   - <0: increased damage taken
	//   - 0: damage is fully taken
	//   - 100: damage is entirely negated
	//   - >100: damage is healed by (BarrierHealth - 100)% of the value
	// NOTE: could go into the negatives to increase damage taken...
	// 
	// EXAMPLE:
	// Health = 100
	// Barrier =
	// -50 -> 100 * 1.5 = 150 final dmg
	//   20 -> 100 * .8 = 80 final dmg
	//   40 -> 100 * .6 = 80 final dmg
	//   100 -> 100 * .0 = 80 final dmg
	//   150 -> 100 * -0.5 = -50 final 

	float BarrierHealth = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(HealthDamageStatics().BarrierHealthDef, EvaluationParameters, BarrierHealth);
	// Readjust the Health damage based off the barrier, but only when health damage is positive
	if (HealthDamage > 0.f)
	{
		HealthDamage = HealthDamage * (1.f - (BarrierHealth / 100.f));
	}
	bool bHealthHeal = HealthDamage < 0.f;
	// if very close to 0.f, round to 0.f and consider it a blocked hit
	bool bBlockedHit = FMath::IsNearlyEqual(HealthDamage, 0.f, 0.1f);
	HealthDamage = bBlockedHit ? 0.f : HealthDamage;

	// Apply the damage
	const FGameplayModifierEvaluatedData EvaluatedData(UAuraAttributeSet::GetIncomingHealthDamageAttribute(), EGameplayModOp::Additive, HealthDamage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);

	// Save out all the text modifiers to the EffectContextHandle
	FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();
	UAuraAbilitySystemLibrary::SetIsHealthHeal(EffectContextHandle, bHealthHeal);
	UAuraAbilitySystemLibrary::SetIsStaggerHeal(EffectContextHandle, false);
	UAuraAbilitySystemLibrary::SetIsBlockedHit(EffectContextHandle, bBlockedHit);
	UAuraAbilitySystemLibrary::SetIsParriedHit(EffectContextHandle, false);  // TODO: implement
}