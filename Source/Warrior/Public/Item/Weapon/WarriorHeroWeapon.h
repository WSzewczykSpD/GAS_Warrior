// BlueCode

#pragma once

#include "CoreMinimal.h"
#include "Item/Weapon/WarriorWeaponBase.h"
#include "WarriorTypes/WarriorStructTypes.h"
#include "WarriorHeroWeapon.generated.h"

/**
 * 
 */
UCLASS()
class WARRIOR_API AWarriorHeroWeapon : public AWarriorWeaponBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly,	BlueprintReadOnly, Category = "WeaponData")
	FWarriorHeroWeaponData HeroWeaponData; 
};
