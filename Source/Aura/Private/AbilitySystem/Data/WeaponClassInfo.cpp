// Copyright Deggo


#include "AbilitySystem/Data/WeaponClassInfo.h"

FWeaponClassDefaultInfo UWeaponClassInfo::GetClassDefaultInfo(EWeaponClass WeaponClass)
{
	return WeaponClassInformation.FindChecked(WeaponClass);
}
