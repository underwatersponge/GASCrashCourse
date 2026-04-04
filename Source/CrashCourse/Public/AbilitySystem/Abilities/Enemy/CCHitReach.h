// 

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/CCGameplayAbility.h"
#include "CCHitReach.generated.h"

UCLASS()
class CRASHCOURSE_API UCCHitReach : public UCCGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Crash|Ability")
	void CacheHitDirectionVectors(AActor* instigator);
	
	UPROPERTY(BlueprintReadOnly, Category = "Crash|Ability")
	FVector avatarForward;
	
	UPROPERTY(BlueprintReadOnly, Category = "Crash|Ability")
	FVector toInstigator;	
};
