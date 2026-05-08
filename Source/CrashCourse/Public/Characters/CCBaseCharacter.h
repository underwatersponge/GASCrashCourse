

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"

#include "CCBaseCharacter.generated.h"

class UGameplayEffect;
class UGameplayAbility;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FASCInitialized, UAbilitySystemComponent*, ASC, UAttributeSet*, AS);

UCLASS(Abstract)
class CRASHCOURSE_API ACCBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ACCBaseCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;	
	void GiveStartupAbilities() const;
	void InitializeAttributes() const;
	
	virtual UAttributeSet* GetAttributeSet() const;
	
	bool IsAlivate() const {return bAlivate;}
	void SetAlivate(bool bAlivateStatus){bAlivate = bAlivateStatus;}
	
protected:
	void OnHealthChanged(const FOnAttributeChangeData& AttributeChangeData);
	void HandleDeath();
	void HandReSpawn();
	
public:
	UPROPERTY(BlueprintAssignable)
	FASCInitialized DEL_OnASCInitialized;;
private:
	UPROPERTY(EditDefaultsOnly, Category = "Crash|Ability")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
	
	UPROPERTY(EditDefaultsOnly, Category = "Crash|Effects")
	TSubclassOf<UGameplayEffect> InitializeAttributesEffect;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true), Replicated)
	bool bAlivate = true;;
};
