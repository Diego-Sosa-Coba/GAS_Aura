// Copyright Deggo


#include "AbilitySystem/ModMagCalc/MMC_MaxMana.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	TankDef.AttributeToCapture = UAuraAttributeSet::GetTankAttribute();
	TankDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	TankDef.bSnapshot = false;

	SupportDef.AttributeToCapture = UAuraAttributeSet::GetSupportAttribute();
	SupportDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	SupportDef.bSnapshot = false;

	BurstDef.AttributeToCapture = UAuraAttributeSet::GetBurstAttribute();
	BurstDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	BurstDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(TankDef);
	RelevantAttributesToCapture.Add(SupportDef);
	RelevantAttributesToCapture.Add(BurstDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Tank = 0.f;
	GetCapturedAttributeMagnitude(TankDef, Spec, EvaluationParameters, Tank);
	float Support = 0.f;
	GetCapturedAttributeMagnitude(SupportDef, Spec, EvaluationParameters, Support);
	float Burst = 0.f;
	GetCapturedAttributeMagnitude(BurstDef, Spec, EvaluationParameters, Burst);

	// TODO: Unused, but might want to have player level/rank in the future so keeping example
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	// For the max vital stats, the 3 Roles will either have High, Medium or Low proficiency
	// corresponding to a scaling factor of 1.0, 0.5 and 0.1, respectively.
	// Refer to the Data Table.xlsx -> Attributes for the exact details.
	const float BaseManaScale = 50.f;
	return BaseManaScale + (BaseManaScale * Tank * 0.1f) + (BaseManaScale * Support * 1.0f) + (BaseManaScale * Burst * 0.5f);
}

