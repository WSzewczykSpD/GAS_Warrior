// BlueCode


#include "WarriorTypes/WarriorCountDownAction.h"

#include "Debug/WarriorDebugHelper.h"

void FWarriorCountDownAction::UpdateOperation(FLatentResponse& Response)
{
	if(bNeedToCancel)
	{
		CountDownOutput = EWarriorCountDownActionOutput::Cancelled;
		
		Response.FinishAndTriggerIf(true, ExecutionFunction,OutputLink,CallbackTarget);

		return;
	}

	if(ElapsedTimeSinceStart >= TotalCountDownTime)
	{
		CountDownOutput = EWarriorCountDownActionOutput::Completed;
		
		Response.FinishAndTriggerIf(true, ExecutionFunction,OutputLink,CallbackTarget);
		
		return;
	}
	if(ElapsedInterval<UpdateInterval)
	{
		ElapsedInterval += Response.ElapsedTime();
	}
	else
	{
		ElapsedTimeSinceStart += UpdateInterval > 0.f ? UpdateInterval : Response.ElapsedTime();

		OutRemainingTime = TotalCountDownTime - ElapsedTimeSinceStart;

		//Debug::Print(TEXT("code: Remainig time: %f"),OutRemainingTime);
		CountDownOutput = EWarriorCountDownActionOutput::Updated;

		Response.TriggerLink(ExecutionFunction, OutputLink, CallbackTarget);

		ElapsedInterval = 0.f;
	}
	
}

void FWarriorCountDownAction::CancelAction()
{
	bNeedToCancel = true;
}

