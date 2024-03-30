// Copyright Deggo

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AbilityClassInfo.generated.h"

class UGameplayEffect;


USTRUCT(BlueprintType)
struct FAbilityClass
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Ability Defaults")
	TSubclassOf<UGameplayEffect> StatsAttributes;

	UPROPERTY(EditDefaultsOnly, Category = "Ability Defaults")
	FGameplayTag InputTag = FGameplayTag();
};

/**
 * 
 */
UCLASS()
class AURA_API UAbilityClassInfo : public UDataAsset
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Ability Class Defaults")
	FAbilityClass AbilityClassInformation;

	FAbilityClass GetClassDefaultInfo();
	
};
