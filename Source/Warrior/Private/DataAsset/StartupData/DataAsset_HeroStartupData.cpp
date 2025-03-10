// BlueCode


#include "DataAsset/StartupData/DataAsset_HeroStartupData.h"

#include "AbilitySystem/WarriorAbilitySystemComponent.h"
//#include "AbilitySystem/Ability/WarriorGameplayAbility.h"
#include "AbilitySystem/Ability/WarriorHeroGameplayAbility.h"
#include "WarriorTypes/WarriorStructTypes.h"


void UDataAsset_HeroStartupData::GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InASCToGive,
	int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

	for(const FWarriorHeroAbilitySet& AbilitySet : HeroStartupAbilitySet)
	{
		if(!AbilitySet.IsValid())continue;

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);
		
		InASCToGive->GiveAbility(AbilitySpec);
	}
}
