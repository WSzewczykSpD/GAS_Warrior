// BlueCode


#include "AbilitySystem/GEExecCalc/GEExecCalc_DamageTaken.h"

#include "WarriorGameplayTags.h"
#include "AbilitySystem/WarriorAttributeSet.h"
#include "Debug/WarriorDebugHelper.h"

struct FWarriorDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)
	
	
	FWarriorDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWarriorAttributeSet,AttackPower,Source,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWarriorAttributeSet,DefensePower,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWarriorAttributeSet,DamageTaken,Target,false);
	}
};

static const FWarriorDamageCapture& GetWarriorDamageCapture()
{
	static FWarriorDamageCapture WarriorDamageCapture; 
	return 	WarriorDamageCapture;
};


UGEExecCalc_DamageTaken::UGEExecCalc_DamageTaken()
{
	/*Slow way of doing capture*/
	// FProperty* AttackPowerProperty = FindFieldChecked<FProperty>(
	// 	UWarriorAttributeSet::StaticClass(),
	// 	GET_MEMBER_NAME_CHECKED(UWarriorAttributeSet,AttackPower)
	// 	);
	//
	// FGameplayEffectAttributeCaptureDefinition AttackPowerCaptureDefinition(
	// 	AttackPowerProperty,
	// 	EGameplayEffectAttributeCaptureSource::Source,
	// 	false
	// 	);
	// RelevantAttributesToCapture.Add(AttackPowerCaptureDefinition);

	RelevantAttributesToCapture.Add(GetWarriorDamageCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetWarriorDamageCapture().DefensePowerDef);
	RelevantAttributesToCapture.Add(GetWarriorDamageCapture().DamageTakenDef);
}

void UGEExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec(); 

	// EffectSpec.GetContext().GetSourceObject();
	// EffectSpec.GetContext().GetAbility();
	// EffectSpec.GetContext().GetInstigator();
	// EffectSpec.GetContext().GetEffectCauser();

	
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();
	
	float SourceAttackPower = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetWarriorDamageCapture().AttackPowerDef,EvaluateParameters,SourceAttackPower);
	//Debug::Print(TEXT("SourceAttackPower"),SourceAttackPower);

	float BaseDamage = 0.0f;
	int32 UsedLightAttackCombo = 0;
	int32 UsedHeavyAttackCombo = 0;
	
	for(const TPair<FGameplayTag,float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if(TagMagnitude.Key.MatchesTagExact(WarriorGameplayTags::Shared_SetByCaller_BaseDamage))
		{
			BaseDamage = TagMagnitude.Value;
			//Debug::Print(TEXT("BaseDamage"),BaseDamage);
		}
		if(TagMagnitude.Key.MatchesTagExact(WarriorGameplayTags::Player_SetByCaller_AttackType_Light))
		{
			UsedLightAttackCombo = TagMagnitude.Value;
			//Debug::Print(TEXT("UsedLightAttackCombo"),UsedLightAttackCombo);
		}
		if(TagMagnitude.Key.MatchesTagExact(WarriorGameplayTags::Player_SetByCaller_AttackType_Heavy))
		{
			UsedHeavyAttackCombo = TagMagnitude.Value;
			//Debug::Print(TEXT("UsedHeavyAttackCombo"),UsedHeavyAttackCombo);
		}
	}
	
	float TargetDefensePower = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetWarriorDamageCapture().DefensePowerDef,EvaluateParameters,TargetDefensePower);
	//Debug::Print(TEXT("TargetDefensePower"),TargetDefensePower);

	if(UsedLightAttackCombo != 0)
	{
		const float DamageIncreasePercentLight = (UsedLightAttackCombo-1)*0.05 + 1.0f;

		BaseDamage *= DamageIncreasePercentLight;
		//Debug::Print(TEXT("ScaledBaseDamageLight"),BaseDamage);
	}
	if(UsedHeavyAttackCombo != 0)
	{
		const float DamageIncreasePercentHeavy = UsedHeavyAttackCombo * 0.15f + 1.0f;

		BaseDamage *= DamageIncreasePercentHeavy;
		//Debug::Print(TEXT("ScaledBaseDamageHeavy"),BaseDamage);
	}

	const float FinalDamageDone = BaseDamage * SourceAttackPower/TargetDefensePower;
	//Debug::Print(TEXT("FinalDamageDone"),FinalDamageDone);
	
	if(FinalDamageDone>0.f)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(GetWarriorDamageCapture().DamageTakenProperty,
				EGameplayModOp::Override,
				FinalDamageDone)
			);
	}
}
