// 

#include "AbilitySystem/CCAttributeSet.h"

#include "Net/UnrealNetwork.h"

void UCCAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxMana, COND_None, REPNOTIFY_Always);
}

void UCCAttributeSet::OnRep_Health(const FGameplayAttributeData& oldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Health, oldValue);
}

void UCCAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& oldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxHealth, oldValue);
}

void UCCAttributeSet::OnRep_Mana(const FGameplayAttributeData& oldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Mana, oldValue);
}

void UCCAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& oldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxMana, oldValue);
}
