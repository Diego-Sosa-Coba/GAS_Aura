// Copyright Deggo

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AbilityLoadoutClassInfo.generated.h"

class UGameplayEffect;

USTRUCT(BlueprintType)
struct FAbilityClassLoadoutDefaultInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag InputTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UTexture2D> Icon = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UMaterialInterface> BackgroundMaterial = nullptr;
};
/**
 * 
 */
UCLASS()
class AURA_API UAbilityLoadoutClassInfo : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, Category = "Ability Information")
	TArray<FAbilityClassLoadoutDefaultInfo> AbilityLoadoutClassInformation;

	FAbilityClassLoadoutDefaultInfo FindAbilityInfoForTag(const FGameplayTag& InputTag, bool bLogNotFound = false);
};
