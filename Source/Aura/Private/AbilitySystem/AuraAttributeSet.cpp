// Copyright Deggo

#include "AbilitySystem/AuraAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameFramework/Character.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerController.h"

UAuraAttributeSet::UAuraAttributeSet()
{
	const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();

	/////////////////////
	// ROLE ATTRIBUTES //
	/////////////////////
	TagsToAttributes.Add(GameplayTags.Attributes_Role_Tank, GetTankAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Role_Support, GetSupportAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Role_Burst, GetBurstAttribute);


	//////////////////////
	// STATS ATTRIBUTES //
	//////////////////////
	TagsToAttributes.Add(GameplayTags.Attributes_Stats_HealthDamage, GetHealthDamageAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Stats_HealthCost, GetHealthCostAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Stats_ManaCrystalCost, GetManaCrystalCostAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Stats_ManaGeneration, GetManaGenerationAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Stats_StaggerDamage, GetStaggerDamageAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Stats_StaggerCost, GetStaggerCostAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Stats_BarrierHealth, GetBarrierHealthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Stats_BarrierStagger, GetBarrierStaggerAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Stats_AbilityCooldown, GetAbilityCooldownAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Stats_AbilityCharges, GetAbilityChargesAttribute);

	//////////////////////
	// PERKS ATTRIBUTES //
	//////////////////////
	TagsToAttributes.Add(GameplayTags.Attributes_Perks_MaxHealth, GetMaxHealthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Perks_MaxMana, GetMaxManaAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Perks_MaxStagger, GetMaxStaggerAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Perks_ThreatGeneration, GetThreatGenerationAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Perks_CooldownReduction, GetCooldownReductionAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Perks_EvasionSpeed, GetEvasionSpeedAttribute);
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
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, HealthCost, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ManaCrystalCost, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ManaGeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, StaggerDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, StaggerCost, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, BarrierHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, BarrierStagger, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, AbilityCooldown, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, AbilityCharges, COND_None, REPNOTIFY_Always);

	//////////////////////
	// PERKS ATTRIBUTES //
	//////////////////////
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxStagger, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ThreatGeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CooldownReduction, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, EvasionSpeed, COND_None, REPNOTIFY_Always);
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
		UE_LOG(LogTemp, Warning, TEXT("Changed Health on %s, Health: %f"), *Props.TargetAvatarActor->GetName(), GetHealth());
	}

	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}

	if (Data.EvaluatedData.Attribute == GetStaggerAttribute())
	{
		SetStagger(FMath::Clamp(GetStagger(), 0.f, GetMaxStagger()));
	}

	if (Data.EvaluatedData.Attribute == GetIncomingHealthDamageAttribute())
	{
		const float LocalIncomingDamage = GetIncomingHealthDamage();
		SetIncomingHealthDamage(0.f);
		const float NewHealth = GetHealth() - LocalIncomingDamage;
		SetHealth(FMath::Clamp(NewHealth, 0.f, GetMaxHealth()));

		const bool bFatal = NewHealth <= 0.f;

		if (bFatal)
		{
			ICombatInterface* CombatInterface = Cast<ICombatInterface>(Props.TargetAvatarActor);
			if (CombatInterface)
			{
				CombatInterface->Die();
			}
		}
		else
		{
			FGameplayTagContainer TagContainer;
			TagContainer.AddTag(FAuraGameplayTags::Get().Effects_HitReact);
			Props.TargetASC->TryActivateAbilitiesByTag(TagContainer);
		}
		const bool bHealthHeal = UAuraAbilitySystemLibrary::IsHealthHeal(Props.EffectContextHandle);
		const bool bStaggerHeal = UAuraAbilitySystemLibrary::IsStaggerHeal(Props.EffectContextHandle);
		const bool bBlockedHit = UAuraAbilitySystemLibrary::IsBlockedHit(Props.EffectContextHandle);
		const bool bParriedHit = UAuraAbilitySystemLibrary::IsParriedHit(Props.EffectContextHandle);
		ShowFloatingText(Props, LocalIncomingDamage, bHealthHeal, bStaggerHeal, bBlockedHit, bParriedHit);
	}
	
	if (Data.EvaluatedData.Attribute == GetIncomingStaggerDamageAttribute())
	{
		const float LocalIncomingDamage = GetIncomingStaggerDamage();
		SetIncomingStaggerDamage(0.f);
		const float NewStagger = GetStagger() - LocalIncomingDamage;
		SetStagger(FMath::Clamp(NewStagger, 0.f, GetMaxStagger()));

		const bool bFatal = NewStagger <= 0.f;

		// TODO: instead of Die(), implement and apply Stun()
		if (bFatal)
		{
			ICombatInterface* CombatInterface = Cast<ICombatInterface>(Props.TargetAvatarActor);
			if (CombatInterface)
			{
				CombatInterface->Die();
			}
		}
		else
		{
			FGameplayTagContainer TagContainer;
			TagContainer.AddTag(FAuraGameplayTags::Get().Effects_HitReact);
			Props.TargetASC->TryActivateAbilitiesByTag(TagContainer);
		}
		const bool bHealthHeal = UAuraAbilitySystemLibrary::IsHealthHeal(Props.EffectContextHandle);
		const bool bStaggerHeal = UAuraAbilitySystemLibrary::IsStaggerHeal(Props.EffectContextHandle);
		const bool bBlockedHit = UAuraAbilitySystemLibrary::IsBlockedHit(Props.EffectContextHandle);
		const bool bParriedHit = UAuraAbilitySystemLibrary::IsParriedHit(Props.EffectContextHandle);
		ShowFloatingText(Props, LocalIncomingDamage, bHealthHeal, bStaggerHeal, bBlockedHit, bParriedHit);
	}


	// TODO: Apply the Perks calculations here because of bug
	// that only applies during editing, not in packaged product

	
}

