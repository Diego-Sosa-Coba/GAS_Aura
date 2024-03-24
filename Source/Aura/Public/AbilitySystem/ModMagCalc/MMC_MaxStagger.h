// Copyright Deggo

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_MaxStagger.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UMMC_MaxStagger : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	UMMC_MaxStagger();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:

	FGameplayEffectAttributeCaptureDefinition TankDef;
	FGameplayEffectAttributeCaptureDefinition SupportDef;
	FGameplayEffectAttributeCaptureDefinition BurstDef;
	
};
