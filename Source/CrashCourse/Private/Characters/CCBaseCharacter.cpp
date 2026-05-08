#include "Characters/CCBaseCharacter.h"
#include "AbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"

ACCBaseCharacter::ACCBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}

UAbilitySystemComponent* ACCBaseCharacter::GetAbilitySystemComponent() const
{
	return nullptr;
}

void ACCBaseCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ThisClass, bAlivate);
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

void ACCBaseCharacter::InitializeAttributes() const
{
	checkf(IsValid(InitializeAttributesEffect), TEXT("InitializeAttributesEffect not set"));
	
	FGameplayEffectContextHandle contextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	FGameplayEffectSpecHandle specHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(InitializeAttributesEffect, 1.0f, contextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*specHandle.Data.Get());
}

UAttributeSet* ACCBaseCharacter::GetAttributeSet() const
{
	return nullptr;
}

void ACCBaseCharacter::OnHealthChanged(const FOnAttributeChangeData& AttributeChangeData)
{
	if (AttributeChangeData.NewValue < 0.f)
		HandleDeath();
}

void ACCBaseCharacter::HandleDeath()
{
	if (IsValid(GEngine))
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("%s is Died!"), *GetName()));
	bAlivate = false;
}

void ACCBaseCharacter::HandReSpawn()
{
	bAlivate = true;
}
