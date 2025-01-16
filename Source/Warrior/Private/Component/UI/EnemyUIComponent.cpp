// BlueCode


#include "Component/UI/EnemyUIComponent.h"

#include "Widget/WarriorWidgetBase.h"

void UEnemyUIComponent::RegisterEnemyDrawnWidget(UWarriorWidgetBase* InWidgetToRegister)
{
	EnemyDrawnWidgets.Add(InWidgetToRegister);
}

void UEnemyUIComponent::RemoveEnemyDrawnWidgetsIfAny()
{
	if(EnemyDrawnWidgets.IsEmpty())
	{
		return;
	}

	for(UWarriorWidgetBase* DrawnWidget : EnemyDrawnWidgets)
	{
		if(DrawnWidget)
		{
			DrawnWidget->RemoveFromParent();
		}
	}
	
	EnemyDrawnWidgets.Empty();
}
