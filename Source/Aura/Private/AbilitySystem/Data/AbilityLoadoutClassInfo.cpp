// Copyright Deggo


#include "AbilitySystem/Data/AbilityLoadoutClassInfo.h"
#include "AuraLogChannels.h"

FAbilityClassLoadoutDefaultInfo UAbilityLoadoutClassInfo::FindAbilityInfoForTag(const FGameplayTag& InputTag, bool bLogNotFound)
{
	for (const FAbilityClassLoadoutDefaultInfo& Info : AbilityLoadoutClassInformation)
	{
		if (Info.InputTag == InputTag)
		{
			return Info;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogAura, Error, TEXT("Can't find info for AbilityTag [%s] on AbilityInfo [%s]"), *InputTag.ToString(), *GetNameSafe(this));
	}

	return FAbilityClassLoadoutDefaultInfo();
}
