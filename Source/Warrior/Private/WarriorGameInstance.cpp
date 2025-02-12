// BlueCode


#include "WarriorGameInstance.h"

TSoftObjectPtr<UWorld> UWarriorGameInstance::GetGameLevelByTag(FGameplayTag InTag) const
{
	for(const FWarriorGameLevelSet& LevelSet : GameLevelSets)
	{
		if(!LevelSet.IsValid()) continue;

		if(LevelSet.LevelTag == InTag)
		{
			return LevelSet.Level;
		}
	}
	
	return TSoftObjectPtr<UWorld>();
}
