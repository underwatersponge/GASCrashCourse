#include "Player/CCPlayerState.h"
#include "AbilitySystem/CCAbilitySystemComponent.h"

#include "AbilitySystem/CCAttributeSet.h"

ACCPlayerState::ACCPlayerState()
{
	//SetNetUpdateFrequency(100.0f);
	AbilitySystemComponent = CreateDefaultSubobject<UCCAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet = CreateDefaultSubobject<UCCAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* ACCPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
