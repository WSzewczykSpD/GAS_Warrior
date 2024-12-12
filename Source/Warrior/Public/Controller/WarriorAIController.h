// BlueCode

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "WarriorAIController.generated.h"

struct FAIStimulus;
/**
 * 
 */
class UAISenseConfig_Sight;
UCLASS()
class WARRIOR_API AWarriorAIController : public AAIController
{
	GENERATED_BODY()
	AWarriorAIController(const FObjectInitializer& ObjectInitializer);

	//~ Begin GenericTeamAgent Interface
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const;
	//~ End GenericTeamAgent Interface

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAIPerceptionComponent* EnemyPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAISenseConfig_Sight* AISenseConfig_Sight;

	UFUNCTION()
	virtual void OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	
};
