// BlueCode

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "DataAsset/StartupData/DataAsset_StartupDataBase.h"
#include "DataAsset_HeroStartupData.generated.h"


USTRUCT(BlueprintType)
struct FWarriorHeroAbilitySet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UWarriorGameplayAbility> AbilityToGrant;

	bool IsValid() const;
};

/**
 * 
 */
UCLASS()
class WARRIOR_API UDataAsset_HeroStartupData : public UDataAsset_StartupDataBase
{
	GENERATED_BODY()
public:
	virtual void GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);

private:
	UPROPERTY(EditDefaultsOnly, Category = "StartupData", meta = (TitleProperty = "InputTag"))
	TArray<FWarriorHeroAbilitySet> HeroStartupAbilitySet;
	
	
};
