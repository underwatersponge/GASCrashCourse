#include "Characters/CCEnemyCharacter.h"
#include "AbilitySystem/CCAbilitySystemComponent.h"

ACCEnemyCharacter::ACCEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	AbilitySystemComponent = CreateDefaultSubobject<UCCAbilitySystemComponent>(FName("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
}

UAbilitySystemComponent* ACCEnemyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ACCEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (!IsValid(GetAbilitySystemComponent()))
		return;
	GetAbilitySystemComponent()->InitAbilityActorInfo(this, this);
	if (!HasAuthority())
		return;
	GiveStartupAbilities();
}

