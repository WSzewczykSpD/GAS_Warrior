// BlueCode

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interface/PawnCombatInterface.h"
#include "Interface/PawnUIInterface.h"
#include "WarriorBaseCharacter.generated.h"

class UMotionWarpingComponent;
class UDataAsset_StartupDataBase;
class UWarriorAttributeSet;
class UWarriorAbilitySystemComponent;

DECLARE_DELEGATE_OneParam(FOnTargetInteractedDelegate, AActor*)

UCLASS()
class WARRIOR_API AWarriorBaseCharacter : public ACharacter, public IAbilitySystemInterface, public IPawnCombatInterface, public IPawnUIInterface
{
	GENERATED_BODY()

public:
	AWarriorBaseCharacter();

	FOnTargetInteractedDelegate OnBodyHitTarget;
	FOnTargetInteractedDelegate OnBodyPulledFromTarget; 

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UWarriorAbilitySystemComponent> AbilityComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UWarriorAttributeSet> AttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData")
	TSoftObjectPtr<UDataAsset_StartupDataBase> CharacterStartupData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MotionWarping")
	TObjectPtr<UMotionWarpingComponent> MotionWarpingComponent;
	
	
public:
	//~ Begin AbilitySystem Interface.
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End AbilitySystem Interface.

	//~ Begin PawnCombat Interface.
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	//~ End PawnCombat Interface.

	//~ Begin PawnUI Interface.
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	//~ End PawnUI Interface.
	
	FORCEINLINE UWarriorAbilitySystemComponent* GetWarriorAbilitySystemComponent() const{return AbilityComponent;}
	FORCEINLINE UWarriorAttributeSet* GetWarriorAttributeSet() const{return AttributeSet;}
	
	UFUNCTION(BlueprintImplementableEvent)
	bool SetupBodyCombatCollisions();
	
protected:
	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface.
};
