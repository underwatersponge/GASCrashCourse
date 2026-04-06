// 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "AbilitySystem/CCAttributeSet.h"

#include "CCAttributeWidget.generated.h"

UCLASS()
class CRASHCOURSE_API UCCAttributeWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void OnAttributeChanged(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair, const UCCAttributeSet* AttributeSet);
	bool MatchesAttribute(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Attribute Changed"))
	void BP_OnAttributeChange(float newValue, float newMaxValue);
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Crash|Attribute")
	FGameplayAttribute Attribute;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Crash|Attribute")
	FGameplayAttribute MaxAttribute;
};
