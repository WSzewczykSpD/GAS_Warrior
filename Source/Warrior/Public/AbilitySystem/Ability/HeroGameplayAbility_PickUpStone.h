// BlueCode

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/WarriorHeroGameplayAbility.h"
#include "HeroGameplayAbility_PickUpStone.generated.h"

class AWarriorStoneBase;
/**
 * 
 */
UCLASS()
class WARRIOR_API UHeroGameplayAbility_PickUpStone : public UWarriorHeroGameplayAbility
{
	GENERATED_BODY()

protected:
	
	//~ Begin UGameplayAbility Interface.
	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		bool bReplicateEndAbility,
		bool bWasCancelled) override;
	
	//~ End UGameplayAbility Interface.


	UFUNCTION(BlueprintCallable)
	void CollectStones();

	UFUNCTION(BlueprintCallable)
	void ConsumeStones(); 

private:
	UPROPERTY(EditDefaultsOnly)
	float BoxTraceDistance = 50.f;
	
	UPROPERTY(EditDefaultsOnly)
	FVector TraceBoxSize = FVector(100.f);
	
	UPROPERTY(EditDefaultsOnly)
	TArray<TEnumAsByte<EObjectTypeQuery>> StoneTraceChannel;

	UPROPERTY(EditDefaultsOnly)
	bool bDrawDebugTrace = false;

	UPROPERTY()
	TArray<AWarriorStoneBase*> CollectedStones;
	
};
