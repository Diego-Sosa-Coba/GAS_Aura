// Copyright Deggo

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AbilityLoadoutClassInfo.h"
#include "WeaponClassInfo.generated.h"

class UGameplayEffect;

UENUM(BlueprintType)
enum class EWeaponClass : uint8
{
	Sword,
	Bow,
	Crozier
};


USTRUCT(BlueprintType)
struct FWeaponClassDefaultInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Defaults")
	TSubclassOf<UGameplayEffect> RoleAttributes;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Defaults")
	UAbilityLoadoutClassInfo *AbilityLoadout;
};
/**
 * 
 */
UCLASS()
class AURA_API UWeaponClassInfo : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon Class Defaults")
	TMap<EWeaponClass, FWeaponClassDefaultInfo> WeaponClassInformation;

	FWeaponClassDefaultInfo GetClassDefaultInfo(EWeaponClass WeaponClass);
};
