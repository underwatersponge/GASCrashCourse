// 


#include "Tasks/CCWaitGameplayEvent.h"

#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"

UCCWaitGameplayEvent* UCCWaitGameplayEvent::WaitGameplayEventProxy(AActor* TargetActor,FGameplayTag EventTag, AActor* OptionalExternalTarget, bool OnlyTriggerOnce, bool OnlyMatchExact)
{
	UCCWaitGameplayEvent* MyObj = NewObject<UCCWaitGameplayEvent>();
	MyObj->SetAbilityActor(TargetActor);
	MyObj->Tag = EventTag;
	MyObj->OnlyTriggerOnce = OnlyTriggerOnce;
	MyObj->OnlyMatchExact = OnlyMatchExact;
	
	return MyObj;
}

void UCCWaitGameplayEvent::StartActivate()
{
	Activate();
}
