// BlueCode


#include "Character/WarriorBaseCharacter.h"

#include "MotionWarpingComponent.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "AbilitySystem/WarriorAttributeSet.h"

AWarriorBaseCharacter::AWarriorBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->SetReceivesDecals(false);
	AbilityComponent = CreateDefaultSubobject<UWarriorAbilitySystemComponent>(TEXT("WarriorAbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UWarriorAttributeSet>(TEXT("WarriorAttributeSet"));
	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent")); 
}

UAbilitySystemComponent* AWarriorBaseCharacter::GetAbilitySystemComponent() const
{
	return GetWarriorAbilitySystemComponent(); 
}

UPawnCombatComponent* AWarriorBaseCharacter::GetPawnCombatComponent() const
{
	return nullptr;
}

UPawnUIComponent* AWarriorBaseCharacter::GetPawnUIComponent() const
{
	return nullptr;
}

void AWarriorBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if(AbilityComponent)
	{
		AbilityComponent->InitAbilityActorInfo(this,this);
	
		ensureMsgf(!CharacterStartupData.IsNull(),TEXT("Forgot to assign startup data for character %s"),*GetName());
	}

	SetupBodyCombatCollisions();
}


