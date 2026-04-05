#include "Characters/CCEnemyCharacter.h"
#include "AbilitySystem/CCAbilitySystemComponent.h"

#include "AbilitySystem/CCAttributeSet.h"

ACCEnemyCharacter::ACCEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	AbilitySystemComponent = CreateDefaultSubobject<UCCAbilitySystemComponent>(FName("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UCCAttributeSet>(FName("AttributeSet"));
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
	InitializeAttributes();
}

