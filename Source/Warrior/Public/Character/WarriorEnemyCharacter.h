// BlueCode

#pragma once

#include "CoreMinimal.h"
#include "Character/WarriorBaseCharacter.h"
#include "WarriorEnemyCharacter.generated.h"

class UBoxComponent;
class UWidgetComponent;
class UEnemyUIComponent;
class UEnemyCombatComponent;
/**
 * 
 */
UCLASS()
class WARRIOR_API AWarriorEnemyCharacter : public AWarriorBaseCharacter
{
	GENERATED_BODY()

public:
	AWarriorEnemyCharacter();

	//~ Begin PawnCombat Interface.
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	//~ End PawnCombat Interface.
	
	//~ Begin PawnUI Interface.
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	virtual UEnemyUIComponent* GetEnemyUIComponent() const override;
	//~ End PawnUI Interface.
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Combat")
	UEnemyCombatComponent* EnemyCombatComponent;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Combat")
	UBoxComponent* LeftHandCollisionBox;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Combat")
	FName LeftHandCollisionBoxAttachBoneName;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Combat")
	UBoxComponent* RightHandCollisionBox;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Combat")
	FName RightHandCollisionBoxAttachBoneName;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "UI")
	UEnemyUIComponent* EnemyUIComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "UI")
	UWidgetComponent* EnemyHealthWidgetComponent;

	UFUNCTION()
	virtual void OnHandCollisionBoxStartOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface.

#if WITH_EDITOR
	//~ Begin UObject Interface.
	virtual void PostEditChangeProperty( struct FPropertyChangedEvent& PropertyChangedEvent) override;
	//~ End UObject Interface.
#endif
	
public:
	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const{return EnemyCombatComponent;};

	FORCEINLINE UBoxComponent* GetLeftHandCollisionBox() const {return LeftHandCollisionBox;};
	FORCEINLINE UBoxComponent* GetRightHandCollisionBox() const {return RightHandCollisionBox;};

private:
	void InitEnemyStartupData();
	
};
