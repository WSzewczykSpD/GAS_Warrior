// BlueCode

#pragma once

#include "CoreMinimal.h"
#include "AnimInstance/WarriorCharacterAnimInstance.h"
#include "WarriorHeroAnimInstance.generated.h"

class AWarriorHeroCharacter;
/**
 * 
 */
UCLASS()
class WARRIOR_API UWarriorHeroAnimInstance : public UWarriorCharacterAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly,Category = "AnimData|References")
	TObjectPtr<AWarriorHeroCharacter> OwningHeroCharacter;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly,Category = "AnimData|LocomotionData")
	bool bShouldEnterRelaxedState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category = "AnimData|LocomotionData")
	float EnterRelaxedStateThreshold = 5.f;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly,Category = "AnimData|LocomotionData")
	float IdleElapsedTime;
};