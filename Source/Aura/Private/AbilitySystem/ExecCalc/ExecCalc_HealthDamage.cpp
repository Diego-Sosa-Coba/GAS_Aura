// Copyright Deggo


#include "AbilitySystem/ExecCalc/ExecCalc_HealthDamage.h"

#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAttributeSet.h"


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

	const AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	const AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

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
	//   150 -> 100 * -0.5 = -50 final dmg

	float BarrierHealth = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(HealthDamageStatics().BarrierHealthDef, EvaluationParameters, BarrierHealth);
	// Readjust the Health damage based off the barrier
	HealthDamage = HealthDamage * (1.f - (BarrierHealth / 100.f));

	const FGameplayModifierEvaluatedData EvaluatedData(UAuraAttributeSet::GetIncomingHealthDamageAttribute(), EGameplayModOp::Additive, HealthDamage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}