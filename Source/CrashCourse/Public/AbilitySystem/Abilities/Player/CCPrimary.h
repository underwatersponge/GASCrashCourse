// 

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/CCGameplayAbility.h"
#include "CCPrimary.generated.h"

/**
 * 
 */
UCLASS()
class CRASHCOURSE_API UCCPrimary : public UCCGameplayAbility
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable,Category = "Crash|Ability")
	void HitBoxOverlayTest();
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Crash|Ability")
	float HitBoxRadius = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Crash|Ability")
	float HitBoxForwardOffset = 200.0f;
	
	UPROPERTY(EditDefaultsOnly,  Category =  "Crash|Ability")
	float HitBoxElevationOffset = 20.0f;
};
