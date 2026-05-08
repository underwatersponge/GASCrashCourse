// 

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Kismet/BlueprintAsyncActionBase.h"

#include "CCAttributeChangeTask.generated.h"

struct FOnAttributeChangeData;
class UAbilitySystemComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAttributeChange, FGameplayAttribute, Attribute, float, NewValue, float, OldValue);

UCLASS()
class CRASHCOURSE_API UCCAttributeChangeTask : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Crash|Task", meta = (BlueprintInternalUseOnly = "true"))
	static UCCAttributeChangeTask* ListenForAttributeChange(UAbilitySystemComponent* AbilitySystemComponent, FGameplayAttribute Attribute);
	
	UFUNCTION(BlueprintCallable)
	void EndTask();
	
	void AttributeChanged(const FOnAttributeChangeData& Data);
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChange DEL_OnAttributeChange;
	
	TWeakObjectPtr<UAbilitySystemComponent> ASC;
	FGameplayAttribute AttributeToListenFor;
};
