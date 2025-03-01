// BlueCode


#include "Component/Combat/HeroCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "WarriorGameplayTags.h"
#include "Character/WarriorHeroCharacter.h"
#include "Components/BoxComponent.h"
#include "Debug/WarriorDebugHelper.h"
#include "Item/Weapon/WarriorHeroWeapon.h"

AWarriorHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<AWarriorHeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}

AWarriorHeroWeapon* UHeroCombatComponent::GetHeroCurrentEquippedWeapon() const
{
	return Cast<AWarriorHeroWeapon>(GetCharacterCurrentEquippedWeapon());
}

float UHeroCombatComponent::GetHeroCurrentEquippedWeaponDamageAtLevel(float InLevel) const
{
	return GetHeroCurrentEquippedWeapon()->HeroWeaponData.WeaponBaseDamage.GetValueAtLevel(InLevel);
}

void UHeroCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if(OverlappedActors.Contains(HitActor))
	{
		return;
	}
	OverlappedActors.AddUnique(HitActor);

	FGameplayEventData Data;
	Data.Instigator = GetOwningPawn();
	Data.Target = HitActor;
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		WarriorGameplayTags::Shared_Event_MeleeHit,
		Data);

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),WarriorGameplayTags::Player_Event_HitPause,
		FGameplayEventData());
}

void UHeroCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),WarriorGameplayTags::Player_Event_HitPause,
		FGameplayEventData());
	
}

void UHeroCombatComponent::ToggleBodyCollisionBoxCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	AWarriorHeroCharacter* OwningHeroCharacter = GetOwningPawn<AWarriorHeroCharacter>();

	check(OwningHeroCharacter);

	UBoxComponent* RightFootCollisionBox = OwningHeroCharacter->GetRightFootCollisionBox();
	
	check(RightFootCollisionBox);

	switch(ToggleDamageType) {
	case EToggleDamageType::RightFoot:
		RightFootCollisionBox->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;
	default:
		break;
	}
	if(bShouldEnable == false)
	{
		OverlappedActors.Empty();
	}
}
