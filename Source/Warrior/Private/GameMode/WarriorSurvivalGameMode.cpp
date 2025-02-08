// BlueCode


#include "GameMode/WarriorSurvivalGameMode.h"

#include "NavigationSystem.h"
#include "Character/WarriorEnemyCharacter.h"
#include "Debug/WarriorDebugHelper.h"
#include "Engine/AssetManager.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"

void AWarriorSurvivalGameMode::BeginPlay()
{
	Super::BeginPlay();

	checkf(EnemyWaveSpawnerDataTable, TEXT("Forgot to assign a valid DataTable in SurvivorGameModeBP"));

	SetCurrentSurvivalGameModeState(EWarriorSurvivalGameModeState::WaitSpawnNewWave);

	TotalWavesToSpawn = EnemyWaveSpawnerDataTable->GetRowNames().Num();

	PreLoadNextWaveEnemies();
	
}

void AWarriorSurvivalGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(CurrentSurvivalGameModeState == EWarriorSurvivalGameModeState::WaitSpawnNewWave)
	{
		TimePassedSinceStart += DeltaSeconds;

		if(TimePassedSinceStart >= SpawnNewWaveWaitTime)
		{
			TimePassedSinceStart = 0.f;
			
			SetCurrentSurvivalGameModeState(EWarriorSurvivalGameModeState::SpawningNewWave);
		}
	}

	if(CurrentSurvivalGameModeState == EWarriorSurvivalGameModeState::SpawningNewWave)
	{
		TimePassedSinceStart += DeltaSeconds;

		if(TimePassedSinceStart >= SpawnEnemiesDelayTime)
		{
			CurrentSpawnedEnemiesCounter += TrySpawnWaveEnemies();
			
			TimePassedSinceStart = 0.f;
			
			SetCurrentSurvivalGameModeState(EWarriorSurvivalGameModeState::InProgress);
		}
	}
	if(CurrentSurvivalGameModeState == EWarriorSurvivalGameModeState::WaveCompleted)
	{
		TimePassedSinceStart += DeltaSeconds;

		if(TimePassedSinceStart>= WaveCompletedWaitTime)
		{
			TimePassedSinceStart = 0.f;
			CurrentWaveCount++;

			if(HasFinishedAllWaves())
			{
				SetCurrentSurvivalGameModeState(EWarriorSurvivalGameModeState::AllWavesDone);
			}else
			{
				SetCurrentSurvivalGameModeState(EWarriorSurvivalGameModeState::WaitSpawnNewWave);
				PreLoadNextWaveEnemies();
			}
		}
	}
	
}

void AWarriorSurvivalGameMode::SetCurrentSurvivalGameModeState(EWarriorSurvivalGameModeState InState)
{
	CurrentSurvivalGameModeState = InState;
	
	OnSurvivalGameModeChange.Broadcast(CurrentSurvivalGameModeState);
}

bool AWarriorSurvivalGameMode::HasFinishedAllWaves() const
{
	return CurrentWaveCount > TotalWavesToSpawn;
}

void AWarriorSurvivalGameMode::PreLoadNextWaveEnemies()
{
	if(HasFinishedAllWaves())
	{
		return;
	}

	PreLoadedEnemyClassMap.Empty();
	
	for(const FWarriorEnemyWaveSpawnerInfo& SpawnerInfo : GetCurrentWaveSpawnerTableRow()->EnemyWaveSpawnerDefinitions)
	{
		if(SpawnerInfo.SoftEnemyClassToSpawn.IsNull()) continue;

		UAssetManager::GetStreamableManager().RequestAsyncLoad(
			SpawnerInfo.SoftEnemyClassToSpawn.ToSoftObjectPath(),
			FStreamableDelegate::CreateLambda(
				[SpawnerInfo,this]()
				{
					if(UClass* LoadedEnemyClass = SpawnerInfo.SoftEnemyClassToSpawn.Get())
					{
						PreLoadedEnemyClassMap.Emplace(SpawnerInfo.SoftEnemyClassToSpawn,LoadedEnemyClass);
						Debug::Print(LoadedEnemyClass->GetName() + TEXT(" is loaded"));
					}
				}

			)
		);
	}
	
}

