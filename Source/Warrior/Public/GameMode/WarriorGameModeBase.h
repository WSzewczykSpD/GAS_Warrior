// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WarriorGameModeBase.generated.h"


enum class EWarriorGameDifficulty : uint8;

UCLASS()
class WARRIOR_API AWarriorGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AWarriorGameModeBase();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Settings")
	EWarriorGameDifficulty CurrentGameDifficulty;

public:
	FORCEINLINE	EWarriorGameDifficulty GetCurrentGameDifficulty() const { return CurrentGameDifficulty;}
};
