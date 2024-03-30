// Copyright Deggo

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AbilityLoadoutClassInfo.h"
#include "SpiritClassInfo.generated.h"

class UGameplayEffect;

UENUM(BlueprintType)
enum class ESpiritClass : uint8
{
	Bird,
	Fox,
	Frog
};


USTRUCT(BlueprintType)
struct FSpiritClassDefaultInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Spirit Defaults")
	TSubclassOf<UGameplayEffect> RoleAttributes;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Defaults")
	UAbilityLoadoutClassInfo* AbilityLoadout;
};

/**
 * 
 */
UCLASS()
class AURA_API USpiritClassInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Spirit Class Defaults")
	TMap<ESpiritClass, FSpiritClassDefaultInfo> SpiritClassInformation;

	FSpiritClassDefaultInfo GetClassDefaultInfo(ESpiritClass SpiritClass);
	
};
