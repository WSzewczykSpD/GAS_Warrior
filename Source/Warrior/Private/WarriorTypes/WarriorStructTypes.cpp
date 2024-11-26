// BlueCode


#include "WarriorTypes/WarriorStructTypes.h"

#include "AbilitySystem/Ability/WarriorHeroGameplayAbility.h"

bool FWarriorHeroAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}
