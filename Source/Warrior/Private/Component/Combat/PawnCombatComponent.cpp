// BlueCode


#include "Component/Combat/PawnCombatComponent.h"

#include "Components/BoxComponent.h"
#include "Item/Weapon/WarriorWeaponBase.h"

void UPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister,
                                                 AWarriorWeaponBase* InWeaponToRegister, bool RegisterAsEquippedWeapon)
{
	checkf(!CharacterCarriedWeaponMap.Contains(InWeaponTagToRegister), TEXT("A named %s has already been added "));
	check(InWeaponToRegister);

	CharacterCarriedWeaponMap.Emplace(InWeaponTagToRegister,InWeaponToRegister);

	InWeaponToRegister->OnWeaponHitTarget.BindUObject(this,&ThisClass::OnHitTargetActor);
	InWeaponToRegister->OnWeaponPulledFromTarget.BindUObject(this, &ThisClass::OnWeaponPulledFromTargetActor);

	if(RegisterAsEquippedWeapon)
	{
		CurrentEquippedWeaponTag = InWeaponTagToRegister;
	}
	
}

void UPawnCombatComponent::RegisterLethalBodyPart(FGameplayTag InWeaponTagToRegister, AWarriorWeaponBase* WeaponToRegister)
{
}

AWarriorWeaponBase* UPawnCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	if(CharacterCarriedWeaponMap.Contains(InWeaponTagToGet))
	{
		if(AWarriorWeaponBase* const* FoundWeapon = CharacterCarriedWeaponMap.Find(InWeaponTagToGet))
		{
			return *FoundWeapon;
		}
	}
	return nullptr;
}

 AWarriorWeaponBase* UPawnCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
	if((!CurrentEquippedWeaponTag.IsValid()))
	{
		return nullptr;	
	}
	return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);	
}

void UPawnCombatComponent::ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	if(ToggleDamageType == EToggleDamageType::CurrentEquippedWeapon)
	{
		ToggleEquippedWeaponCollision(bShouldEnable);
	}
	else
	{
		ToggleBodyCollisionBoxCollision(bShouldEnable,ToggleDamageType);
	}
}

void UPawnCombatComponent::AddBodyCollisionComponent(EToggleDamageType DamageType, UBoxComponent* BoxComponent)
{
	BodyDamageCollisionComponents.Add(DamageType,BoxComponent);
}

void UPawnCombatComponent::OnHitTargetActor(AActor* HitActor)
{
}

void UPawnCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
}

void UPawnCombatComponent::ToggleEquippedWeaponCollision(bool bShouldEnable)
{
	AWarriorWeaponBase* WeaponToToggle = GetCharacterCurrentEquippedWeapon();
	
	check(WeaponToToggle);
	
	if(bShouldEnable)
	{
		WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}else
	{
		WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		OverlappedActors.Empty();
	}
	
}

void UPawnCombatComponent::ToggleBodyCollisionBoxCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	if(UBoxComponent* BodyCollisionBoxToToggle = BodyDamageCollisionComponents.FindOrAdd(EToggleDamageType::RightFoot))
	{
		if(bShouldEnable)
		{
			BodyCollisionBoxToToggle->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		}else
		{
			BodyCollisionBoxToToggle->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			OverlappedActors.Empty();
		}
	}
}
