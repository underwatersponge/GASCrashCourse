// 
#include "AbilitySystem/CCAbilitySystemComponent.h"

#include "CrashCourse/Public/GameplayTagss/CCTags.h"

UCCAbilitySystemComponent::UCCAbilitySystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCCAbilitySystemComponent::OnGiveAbility(FGameplayAbilitySpec& AbilitySpec)
{
	Super::OnGiveAbility(AbilitySpec);
	
	HandleActivateAbility(AbilitySpec);
}

void UCCAbilitySystemComponent::OnRep_ActivateAbilities()
{
	Super::OnRep_ActivateAbilities();
	
	FScopedAbilityListLock ActivateScopeLock(*this);
	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		HandleActivateAbility(AbilitySpec);
	}
}

void UCCAbilitySystemComponent::HandleActivateAbility(const FGameplayAbilitySpec& AbilitySpec)
{
	if (!IsValid(AbilitySpec.Ability))
		return;
	for (const auto& tag : AbilitySpec.Ability->AbilityTags)
	{
		if (tag.MatchesTagExact(CCTags::CCAbilities::ActiveOnGiveAbility))
		{
			TryActivateAbility(AbilitySpec.Handle);
			return;
		}
	}
}


