// BlueCode

#pragma once

#include "CoreMinimal.h"
#include "Character/WarriorBaseCharacter.h"
#include "WarriorHeroCharacter.generated.h"

class UBoxComponent;
class UHeroUIComponent;
struct FGameplayTag;
class UHeroCombatComponent;
struct FInputActionValue;
class UDataAsset_InputConfig;
class UCameraComponent;
class USpringArmComponent;


UCLASS()
class WARRIOR_API AWarriorHeroCharacter : public AWarriorBaseCharacter
{
	GENERATED_BODY()

public:
	AWarriorHeroCharacter();
	
	//~ Begin PawnCombat Interface.
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	//~ End PawnCombat Interface.

	//~ Begin PawnUI Interface.
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	virtual UHeroUIComponent* GetHeroUIComponent() const override;
	//~ End PawnUI Interface.
	
protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
#if WITH_EDITOR
	//~ Begin UObject Interface.
	virtual void PostEditChangeProperty( struct FPropertyChangedEvent& PropertyChangedEvent) override;
	//~ End UObject Interface.
#endif

	UFUNCTION(BlueprintCallable, Category = "Camera")
	void SetDefaultCameraViewOnStartup(bool EnableStandardView);

	UFUNCTION(BlueprintCallable, Category = "Camera")
	void ToggleCameraView(bool EnableStandardView);

	UFUNCTION()
	virtual void OnFootCollisionBoxStartOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	//TODO: Create SetEnabledCameraOnStartup func and ToggleCameraView
	
	UPROPERTY(EditAnywhere, Category = "Camera")
	bool bAlternativeCamera = false;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Combat")
	UBoxComponent* RightFootCollisionBox;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Combat")
	FName RightFootCollisionBoxAttachBoneName;

private:
#pragma region Components

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* AltCameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* AltFollowCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UHeroCombatComponent* HeroCombatComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UHeroUIComponent* HeroUIComponent;
	
#pragma endregion

#pragma region Inputs
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	UDataAsset_InputConfig* InputConfigDataAsset;

	UPROPERTY()
	FVector2D SwitchDirection = FVector2D::ZeroVector;
	
	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);

	void Input_SwitchTargetTriggered(const FInputActionValue& InputActionValue);
	void Input_SwitchTargetCompleted(const FInputActionValue& InputActionValue);

	void Input_PickUpStoneStarted();

	void Input_AbilityInputPressed(FGameplayTag InInputTag);
	void Input_AbilityInputReleased(FGameplayTag InInputTag);
	
#pragma endregion 

public:
	FORCEINLINE UHeroCombatComponent* GetCombatComponent() const {return HeroCombatComponent;}
	FORCEINLINE UBoxComponent* GetRightFootCollisionBox() const {return RightFootCollisionBox;};
	
};
