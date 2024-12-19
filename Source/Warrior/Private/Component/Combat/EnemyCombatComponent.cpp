// BlueCode


#include "Component/Combat/EnemyCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "WarriorGameplayTags.h"
#include "Debug/WarriorDebugHelper.h"

void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if(OverlappedActors.Contains(HitActor))
	{
		return;
	}

	OverlappedActors.AddUnique(HitActor);

	//TODO implement block check
	bool bISValidBlock = false;
	
	const bool bIsPlayerBlocking = false;
	const bool bIsMyAttackUnblockable = false;

	if(bIsPlayerBlocking && bIsMyAttackUnblockable)
	{
		//TODO: check if block is valid
	}

	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitActor;

	if(bISValidBlock)
	{
		//TODO: Handle succesfull block
	}else
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			GetOwningPawn(),
			WarriorGameplayTags::Shared_Event_MeleeHit,
			EventData);
	}
}
