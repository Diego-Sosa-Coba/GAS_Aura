// Copyright Deggo


#include "AbilitySystem/ExecCalc/ExecCalc_StaggerDamage.h"

#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/BossClassInfo.h"
#include "Interaction/CombatInterface.h"


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
	float StaggerDamage = Spec.GetSetByCallerMagnitude(FAuraGameplayTags::Get().Attributes_Stats_StaggerDamage);

	// This barrier is the % damage reduction done to Stagger. This value behaves as follows
	//   - <0: increased damage taken
	//   - 0: damage is fully taken
	//   - 100: damage is entirely negated
	//   - >100: damage is healed by (BarrierStagger - 100)% of the value
	// NOTE: could go into the negatives to increase damage taken...
	// 
	// EXAMPLE:
	// Stagger = 100
	// Barrier =
	// -50 -> 100 * 1.5 = 150 final dmg
	//   20 -> 100 * .8 = 80 final dmg
	//   40 -> 100 * .6 = 80 final dmg
	//   100 -> 100 * .0 = 80 final dmg
	//   150 -> 100 * -0.5 = -50 final dmg

	float BarrierStagger = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(StaggerDamageStatics().BarrierStaggerDef, EvaluationParameters, BarrierStagger);
	// Readjust the Stagger damage based off the barrier
	StaggerDamage = StaggerDamage * (1.f - (BarrierStagger / 100.f));

	const FGameplayModifierEvaluatedData EvaluatedData(UAuraAttributeSet::GetIncomingStaggerDamageAttribute(), EGameplayModOp::Additive, StaggerDamage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}