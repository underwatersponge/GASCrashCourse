// 

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Components/WidgetComponent.h"
#include "CCWidgetComponent.generated.h"

class UCCAttributeSet;
class UCCAbilitySystemComponent;
class ACCBaseCharacter;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRASHCOURSE_API UCCWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
private:
	void InitAbilitySystemData();
	bool IsASCInitialized() const;
	void InitializeAttributeDelegate();
	void BindWidgetToAttributeChange(UWidget* widgetObject, const TTuple<FGameplayAttribute, FGameplayAttribute>& pair) const;;
	
	UFUNCTION()
	void OnASCInitialized(UAbilitySystemComponent* ASC, UAttributeSet* AS);
	
	UFUNCTION()
	void BindToAttributeChanged();

protected:
	UPROPERTY(EditAnywhere, Category = "Crash|Attribute")
	TMap<FGameplayAttribute, FGameplayAttribute> AttributeMap;
private:
	TWeakObjectPtr<ACCBaseCharacter> CrashCharacter;
	TWeakObjectPtr<UCCAbilitySystemComponent> AbilitySystemComponent;
	TWeakObjectPtr<UCCAttributeSet> AttributeSet;
};
