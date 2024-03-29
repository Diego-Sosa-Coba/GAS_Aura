// Copyright Deggo

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AbilityClassInfo.generated.h"

class UGameplayEffect;

USTRUCT(BlueprintType)
struct FWeaponClassDefaultInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Defaults")
	TSubclassOf<UGameplayEffect> StatsAttributes;
};
/**
 * 
 */
UCLASS()
class AURA_API UAbilityClassInfo : public UDataAsset
{
	GENERATED_BODY()
	
};
