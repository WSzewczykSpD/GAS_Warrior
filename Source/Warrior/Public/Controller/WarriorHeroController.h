// BlueCode

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/PlayerController.h"
#include "WarriorHeroController.generated.h"

/**
 * 
 */
UCLASS()
class WARRIOR_API AWarriorHeroController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

	AWarriorHeroController();
	//~ Begin GenericTeamAgent Interface
	virtual FGenericTeamId GetGenericTeamId() const override;
	//~ End GenericTeamAgent Interface

public:
	FGenericTeamId HeroTeamID; 
};
