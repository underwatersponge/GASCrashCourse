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
	
	virtual void BeginPlay() override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const override;
	
	UFUNCTION(BlueprintImplementableEvent)
	float GetTimelineLength();
protected:
	virtual void HandleDeath() override;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Crash|AI")
	float AcceptDistance{500.0f};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Crash|AI")
	float MinAttackDelay{0.1f};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Crash|AI")
	float MaxAttackDelay{2.0f};
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Crash|Ability")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
