// 

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/CCGameplayAbility.h"
#include "CCSearchTarget.generated.h"

class AAIController;
class UAITask_MoveTo;
class UAbilityTask_WaitDelay;
class UCCWaitGameplayEvent;
class ACCBaseCharacter;
class ACCEnemyCharacter;
/**
 * 
 */
UCLASS()
class CRASHCOURSE_API UCCSearchTarget : public UCCGameplayAbility
{
	GENERATED_BODY()
public:
	UCCSearchTarget();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
private:
	void StartSearch();
	UFUNCTION()
	void EndAttackEventReceived(FGameplayEventData Payload);
	UFUNCTION()
	void Search();
	UFUNCTION()
	void MoveToTargetAndAttack();
	UFUNCTION()
	void AttackTarget();
	UFUNCTION()
	void Attack();
	
public:
	TWeakObjectPtr<ACCEnemyCharacter> OwnerCharacter;
	TWeakObjectPtr<AAIController> OwnerController;
	TWeakObjectPtr<ACCBaseCharacter> TargetBaseCharacter;
	
private:
	UPROPERTY()
	TObjectPtr<UCCWaitGameplayEvent> WaitGameplayEventTask;
	UPROPERTY()
	TObjectPtr<UAbilityTask_WaitDelay> SearchDelayTask;
	UPROPERTY()
	TObjectPtr<UAbilityTask_WaitDelay> AttackDelayTask;
	UPROPERTY()
	TObjectPtr<UAITask_MoveTo> MoveToLocationOrActorTask;
};
