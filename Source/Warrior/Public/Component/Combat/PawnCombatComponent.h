// BlueCode

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Component/PawnExtensionComponentBase.h"
#include "PawnCombatComponent.generated.h"

class UBoxComponent;
class AWarriorWeaponBase;

UENUM(BlueprintType)
enum class EToggleDamageType : uint8
{
	CurrentEquippedWeapon,
	LeftHand,
	RightHand,
	RightFoot
};

UCLASS()
class WARRIOR_API UPawnCombatComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
	void RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AWarriorWeaponBase* WeaponToRegister, bool RegisterAsEquippedWeapon = false);
	UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
	void RegisterLethalBodyPart(FGameplayTag InWeaponTagToRegister, AWarriorWeaponBase* WeaponToRegister);

	UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
	AWarriorWeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;

	UPROPERTY(BlueprintReadWrite, Category = "Warrior|Combat")
	FGameplayTag CurrentEquippedWeaponTag;
	
	UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
	AWarriorWeaponBase* GetCharacterCurrentEquippedWeapon() const;
	
	UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
	void ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType = EToggleDamageType::CurrentEquippedWeapon);

	UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
	void AddBodyCollisionComponent(EToggleDamageType DamageType, UBoxComponent* BoxComponent);
	
	virtual void OnHitTargetActor(AActor* HitActor);
	virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor);

	

protected:
	virtual void ToggleEquippedWeaponCollision(bool bShouldEnable);
	virtual void ToggleBodyCollisionBoxCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType);
	
	UPROPERTY(VisibleAnywhere)
	TMap<EToggleDamageType, UBoxComponent*> BodyDamageCollisionComponents;

	UPROPERTY()
	TArray<TObjectPtr<AActor>> OverlappedActors;

	
private:
	TMap<FGameplayTag, AWarriorWeaponBase*> CharacterCarriedWeaponMap;
	
	
};
