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
	
	void HandleActivateAbility(const FGameplayAbilitySpec& AbilitySpec);
};
