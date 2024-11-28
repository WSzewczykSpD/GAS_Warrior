// BlueCode

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/StartupData/DataAsset_StartupDataBase.h"
#include "DataAsset_EnemyStartupData.generated.h"

class UWarriorEnemyGameplayAbility;
/**
 * 
 */
UCLASS()
class WARRIOR_API UDataAsset_EnemyStartupData : public UDataAsset_StartupDataBase
{
	GENERATED_BODY()
public:
	virtual void GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);

private:
	UPROPERTY(EditDefaultsOnly, Category = "StartupData")
	TArray<TSubclassOf<UWarriorEnemyGameplayAbility>> EnemyCombatAbilities; 
};


