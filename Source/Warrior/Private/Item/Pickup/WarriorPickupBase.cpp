// BlueCode


#include "Item/Pickup/WarriorPickupBase.h"

#include "Components/SphereComponent.h"

// Sets default values
AWarriorPickupBase::AWarriorPickupBase()
{
	PrimaryActorTick.bCanEverTick = true;

	PickUpCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PickUpCollisionSphere"));
	SetRootComponent(PickUpCollisionSphere);
	PickUpCollisionSphere->InitSphereRadius(50.f);
	PickUpCollisionSphere->OnComponentBeginOverlap.AddUniqueDynamic(this,&ThisClass::OnPickUpCollisionSphereBeginOverlap); 

}

void AWarriorPickupBase::OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

