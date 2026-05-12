// 
#include "Tasks/CCAttributeChangeTask.h"
#include "AbilitySystemComponent.h"

UCCAttributeChangeTask* UCCAttributeChangeTask::ListenForAttributeChange(UAbilitySystemComponent* AbilitySystemComponent, FGameplayAttribute Attribute)
{
	UCCAttributeChangeTask* Task = NewObject<UCCAttributeChangeTask>();
	Task->ASC = AbilitySystemComponent;
	Task->AttributeToListenFor = Attribute;
	
	if (!IsValid(AbilitySystemComponent))
	{
		Task->RemoveFromRoot();
		return nullptr;
	}
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(Task, &UCCAttributeChangeTask::AttributeChanged);
	return Task;
}

void UCCAttributeChangeTask::EndTask()
{
	if (ASC.IsValid())
	{
		ASC->GetGameplayAttributeValueChangeDelegate(AttributeToListenFor).RemoveAll(this);
	}
	
	SetReadyToDestroy();
	MarkAsGarbage();
}

void UCCAttributeChangeTask::AttributeChanged(const FOnAttributeChangeData& Data)
{
	DEL_OnAttributeChange.Broadcast(Data.Attribute, Data.NewValue, Data.OldValue);
}
