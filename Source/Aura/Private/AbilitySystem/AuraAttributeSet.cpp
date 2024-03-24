// Copyright Deggo

#include "AbilitySystem/AuraAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameFramework/Character.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

UAuraAttributeSet::UAuraAttributeSet()
{
	InitHealth(10.f);
	InitMana(10.f);
	InitStagger(50.f);
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//////////////////////
	// VITAL ATTRIBUTES //
	//////////////////////
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Stagger, COND_None, REPNOTIFY_Always);

	/////////////////////
	// ROLE ATTRIBUTES //
	/////////////////////
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Tank, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Support, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Burst, COND_None, REPNOTIFY_Always);

	//////////////////////
	// STATS ATTRIBUTES //
	//////////////////////
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, HealthDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, HealthDamageReduction, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ManaCrystalCost, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ManaGeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, StaggerDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, StaggerDamageReduction, COND_None, REPNOTIFY_Always);

	//////////////////////
	// PERKS ATTRIBUTES //
	//////////////////////
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxStagger, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Aggro, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Cooldown, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Speed, COND_None, REPNOTIFY_Always);
}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
	if (Attribute == GetStaggerAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxStagger());
	}
}

void UAuraAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props)
{
	// Source = causer of the effect, Target = target of the effect (owner of this AS)

	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		const AController* SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}

		if (Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}


void UAuraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	SetEffectProperties(Data, Props);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}

	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}

	if (Data.EvaluatedData.Attribute == GetStaggerAttribute())
	{
		SetStagger(FMath::Clamp(GetStagger(), 0.f, GetMaxStagger()));
	}

	
}

//////////////////////
// VITAL ATTRIBUTES //
//////////////////////

void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth);
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana);
}

void UAuraAttributeSet::OnRep_Stagger(const FGameplayAttributeData& OldStagger) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Stagger, OldStagger);
}


/////////////////////
// ROLE ATTRIBUTES //
/////////////////////

void UAuraAttributeSet::OnRep_Tank(const FGameplayAttributeData& OldTank) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Tank, OldTank);
}

void UAuraAttributeSet::OnRep_Support(const FGameplayAttributeData& OldSupport) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Support, OldSupport);
}

void UAuraAttributeSet::OnRep_Burst(const FGameplayAttributeData& OldBurst) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Burst, OldBurst);
}


//////////////////////
// STATS ATTRIBUTES //
//////////////////////

void UAuraAttributeSet::OnRep_HealthDamage(const FGameplayAttributeData& OldHealthDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, HealthDamage, OldHealthDamage);
}

void UAuraAttributeSet::OnRep_HealthDamageReduction(const FGameplayAttributeData& OldHealthDamageReduction) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, HealthDamageReduction, OldHealthDamageReduction);
}

void UAuraAttributeSet::OnRep_ManaCrystalCost(const FGameplayAttributeData& OldManaCrystalCost) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ManaCrystalCost, OldManaCrystalCost);
}

void UAuraAttributeSet::OnRep_ManaGeneration(const FGameplayAttributeData& OldManaGeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ManaGeneration, OldManaGeneration);
}

void UAuraAttributeSet::OnRep_StaggerDamage(const FGameplayAttributeData& OldStaggerDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, StaggerDamage, OldStaggerDamage);
}

void UAuraAttributeSet::OnRep_StaggerDamageReduction(const FGameplayAttributeData& OldStaggerDamageReduction) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, StaggerDamageReduction, OldStaggerDamageReduction);
}

//////////////////////
// PERKS ATTRIBUTES //
//////////////////////

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, OldMaxMana);
}

void UAuraAttributeSet::OnRep_MaxStagger(const FGameplayAttributeData& OldMaxStagger) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxStagger, OldMaxStagger);
}

void UAuraAttributeSet::OnRep_Aggro(const FGameplayAttributeData& OldAggro) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Aggro, OldAggro);
}

void UAuraAttributeSet::OnRep_Cooldown(const FGameplayAttributeData& OldCooldown) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Cooldown, OldCooldown);
}

void UAuraAttributeSet::OnRep_Speed(const FGameplayAttributeData& OldSpeed) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Speed, OldSpeed);
}
