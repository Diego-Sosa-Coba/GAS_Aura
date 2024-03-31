// Copyright Deggo


#include "AbilitySystem/ExecCalc/ExecCalc_HealthDamage.h"

#include "AbilitySystemComponent.h"
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

	float BarrierHealth = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(HealthDamageStatics().BarrierHealthDef, EvaluationParameters, BarrierHealth);
	BarrierHealth = FMath::Max<float>(0.f, BarrierHealth);
	++BarrierHealth;

	const FGameplayModifierEvaluatedData EvaluatedData(HealthDamageStatics().BarrierHealthProperty, EGameplayModOp::Additive, BarrierHealth);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}