// Copyright Deggo

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AuraGameModeBase.generated.h"

class UWeaponClassInfo;
class USpiritClassInfo;
class UBossClassInfo;
/**
 * 
 */
UCLASS()
class AURA_API AAuraGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Boss Class Defaults")
	TObjectPtr<UWeaponClassInfo> WeaponClassInfo;

	UPROPERTY(EditDefaultsOnly, Category = "Boss Class Defaults")
	TObjectPtr<USpiritClassInfo> SpiritClassInfo;

	UPROPERTY(EditDefaultsOnly, Category = "Boss Class Defaults")
	TObjectPtr<UBossClassInfo> BossClassInfo;
	
};
