// Copyright Deggo


#include "AbilitySystem/Data/SpiritClassInfo.h"

FSpiritClassDefaultInfo USpiritClassInfo::GetClassDefaultInfo(ESpiritClass SpiritClass)
{
    return SpiritClassInformation.FindChecked(SpiritClass);
}
