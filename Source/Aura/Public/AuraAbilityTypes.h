// Copyright Deggo

#pragma once

#include "GameplayEffectTypes.h"
#include "AuraAbilityTypes.generated.h"

USTRUCT(BlueprintType)
struct FAuraGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

public:

	bool IsHealthHeal() const { return bIsHealthHeal; }
	bool IsStaggerHeal() const { return bIsStaggerHeal; }
	bool IsBlockedHit() const { return bIsBlockedHit; }
	bool IsParriedHit() const { return bIsParriedHit; }

	void SetIsHealthHeal(bool bInIsHealthHeal) { bIsHealthHeal = bInIsHealthHeal; }
	void SetIsStaggerHeal(bool bInIsStaggerHeal) { bIsStaggerHeal = bInIsStaggerHeal; }
	void SetIsBlockedHit(bool bInIsBlockedHit) { bIsBlockedHit = bInIsBlockedHit; }
	void SetIsParriedHit(bool bInIsParriedHit) { bIsParriedHit = bInIsParriedHit; }

	/** Returns the actual struct used for serialization, subclasses must override this! */
	virtual UScriptStruct* GetScriptStruct() const
	{
		return StaticStruct();
	}

	/** Creates a copy of this context, used to duplicate for later modifications */
	virtual FAuraGameplayEffectContext* Duplicate() const
	{
		FAuraGameplayEffectContext* NewContext = new FAuraGameplayEffectContext();
		*NewContext = *this;
		if (GetHitResult())
		{
			// Does a deep copy of the hit result
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}

	/** Custom serialization, subclasses must override this */
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);

protected:

	UPROPERTY()
	bool bIsHealthHeal = false;

	UPROPERTY()
	bool bIsStaggerHeal = false;

	UPROPERTY()
	bool bIsBlockedHit = false;

	UPROPERTY()
	bool bIsParriedHit = false;

};

template<>
struct TStructOpsTypeTraits<FAuraGameplayEffectContext> : public TStructOpsTypeTraitsBase2<FAuraGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true
	};
};