void UAuraAttributeSet::ShowFloatingText(const FEffectProperties& Props, float Damage, bool bHealthHeal, bool bStaggerHeal, bool bBlockedHit, bool bParriedHit) const
{
	if (Props.SourceCharacter != Props.TargetCharacter)
	{
		if (AAuraPlayerController* PC = Cast<AAuraPlayerController>(UGameplayStatics::GetPlayerController(Props.SourceCharacter, 0)))
		{
			PC->ShowDamageNumber(Damage, Props.TargetCharacter);
		}
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

void UAuraAttributeSet::OnRep_HealthCost(const FGameplayAttributeData& OldHealthCost) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, HealthCost, OldHealthCost);
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

void UAuraAttributeSet::OnRep_StaggerCost(const FGameplayAttributeData& OldStaggerCost) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, StaggerCost, OldStaggerCost);
}

void UAuraAttributeSet::OnRep_BarrierHealth(const FGameplayAttributeData& OldBarrierHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, BarrierHealth, OldBarrierHealth);
}

void UAuraAttributeSet::OnRep_BarrierStagger(const FGameplayAttributeData& OldBarrierStagger) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, BarrierStagger, OldBarrierStagger);
}

void UAuraAttributeSet::OnRep_AbilityCooldown(const FGameplayAttributeData& OldAbilityCooldown) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, AbilityCooldown, OldAbilityCooldown);
}

void UAuraAttributeSet::OnRep_AbilityCharges(const FGameplayAttributeData& OldAbilityCharges) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, AbilityCharges, OldAbilityCharges);
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

void UAuraAttributeSet::OnRep_ThreatGeneration(const FGameplayAttributeData& OldThreatGeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ThreatGeneration, OldThreatGeneration);
}

void UAuraAttributeSet::OnRep_CooldownReduction(const FGameplayAttributeData& OldCooldownReduction) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CooldownReduction, OldCooldownReduction);
}

void UAuraAttributeSet::OnRep_EvasionSpeed(const FGameplayAttributeData& OldEvasionSpeed) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, EvasionSpeed, OldEvasionSpeed);
}
