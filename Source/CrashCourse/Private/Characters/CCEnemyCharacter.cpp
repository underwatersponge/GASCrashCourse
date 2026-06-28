#include "Characters/CCEnemyCharacter.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/CCAbilitySystemComponent.h"
#include "AIController.h"
#include "AbilitySystem/CCAttributeSet.h"
#include "GameplayTagss/CCTags.h"
#include "Net/UnrealNetwork.h"

ACCEnemyCharacter::ACCEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	AbilitySystemComponent = CreateDefaultSubobject<UCCAbilitySystemComponent>(FName("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UCCAttributeSet>(FName("AttributeSet"));
}

void ACCEnemyCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ThisClass, bIsBeingLaunched);
}

UAbilitySystemComponent* ACCEnemyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* ACCEnemyCharacter::GetAttributeSet() const
{
	return AttributeSet;
}

void ACCEnemyCharacter::StopMovementUntilLanded()
{
	bIsBeingLaunched = true;
	
	AAIController* aiController = Cast<AAIController>(GetOwner());
	if (!IsValid(aiController))
		return;
	aiController->StopMovement();
	
	if (!LandedDelegate.IsAlreadyBound(this, &ThisClass::EnableMovementOnLanded))
	{
		LandedDelegate.AddDynamic(this, &ThisClass::EnableMovementOnLanded);
	}
}

void ACCEnemyCharacter::EnableMovementOnLanded(const FHitResult& hitResult)
{
	bIsBeingLaunched = false;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, CCTags::Events::Enemy::EndAttack, FGameplayEventData());
	LandedDelegate.RemoveAll(this);
	
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

