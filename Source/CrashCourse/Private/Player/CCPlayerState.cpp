#include "Player/CCPlayerState.h"
#include "AbilitySystem/CCAbilitySystemComponent.h"

ACCPlayerState::ACCPlayerState()
{
	//SetNetUpdateFrequency(100.0f);
	AbilitySystemComponent = CreateDefaultSubobject<UCCAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

UAbilitySystemComponent* ACCPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