FWarriorEnemyWaveSpawnerTableRow* AWarriorSurvivalGameMode::GetCurrentWaveSpawnerTableRow() const
{
	const FName RowName = FName(TEXT("Wave") + FString::FromInt(CurrentWaveCount));

	FWarriorEnemyWaveSpawnerTableRow* FoundRow = EnemyWaveSpawnerDataTable->FindRow<FWarriorEnemyWaveSpawnerTableRow>(RowName, FString());

	checkf(FoundRow,TEXT("Could not find a valid row under the name %s in the data table."), *RowName.ToString());
	
	return FoundRow;
}

int32 AWarriorSurvivalGameMode::TrySpawnWaveEnemies()
{
	if(TargetPointsArray.IsEmpty())
	{
		UGameplayStatics::GetAllActorsOfClass(this, ATargetPoint::StaticClass(),TargetPointsArray);
	}
	checkf(!TargetPointsArray.IsEmpty(),TEXT("No Valid target point found in level: %s for spawning enemies"), *GetWorld()->GetName());

	uint32 EnemiesSpawnedThisTime = 0;

	for(const FWarriorEnemyWaveSpawnerInfo& SpawnerInfo : GetCurrentWaveSpawnerTableRow()->EnemyWaveSpawnerDefinitions)
	{
		if(SpawnerInfo.SoftEnemyClassToSpawn.IsNull()) continue;

		const int32 NumToSpawn = FMath::RandRange(SpawnerInfo.MinPerSpawnCount,SpawnerInfo.MaxPerSpawnCount);

		UClass* LoadedEnemyClass = PreLoadedEnemyClassMap.FindChecked(SpawnerInfo.SoftEnemyClassToSpawn);

		for(int32 i = 0 ; i< NumToSpawn; i++)
		{
			const int32 RandomTargetPointIndex = FMath::RandRange(0, TargetPointsArray.Num() - 1);
			const FVector SpawnOrigin = TargetPointsArray[RandomTargetPointIndex]->GetActorLocation();
			const FRotator SpawnRotation =  TargetPointsArray[RandomTargetPointIndex]->GetActorForwardVector().ToOrientationRotator();
			FVector RandomLocation;

			UNavigationSystemV1::K2_GetRandomLocationInNavigableRadius(this, SpawnOrigin,RandomLocation,400.f);

			RandomLocation += FVector(0.f,0.f,150.f);

			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride =  ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			AWarriorEnemyCharacter* SpawnedEnemy = GetWorld()->SpawnActor<AWarriorEnemyCharacter>(LoadedEnemyClass, RandomLocation, SpawnRotation, SpawnParams);

			 if(SpawnedEnemy)
			 {
			 	SpawnedEnemy->OnDestroyed.AddUniqueDynamic(this,&ThisClass::OnEnemyDestroyed);

			 	
			 	EnemiesSpawnedThisTime++;
			 	TotalSpawnedEnemiesThisWaveCounter++;
			 }
			
			if(!ShouldKeepSpawnEnemies())
			{
				return EnemiesSpawnedThisTime;
			}
			
		}
	}
	
	return EnemiesSpawnedThisTime;
}

bool AWarriorSurvivalGameMode::ShouldKeepSpawnEnemies() const
{
	return TotalSpawnedEnemiesThisWaveCounter < GetCurrentWaveSpawnerTableRow()->TotalEnemyToSpawnThisWave;
}

void AWarriorSurvivalGameMode::OnEnemyDestroyed(AActor* DestroyedActor)
{
	CurrentSpawnedEnemiesCounter--;

	if(ShouldKeepSpawnEnemies())
	{
		CurrentSpawnedEnemiesCounter += TrySpawnWaveEnemies();	
	}
	else if(CurrentSpawnedEnemiesCounter == 0)
	{
		TotalSpawnedEnemiesThisWaveCounter = 0;
		SetCurrentSurvivalGameModeState(EWarriorSurvivalGameModeState::WaveCompleted);
	}
}

void AWarriorSurvivalGameMode::RegisterSpawnedEnemies(const TArray<AWarriorEnemyCharacter*>& InEnemiesToRegister)
{
	for(AWarriorEnemyCharacter* SpawnedEnemy : InEnemiesToRegister)
	{
		if(SpawnedEnemy)
		{
			CurrentSpawnedEnemiesCounter++;
			SpawnedEnemy->OnDestroyed.AddUniqueDynamic(this,&ThisClass::OnEnemyDestroyed);
		}
	}
}

