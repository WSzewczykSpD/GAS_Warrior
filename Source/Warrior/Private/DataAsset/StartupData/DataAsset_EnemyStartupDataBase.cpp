// BlueCode


#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "AbilitySystem/Ability/WarriorEnemyGameplayAbility.h"
#include "DataAsset/StartupData/DataAsset_EnemyStartupData.h"

void UDataAsset_EnemyStartupData::GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InASCToGive,
	int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);
	if(!EnemyCombatAbilities.IsEmpty())
	{
		for(const TSubclassOf<UWarriorEnemyGameplayAbility> AbilityClass: EnemyCombatAbilities)
		{
			if(!AbilityClass)continue;

			FGameplayAbilitySpec AbilitySpec(AbilityClass);
			AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
			AbilitySpec.Level = ApplyLevel;
			
			InASCToGive->GiveAbility(AbilitySpec);
		}
	}
}