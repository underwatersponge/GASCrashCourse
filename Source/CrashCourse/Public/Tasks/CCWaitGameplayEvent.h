// 

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Async/AbilityAsync_WaitGameplayEvent.h"
#include "CCWaitGameplayEvent.generated.h"

/**
 * 
 */
UCLASS()
class CRASHCOURSE_API UCCWaitGameplayEvent : public UAbilityAsync_WaitGameplayEvent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category ="CC", meta = (HidePin = "OwningAbility", DefaultToSelf ="OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UCCWaitGameplayEvent* WaitGameplayEventProxy(AActor* TargetActor, FGameplayTag EventTag, AActor* OptionalExternalTarget = nullptr, bool OnlyTriggerOnce = false, bool OnlyMatchExact = true);

	void StartActivate();	
};
