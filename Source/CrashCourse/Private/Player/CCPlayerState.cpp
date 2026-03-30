


#include "Player/CCPlayerState.h"
#include "AbilitySystemComponent.h"

ACCPlayerState::ACCPlayerState()
{
	//SetNetUpdateFrequency(100.0f);
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

UAbilitySystemComponent* ACCPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
