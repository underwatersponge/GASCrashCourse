


#include "Characters/CCBaseCharacter.h"
#include "AbilitySystemComponent.h"

ACCBaseCharacter::ACCBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}

UAbilitySystemComponent* ACCBaseCharacter::GetAbilitySystemComponent() const
{
	return nullptr;
}

void ACCBaseCharacter::GiveStartupAbilities() const
{
	for (auto& ability : StartupAbilities)
	{
		UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(ability);
		ASC->GiveAbility(AbilitySpec);
	}
}

void ACCBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}
