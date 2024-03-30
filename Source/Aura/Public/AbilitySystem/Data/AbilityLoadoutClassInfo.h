// Copyright Deggo

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AbilityClassRow.h"
#include "AbilityLoadoutClassInfo.generated.h"

class UGameplayEffect;

UENUM(BlueprintType)
enum class EAbilityInput : uint8
{
	Attack1_Ground,
	Attack2_Ground,
	Defend_Ground,
	Attack1_Ground_Enhance,
	Attack2_Ground_Enhance,
	Defend_Ground_Enhance,
	Attack1_Aerial,
	Attack2_Aerial,
	Defend_Aerial,
	Attack1_Aerial_Enhance,
	Attack2_Aerial_Enhance,
	Defend_Aerial_Enhance,
};

USTRUCT(BlueprintType)
struct FAbilityClassLoadoutDefaultInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Ability Loadout Defaults")
	TSubclassOf<UGameplayEffect> AbilityStatsAttributes;
};
/**
 * 
 */
UCLASS()
class AURA_API UAbilityLoadoutClassInfo : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, Category = "Ability Loadout Class Defaults")
	TMap<EAbilityInput, FAbilityClassLoadoutDefaultInfo> AbilityLoadoutClassInformation;

	FAbilityClassLoadoutDefaultInfo GetClassDefaultInfo(EAbilityInput AbilityInput);
};
