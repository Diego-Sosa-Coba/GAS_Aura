// Copyright Deggo


#include "AbilitySystem/Data/BossClassInfo.h"

FBossClassDefaultInfo UBossClassInfo::GetClassDefaultInfo(EBossClass BossClass)
{
	return BossClassInfo.FindChecked(BossClass);
}
