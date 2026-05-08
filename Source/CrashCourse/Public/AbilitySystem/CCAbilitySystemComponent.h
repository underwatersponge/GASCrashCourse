// 

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "CCAbilitySystemComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRASHCOURSE_API UCCAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UCCAbilitySystemComponent();

	virtual void OnGiveAbility(FGameplayAbilitySpec& AbilitySpec) override;
	virtual void OnRep_ActivateAbilities() override;
	
	UFUNCTION(BlueprintCallable, Category = "Crash|Ability")
	void SetAbilityLevel(const TSubclassOf<UGameplayAbility> abilityClass, int32 level);
	
	UFUNCTION(BlueprintCallable, Category = "Crash|Ability")
	void AddToAbilityLevel(const TSubclassOf<UGameplayAbility> abilityClass, int32 level = 1);
	
	
	void HandleActivateAbility(const FGameplayAbilitySpec& AbilitySpec);
};
