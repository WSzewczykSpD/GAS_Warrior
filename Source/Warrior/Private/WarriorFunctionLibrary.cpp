// BlueCode


#include "WarriorFunctionLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "AbilitySystem/Ability/WarriorGameplayAbility.h"

UWarriorAbilitySystemComponent* UWarriorFunctionLibrary::NativeGetWarriorASCFromActor(AActor* InActor)
{
	check(InActor);
	
	return CastChecked<UWarriorAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));

}

void UWarriorFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, const FGameplayTag TagToAdd)
{
	//InActor->
	UWarriorAbilitySystemComponent* ASC = NativeGetWarriorASCFromActor(InActor);
	if(!ASC->HasMatchingGameplayTag(TagToAdd))
	{
		ASC->AddLooseGameplayTag(TagToAdd);
	}
}

void UWarriorFunctionLibrary::RemoveGameplayTagToActorIfFound(AActor* InActor, const FGameplayTag TagToRemove)
{
	UWarriorAbilitySystemComponent* ASC = NativeGetWarriorASCFromActor(InActor);
	if(ASC->HasMatchingGameplayTag(TagToRemove))
	{
		ASC->RemoveLooseGameplayTag(TagToRemove);
	}
	
}

bool UWarriorFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, const FGameplayTag TagToCheck)
{
	UWarriorAbilitySystemComponent* ASC = NativeGetWarriorASCFromActor(InActor);
	return ASC->HasMatchingGameplayTag(TagToCheck);
}

void UWarriorFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, const FGameplayTag TagToCheck, EWarriorConfirmType& OutConfirmType)
{
	OutConfirmType = NativeDoesActorHaveTag(InActor,TagToCheck) ? EWarriorConfirmType::Yes : EWarriorConfirmType::No;
	
}
