#include "Characters/CCEnemyCharacter.h"

#include "AbilitySystem/CCAbilitySystemComponent.h"
#include "AIController.h"
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

UAttributeSet* ACCEnemyCharacter::GetAttributeSet() const
{
	return AttributeSet;
}

void ACCEnemyCharacter::HandleDeath()
{
	Super::HandleDeath();
	
	AAIController* aiController = Cast<AAIController>(GetController());
	if (!IsValid(aiController)) return;
	aiController->StopMovement();
}

void ACCEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (!IsValid(GetAbilitySystemComponent()))
		return;
	GetAbilitySystemComponent()->InitAbilityActorInfo(this, this);
	DEL_OnASCInitialized.Broadcast(GetAbilitySystemComponent(), GetAttributeSet());
	
	if (!HasAuthority())
		return;
	GiveStartupAbilities();
	InitializeAttributes();
	
	UCCAttributeSet* CC_AttributeSet = Cast<UCCAttributeSet>(GetAttributeSet());
	if(IsValid(CC_AttributeSet))
		return;
	GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(CC_AttributeSet->GetHealthAttribute()).AddUObject(this, &ThisClass::OnHealthChanged);
}

