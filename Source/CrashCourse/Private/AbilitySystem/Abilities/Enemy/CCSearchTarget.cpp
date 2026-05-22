// 


#include "AbilitySystem/Abilities/Enemy/CCSearchTarget.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AIController.h"
#include "Abilities/Tasks/AbilityTask_WaitDelay.h"
#include "Characters/CCEnemyCharacter.h"
#include "Tasks/CCWaitGameplayEvent.h"
#include "GameplayTagss/CCTags.h"
#include "Tasks/GameplayTask_WaitDelay.h"
#include "Utils/CCBlueprintLibrary.h"
#include "Characters/CCBaseCharacter.h"
#include "Tasks/AITask_MoveTo.h"

UCCSearchTarget::UCCSearchTarget()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerOnly;
}

void UCCSearchTarget::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                      const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                      const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	OwnerCharacter = Cast<ACCEnemyCharacter>(GetAvatarActorFromActorInfo());
	if (IsValid(OwnerCharacter.Get()))
	{
		OwnerController = Cast<AAIController>(OwnerCharacter->GetController());
	}
	
	StartSearch();
	WaitGameplayEventTask = UCCWaitGameplayEvent::WaitGameplayEventProxy(GetAvatarActorFromActorInfo(), CCTags::Events::Enemy::EndAttack);
	WaitGameplayEventTask->EventReceived.AddDynamic(this, &ThisClass::EndAttackEventReceived);
	WaitGameplayEventTask->StartActivate();
}

void UCCSearchTarget::StartSearch()
{
	if (bShowDebug)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.7f, FColor::Red, FString::Printf(TEXT("UCCSearchTarget::Start")));
	}
	if (!IsValid(OwnerCharacter.Get()))
		return;
	
	float searchDelay = FMath::RandRange(OwnerCharacter->MinAttackDelay, OwnerCharacter->MaxAttackDelay);
	SearchDelayTask = UAbilityTask_WaitDelay::WaitDelay(this, searchDelay);

	SearchDelayTask->OnFinish.AddDynamic(this, &ThisClass::Search);
	SearchDelayTask->Activate();
}

void UCCSearchTarget::EndAttackEventReceived(FGameplayEventData Payload)
{
	if (OwnerCharacter.IsValid())
	{
		StartSearch();
	}
}

void UCCSearchTarget::Search()
{
	if (!IsValid(OwnerCharacter.Get()))
		return;
	FVector SearchOrigin = OwnerCharacter->GetActorLocation();
	
	TargetBaseCharacter = Cast<ACCBaseCharacter>(UCCBlueprintLibrary::SearchClosestCharacter(GetAvatarActorFromActorInfo(), SearchOrigin, CrashTags::Player).Character);
	
	if (!TargetBaseCharacter.IsValid())
	{
		StartSearch();
		return;
	}
	
	if (TargetBaseCharacter->IsAlivate())
	{
		MoveToTargetAndAttack();
	}
	else
	{
		StartSearch();
	}
}

void UCCSearchTarget::MoveToTargetAndAttack()
{
	if (!OwnerCharacter.IsValid() || !OwnerController.IsValid() || !TargetBaseCharacter.IsValid() )
	{
		return;
	}
	if (!OwnerCharacter->IsAlivate())
	{
		StartSearch();
		return;
	}
	
	MoveToLocationOrActorTask = UAITask_MoveTo::AIMoveTo(
		OwnerController.Get(), FVector(), TargetBaseCharacter.Get(),
		OwnerCharacter->AcceptDistance);
	
	// MoveToLocationOrActorTask->OnMoveFinished().AddUObject(this, &ThisClass::AttackTarget);
	MoveToLocationOrActorTask->ConditionalPerformMove();
	EPathFollowingResult::Type result =  MoveToLocationOrActorTask->GetMoveResult();
	if (result == EPathFollowingResult::Type::Success)
	{
		AttackTarget();
	}
	else
	{
		StartSearch();
	}
}

void UCCSearchTarget::AttackTarget()
{
	// GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("AttackTarget"));
	OwnerCharacter->RotateToTarget(TargetBaseCharacter.Get());
	
	AttackDelayTask = UAbilityTask_WaitDelay::WaitDelay(this, OwnerCharacter->GetTimelineLength());
	AttackDelayTask->OnFinish.AddDynamic(this, &ThisClass::Attack);
	AttackDelayTask->Activate();
}

void UCCSearchTarget::Attack()
{
	const FGameplayTag AttackTag = CCTags::CCAbilities::Enemy::Attack;
	GetAbilitySystemComponentFromActorInfo()->TryActivateAbilitiesByTag(AttackTag.GetSingleTagContainer());
}

