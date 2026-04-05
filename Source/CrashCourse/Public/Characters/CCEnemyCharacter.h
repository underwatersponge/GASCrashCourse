// 

#pragma once

#include "CoreMinimal.h"
#include "CCBaseCharacter.h"
#include "CCEnemyCharacter.generated.h"

class UAttributeSet;

UCLASS()
class CRASHCOURSE_API ACCEnemyCharacter : public ACCBaseCharacter
{
	GENERATED_BODY()

public:
	ACCEnemyCharacter();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void BeginPlay() override;
private:
	UPROPERTY(VisibleAnywhere, Category = "Crash|Ability")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
