

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"

#include "CCBaseCharacter.generated.h"

class UGameplayAbility;

UCLASS(Abstract)
class CRASHCOURSE_API ACCBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ACCBaseCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	void GiveStartupAbilities() const;
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Crash|Ability")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
};
