// BlueCode


#include "AnimInstance/Hero/WarriorHeroLinkedAnimLayer.h"
#include "AnimInstance/Hero/WarriorHeroAnimInstance.h"

UWarriorHeroAnimInstance* UWarriorHeroLinkedAnimLayer::GetHeroAnimInstance() const
{
	return Cast<UWarriorHeroAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
