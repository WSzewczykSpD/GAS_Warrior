// BlueCode


#include "Item/Weapon/WarriorHeroWeapon.h"
#include "GameplayAbilitySpecHandle.h"


void AWarriorHeroWeapon::AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InsSpecHandles)
{
	GrantedAbilitySpecHandles = InsSpecHandles;
}

TArray<FGameplayAbilitySpecHandle> AWarriorHeroWeapon::GetGrantedAbilitySpecHandles() const
{
	return GrantedAbilitySpecHandles;
}
