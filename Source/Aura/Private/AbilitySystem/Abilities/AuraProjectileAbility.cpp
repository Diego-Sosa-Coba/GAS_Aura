// Copyright Deggo



#include "AbilitySystem/Abilities/AuraProjectileAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"
#include "Aura/Public/AuraGameplayTags.h"

void UAuraProjectileAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

}

void UAuraProjectileAbility::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();

	if (!bIsServer) return;

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (CombatInterface)
	{
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
		FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();

		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(Rotation.Quaternion());

		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());

		// NOTE: This exposes the EffectContext so we can do things with it (like get bools for Crits)
		FGameplayEffectContextHandle EffectContextHandle = SourceASC->MakeEffectContext();
		EffectContextHandle.SetAbility(this);
		EffectContextHandle.AddSourceObject(Projectile);
		TArray<TWeakObjectPtr<AActor>> Actors;
		Actors.Add(Projectile);
		EffectContextHandle.AddActors(Actors);
		FHitResult HitResult;
		HitResult.Location = ProjectileTargetLocation;
		EffectContextHandle.AddHitResult(HitResult);

		const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), EffectContextHandle);

		const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Attributes_Stats_HealthDamage, HealthDamage);
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Attributes_Stats_StaggerDamage, StaggerDamage);
		// TODO: Add the rest of the relevant attributes here?
		Projectile->DamageEffectSpecHandle = SpecHandle;

		Projectile->FinishSpawning(SpawnTransform);
	}
}