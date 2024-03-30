// Copyright Deggo

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "AbilityClassRow.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FAbilityClassRow: public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

public:

    FAbilityClassRow()
        : HealthDamage(0)
        , HealthCost(0)
    {}

    /** The 'Name' column is the same as the XP Level */

    /** XP to get to the given level from the previous level */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
    int32 HealthDamage;

    /** Extra HitPoints gained at this level */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
    int32 HealthCost;
};