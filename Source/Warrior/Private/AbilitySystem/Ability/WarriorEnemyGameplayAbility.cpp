// BlueCode


#include "AbilitySystem/Ability/WarriorEnemyGameplayAbility.h"

#include "WarriorGameplayTags.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "Character/WarriorEnemyCharacter.h"

AWarriorEnemyCharacter* UWarriorEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
	if(!CachedWarriorEnemyCharacter.IsValid())
	{
		CachedWarriorEnemyCharacter = Cast<AWarriorEnemyCharacter>(CurrentActorInfo->AvatarActor);
	}
	return CachedWarriorEnemyCharacter.IsValid()? CachedWarriorEnemyCharacter.Get() : nullptr;
}

UEnemyCombatComponent* UWarriorEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
	return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}

FGameplayEffectSpecHandle UWarriorEnemyGameplayAbility::MakeEnemyDamageEffectSpecHandle(
	TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat InDamageScalableFloat)
{
	check(EffectClass);
	
	FGameplayEffectContextHandle EffectContext = GetWarriorAbilitySystemComponentFromActorInfo()->MakeEffectContext();//GetWarriorAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	EffectContext.SetAbility(this);
	EffectContext.AddSourceObject(GetAvatarActorFromActorInfo());
	EffectContext.AddInstigator(GetAvatarActorFromActorInfo(),GetAvatarActorFromActorInfo());

	FGameplayEffectSpecHandle EffectSpecHandle =
		GetWarriorAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
			EffectClass,
			GetAbilityLevel(),
			EffectContext
		);

	EffectSpecHandle.Data->SetSetByCallerMagnitude(
		WarriorGameplayTags::Shared_SetByCaller_BaseDamage,
		InDamageScalableFloat.GetValueAtLevel(GetAbilityLevel())
		);
	
	return EffectSpecHandle;
}
