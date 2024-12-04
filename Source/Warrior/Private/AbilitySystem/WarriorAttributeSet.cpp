// BlueCode


#include "AbilitySystem/WarriorAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Debug/WarriorDebugHelper.h"

UWarriorAttributeSet::UWarriorAttributeSet()
{
	InitCurrentHealth(1.f);
	InitMaxHealth(1.f);
	InitCurrentRage(1.f);
	InitMaxRage(1.f);
	InitAttackPower(1.f);
	InitDefensePower(1.f);
}

void UWarriorAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	if(Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth(),0.0f, GetMaxHealth());

		SetCurrentHealth(NewCurrentHealth);
	}

	if(Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
	{
		const float NewCurrentRage = FMath::Clamp(GetCurrentRage(),0.0f, GetMaxRage());

		SetCurrentRage(NewCurrentRage);
	}

	if(Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float OldHealth = GetCurrentHealth();
		const float DamageDone = GetDamageTaken();
		const float NewCurrentHealth = FMath::Clamp(OldHealth-DamageDone,0.0f,GetMaxHealth());
		
		SetCurrentHealth(NewCurrentHealth);
		const FString DebugString = FString::Printf(TEXT("Old health: %f, DamageDone: %f, NewCurrentHealth: %f"),
			OldHealth,DamageDone,NewCurrentHealth);

		Debug::Print(DebugString,FColor::Green);
		
		//TODO:: notify the UI
		//TODO:: handle character death
		if(NewCurrentHealth==0.0f)
		{
			
		}
	}
}
