// Copyright Deggo


#include "AbilitySystem/ExecCalc/ExecCalc_StaggerDamage.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"


struct AuraStaggerDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(BarrierStagger);

	AuraStaggerDamageStatics()
	{
		// NOTE: Can choose "Source" or "Target" depending on what the calculation is doing
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, BarrierStagger, Target, false);
	}
};

static const AuraStaggerDamageStatics& StaggerDamageStatics()
{
	static AuraStaggerDamageStatics SDStatics;
	return SDStatics;
}

UExecCalc_StaggerDamage::UExecCalc_StaggerDamage()
{
	RelevantAttributesToCapture.Add(StaggerDamageStatics().BarrierStaggerDef);
}

void UExecCalc_StaggerDamage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
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

	float BarrierStagger = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(StaggerDamageStatics().BarrierStaggerDef, EvaluationParameters, BarrierStagger);
	BarrierStagger = FMath::Max<float>(0.f, BarrierStagger);
	++BarrierStagger;

	const FGameplayModifierEvaluatedData EvaluatedData(StaggerDamageStatics().BarrierStaggerProperty, EGameplayModOp::Additive, BarrierStagger);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}