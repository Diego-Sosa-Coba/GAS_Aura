// Copyright Deggo


#include "AbilitySystem/Data/AbilityLoadoutClassInfo.h"

FAbilityClassLoadoutDefaultInfo UAbilityLoadoutClassInfo::GetClassDefaultInfo(EAbilityInput AbilityInput)
{
    return AbilityLoadoutClassInformation.FindChecked(AbilityInput);
}
